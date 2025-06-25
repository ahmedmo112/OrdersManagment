#include "managers/UserManager.h"
#include "utils/Database.h"
#include "utils/Logger.h"
#include "utils/Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

UserManager::UserManager() : nextUserId(1), currentUser(nullptr)
{
    loadUsers();
    if (users.empty())
    {
        createDefaultAdmin();
    }
}

UserManager::~UserManager()
{
    saveUsers();
}

void UserManager::loadUsers()
{
    Database &db = Database::getInstance();
    std::vector<std::string> data = db.loadUsers();

    users.clear();
    for (const auto &line : data)
    {
        if (!line.empty())
        {
            User user = User::deserialize(line);
            users.push_back(user);

            // Update next ID
            if (user.getUserId() >= nextUserId)
            {
                nextUserId = user.getUserId() + 1;
            }
        }
    }

    LOG_INFO("Loaded " + std::to_string(users.size()) + " users");
}

void UserManager::saveUsers()
{
    std::vector<std::string> data;
    for (const auto &user : users)
    {
        data.push_back(user.serialize());
    }

    Database &db = Database::getInstance();
    if (db.saveUsers(data))
    {
        LOG_INFO("Saved " + std::to_string(users.size()) + " users");
    }
    else
    {
        LOG_ERROR("Failed to save users");
    }
}

int UserManager::generateNextId()
{
    return nextUserId++;
}

void UserManager::createDefaultAdmin()
{
    User admin(1, "admin", Utils::hashPassword("admin"),
               "System Administrator", "admin@orderms.com", UserRole::ADMIN);
    admin.setIsActive(true);

    users.push_back(admin);
    saveUsers();

    LOG_INFO("Created default admin user");
}

bool UserManager::login(const std::string &username, const std::string &password)
{
    auto it = std::find_if(users.begin(), users.end(),
                           [&username](const User &u)
                           {
                               return Utils::toLower(u.getUsername()) == Utils::toLower(username) && u.getIsActive();
                           });

    if (it != users.end() && it->verifyPassword(password))
    {
        currentUser = &(*it);
        currentUser->updateLastLogin();
        saveUsers(); // Save updated last login time
        LOG_INFO("User logged in: " + username);
        return true;
    }

    LOG_WARNING("Failed login attempt for: " + username);
    return false;
}

void UserManager::logout()
{
    if (currentUser)
    {
        LOG_INFO("User logged out: " + currentUser->getUsername());
        currentUser = nullptr;
    }
}

bool UserManager::addUser(const User &user)
{
    if (!validateUser(user))
    {
        LOG_WARNING("Invalid user data");
        return false;
    }

    User newUser = user;
    newUser.setUserId(generateNextId());
    newUser.setPassword(Utils::hashPassword(newUser.getPassword()));

    users.push_back(newUser);
    saveUsers();

    LOG_INFO("Added new user: " + newUser.getUsername());
    return true;
}

User *UserManager::getUser(int userId)
{
    auto it = std::find_if(users.begin(), users.end(),
                           [userId](const User &u)
                           {
                               return u.getUserId() == userId;
                           });

    return (it != users.end()) ? &(*it) : nullptr;
}

User *UserManager::getUserByUsername(const std::string &username)
{
    auto it = std::find_if(users.begin(), users.end(),
                           [&username](const User &u)
                           {
                               return Utils::toLower(u.getUsername()) == Utils::toLower(username);
                           });

    return (it != users.end()) ? &(*it) : nullptr;
}

std::vector<User> UserManager::getAllUsers()
{
    return users;
}

std::vector<User> UserManager::getActiveUsers()
{
    std::vector<User> activeUsers;
    std::copy_if(users.begin(), users.end(),
                 std::back_inserter(activeUsers),
                 [](const User &u)
                 { return u.getIsActive(); });
    return activeUsers;
}

bool UserManager::updateUser(const User &user)
{
    auto it = std::find_if(users.begin(), users.end(),
                           [&user](const User &u)
                           {
                               return u.getUserId() == user.getUserId();
                           });

    if (it != users.end())
    {
        if (!validateUser(user))
        {
            return false;
        }

        // Preserve password if not changed
        User updatedUser = user;
        if (updatedUser.getPassword().empty())
        {
            updatedUser.setPassword(it->getPassword());
        }
        else
        {
            updatedUser.setPassword(Utils::hashPassword(updatedUser.getPassword()));
        }

        *it = updatedUser;
        saveUsers();
        LOG_INFO("Updated user: " + user.getUsername());
        return true;
    }

    return false;
}

bool UserManager::deleteUser(int userId)
{
    auto it = std::find_if(users.begin(), users.end(),
                           [userId](const User &u)
                           {
                               return u.getUserId() == userId;
                           });

    if (it != users.end())
    {
        // Don't allow deletion of current user or last admin
        if (currentUser && it->getUserId() == currentUser->getUserId())
        {
            LOG_WARNING("Cannot delete currently logged in user");
            return false;
        }

        if (it->getRole() == UserRole::ADMIN && getUserCountByRole(UserRole::ADMIN) <= 1)
        {
            LOG_WARNING("Cannot delete last admin user");
            return false;
        }

        std::string username = it->getUsername();
        users.erase(it);
        saveUsers();
        LOG_INFO("Deleted user: " + username);
        return true;
    }

    return false;
}

bool UserManager::deactivateUser(int userId)
{
    User *user = getUser(userId);
    if (user)
    {
        // Don't allow deactivation of current user or last admin
        if (currentUser && user->getUserId() == currentUser->getUserId())
        {
            return false;
        }

        if (user->getRole() == UserRole::ADMIN && getUserCountByRole(UserRole::ADMIN) <= 1)
        {
            return false;
        }

        user->setIsActive(false);
        saveUsers();
        LOG_INFO("Deactivated user: " + user->getUsername());
        return true;
    }
    return false;
}

bool UserManager::activateUser(int userId)
{
    User *user = getUser(userId);
    if (user)
    {
        user->setIsActive(true);
        saveUsers();
        LOG_INFO("Activated user: " + user->getUsername());
        return true;
    }
    return false;
}

bool UserManager::changePassword(int userId, const std::string &oldPassword, const std::string &newPassword)
{
    User *user = getUser(userId);
    if (user && user->verifyPassword(oldPassword))
    {
        if (validatePassword(newPassword))
        {
            user->setPassword(Utils::hashPassword(newPassword));
            saveUsers();
            LOG_INFO("Password changed for user: " + user->getUsername());
            return true;
        }
    }
    return false;
}

bool UserManager::resetPassword(int userId, const std::string &newPassword)
{
    User *user = getUser(userId);
    if (user && validatePassword(newPassword))
    {
        user->setPassword(Utils::hashPassword(newPassword));
        saveUsers();
        LOG_INFO("Password reset for user: " + user->getUsername());
        return true;
    }
    return false;
}

bool UserManager::validatePassword(const std::string &password)
{
    return password.length() >= 4; // Simple validation
}

bool UserManager::changeUserRole(int userId, UserRole newRole)
{
    User *user = getUser(userId);
    if (user)
    {
        // Don't allow changing role of last admin
        if (user->getRole() == UserRole::ADMIN &&
            newRole != UserRole::ADMIN &&
            getUserCountByRole(UserRole::ADMIN) <= 1)
        {
            return false;
        }

        user->setRole(newRole);
        saveUsers();
        LOG_INFO("Changed role for user: " + user->getUsername() + " to " + User::roleToString(newRole));
        return true;
    }
    return false;
}

std::vector<User> UserManager::getUsersByRole(UserRole role)
{
    std::vector<User> result;
    std::copy_if(users.begin(), users.end(),
                 std::back_inserter(result),
                 [role](const User &u)
                 { return u.getRole() == role; });
    return result;
}

std::vector<User> UserManager::searchByUsername(const std::string &username)
{
    std::vector<User> results;
    std::string searchUsername = Utils::toLower(username);

    std::copy_if(users.begin(), users.end(),
                 std::back_inserter(results),
                 [&searchUsername](const User &u)
                 {
                     return Utils::toLower(u.getUsername()).find(searchUsername) != std::string::npos;
                 });

    return results;
}

std::vector<User> UserManager::searchByFullName(const std::string &fullName)
{
    std::vector<User> results;
    std::string searchName = Utils::toLower(fullName);

    std::copy_if(users.begin(), users.end(),
                 std::back_inserter(results),
                 [&searchName](const User &u)
                 {
                     return Utils::toLower(u.getFullName()).find(searchName) != std::string::npos;
                 });

    return results;
}

std::vector<User> UserManager::searchByEmail(const std::string &email)
{
    std::vector<User> results;
    std::string searchEmail = Utils::toLower(email);

    std::copy_if(users.begin(), users.end(),
                 std::back_inserter(results),
                 [&searchEmail](const User &u)
                 {
                     return Utils::toLower(u.getEmail()).find(searchEmail) != std::string::npos;
                 });

    return results;
}

bool UserManager::isUsernameUnique(const std::string &username, int excludeUserId)
{
    return std::none_of(users.begin(), users.end(),
                        [&username, excludeUserId](const User &u)
                        {
                            return u.getUserId() != excludeUserId &&
                                   Utils::toLower(u.getUsername()) == Utils::toLower(username);
                        });
}

bool UserManager::isEmailUnique(const std::string &email, int excludeUserId)
{
    return std::none_of(users.begin(), users.end(),
                        [&email, excludeUserId](const User &u)
                        {
                            return u.getUserId() != excludeUserId &&
                                   Utils::toLower(u.getEmail()) == Utils::toLower(email);
                        });
}

bool UserManager::validateUser(const User &user)
{
    if (!user.isValid())
    {
        return false;
    }

    if (!isUsernameUnique(user.getUsername(), user.getUserId()))
    {
        LOG_WARNING("Username already exists: " + user.getUsername());
        return false;
    }

    if (!isEmailUnique(user.getEmail(), user.getUserId()))
    {
        LOG_WARNING("Email already exists: " + user.getEmail());
        return false;
    }

    return true;
}

bool UserManager::hasPermission(const std::string &operation) const
{
    if (!currentUser)
        return false;

    if (operation == "manage_users")
        return currentUser->canManageUsers();
    if (operation == "manage_products")
        return currentUser->canManageProducts();
    if (operation == "manage_orders")
        return currentUser->canManageOrders();
    if (operation == "view_reports")
        return currentUser->canViewReports();
    if (operation == "manage_customers")
        return currentUser->canManageOrders(); // Employees can manage customers
    if (operation == "manage_settings")
        return currentUser->canManageUsers(); // Only admins

    return false;
}

bool UserManager::canManageUsers() const
{
    return currentUser && currentUser->canManageUsers();
}

bool UserManager::canManageProducts() const
{
    return currentUser && currentUser->canManageProducts();
}

bool UserManager::canManageOrders() const
{
    return currentUser && currentUser->canManageOrders();
}

bool UserManager::canViewReports() const
{
    return currentUser && currentUser->canViewReports();
}

int UserManager::getTotalUsers()
{
    return static_cast<int>(users.size());
}

int UserManager::getActiveUsersCount()
{
    return static_cast<int>(std::count_if(users.begin(), users.end(),
                                          [](const User &u)
                                          { return u.getIsActive(); }));
}

int UserManager::getUserCountByRole(UserRole role)
{
    return static_cast<int>(std::count_if(users.begin(), users.end(),
                                          [role](const User &u)
                                          { return u.getRole() == role && u.getIsActive(); }));
}

std::vector<User> UserManager::getRecentlyActiveUsers(int days)
{
    // Implementation for getting recently active users
    // This would require storing last activity timestamps
    return std::vector<User>();
}

void UserManager::logLoginAttempt(const std::string &username, bool success)
{
    if (success)
    {
        LOG_INFO("Successful login: " + username);
    }
    else
    {
        LOG_WARNING("Failed login attempt: " + username);
    }
}

std::vector<std::string> UserManager::getLoginHistory(int userId)
{
    // Implementation for getting login history
    // This would require storing login timestamps
    return std::vector<std::string>();
}

bool UserManager::isAccountLocked(const std::string &username)
{
    // Implementation for account locking
    // This would require tracking failed login attempts
    return false;
}

void UserManager::printUser(const User &user)
{
    std::cout << user.toString() << std::endl;
}

void UserManager::printAllUsers()
{
    Utils::printHeader("All Users");
    for (const auto &user : users)
    {
        printUser(user);
        Utils::printSeparator('-', 50);
    }
}

void UserManager::printUsersByRole(UserRole role)
{
    Utils::printHeader("Users with role: " + User::roleToString(role));
    for (const auto &user : users)
    {
        if (user.getRole() == role)
        {
            printUser(user);
            Utils::printSeparator('-', 50);
        }
    }
}

bool UserManager::exportToCSV(const std::string &filename)
{
    LOG_INFO("Exporting users to CSV: " + filename);
    return true;
}

bool UserManager::importFromCSV(const std::string &filename)
{
    LOG_INFO("Importing users from CSV: " + filename);
    return true;
}