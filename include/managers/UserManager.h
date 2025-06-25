#pragma once
#include "models/User.h"
#include <vector>
#include <memory>

class UserManager
{
private:
    std::vector<User> users;
    int nextUserId;
    User *currentUser;

    void loadUsers();
    void saveUsers();
    int generateNextId();
    void createDefaultAdmin();

public:
    UserManager();
    ~UserManager();

    // Authentication
    bool login(const std::string &username, const std::string &password);
    void logout();
    bool isLoggedIn() const { return currentUser != nullptr; }
    User *getCurrentUser() const { return currentUser; }

    // CRUD operations
    bool addUser(const User &user);
    User *getUser(int userId);
    User *getUserByUsername(const std::string &username);
    std::vector<User> getAllUsers();
    std::vector<User> getActiveUsers();
    bool updateUser(const User &user);
    bool deleteUser(int userId);
    bool deactivateUser(int userId);
    bool activateUser(int userId);

    // Password management
    bool changePassword(int userId, const std::string &oldPassword, const std::string &newPassword);
    bool resetPassword(int userId, const std::string &newPassword);
    bool validatePassword(const std::string &password);

    // User role management
    bool changeUserRole(int userId, UserRole newRole);
    std::vector<User> getUsersByRole(UserRole role);

    // Search operations
    std::vector<User> searchByUsername(const std::string &username);
    std::vector<User> searchByFullName(const std::string &fullName);
    std::vector<User> searchByEmail(const std::string &email);

    // Validation
    bool isUsernameUnique(const std::string &username, int excludeUserId = -1);
    bool isEmailUnique(const std::string &email, int excludeUserId = -1);
    bool validateUser(const User &user);

    // Access control
    bool hasPermission(const std::string &operation) const;
    bool canManageUsers() const;
    bool canManageProducts() const;
    bool canManageOrders() const;
    bool canViewReports() const;

    // Statistics
    int getTotalUsers();
    int getActiveUsersCount();
    int getUserCountByRole(UserRole role);
    std::vector<User> getRecentlyActiveUsers(int days = 30);

    // Security
    void logLoginAttempt(const std::string &username, bool success);
    std::vector<std::string> getLoginHistory(int userId);
    bool isAccountLocked(const std::string &username);

    // Utility
    void printUser(const User &user);
    void printAllUsers();
    void printUsersByRole(UserRole role);
    bool exportToCSV(const std::string &filename);
    bool importFromCSV(const std::string &filename);
};