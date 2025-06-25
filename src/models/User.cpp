#include "models/User.h"
#include "utils/Utils.h"
#include <sstream>

User::User()
    : userId(0), role(UserRole::GUEST), isActive(true)
{
}

User::User(int id, const std::string &username, const std::string &password,
           const std::string &fullName, const std::string &email, UserRole role)
    : userId(id), username(username), password(password), fullName(fullName),
      email(email), role(role), isActive(true)
{
}

bool User::verifyPassword(const std::string &inputPassword) const
{
    return Utils::verifyPassword(inputPassword, password);
}

void User::updateLastLogin()
{
    lastLoginDate = Utils::getCurrentDateTime();
}

bool User::canManageUsers() const
{
    return role == UserRole::ADMIN;
}

bool User::canManageProducts() const
{
    return role == UserRole::ADMIN || role == UserRole::MANAGER;
}

bool User::canManageOrders() const
{
    return role == UserRole::ADMIN || role == UserRole::MANAGER || role == UserRole::EMPLOYEE;
}

bool User::canViewReports() const
{
    return role == UserRole::ADMIN || role == UserRole::MANAGER;
}

std::string User::getRoleString() const
{
    return roleToString(role);
}

std::string User::roleToString(UserRole role)
{
    switch (role)
    {
    case UserRole::ADMIN:
        return "Administrator";
    case UserRole::MANAGER:
        return "Manager";
    case UserRole::EMPLOYEE:
        return "Employee";
    case UserRole::GUEST:
        return "Guest";
    default:
        return "Unknown";
    }
}

UserRole User::stringToRole(const std::string &roleStr)
{
    if (roleStr == "Administrator")
        return UserRole::ADMIN;
    if (roleStr == "Manager")
        return UserRole::MANAGER;
    if (roleStr == "Employee")
        return UserRole::EMPLOYEE;
    if (roleStr == "Guest")
        return UserRole::GUEST;
    return UserRole::GUEST;
}

std::string User::toString() const
{
    std::stringstream ss;
    ss << "User ID: " << userId << "\n"
       << "Username: " << username << "\n"
       << "Full Name: " << fullName << "\n"
       << "Email: " << email << "\n"
       << "Role: " << getRoleString() << "\n"
       << "Status: " << (isActive ? "Active" : "Inactive") << "\n"
       << "Last Login: " << (lastLoginDate.empty() ? "Never" : lastLoginDate);
    return ss.str();
}

bool User::isValid() const
{
    return !username.empty() &&
           !password.empty() &&
           !fullName.empty() &&
           Utils::isValidEmail(email);
}

std::string User::serialize() const
{
    std::stringstream ss;
    ss << userId << "|"
       << username << "|"
       << password << "|"
       << fullName << "|"
       << email << "|"
       << roleToString(role) << "|"
       << (isActive ? "1" : "0") << "|"
       << lastLoginDate;
    return ss.str();
}

User User::deserialize(const std::string &data)
{
    std::vector<std::string> parts = Utils::split(data, '|');
    User user;

    if (parts.size() >= 8)
    {
        user.userId = std::stoi(parts[0]);
        user.username = parts[1];
        user.password = parts[2];
        user.fullName = parts[3];
        user.email = parts[4];
        user.role = stringToRole(parts[5]);
        user.isActive = (parts[6] == "1");
        user.lastLoginDate = parts[7];
    }

    return user;
}