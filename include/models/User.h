#pragma once
#include <string>

enum class UserRole
{
    ADMIN,
    MANAGER,
    EMPLOYEE,
    GUEST
};

class User
{
private:
    int userId;
    std::string username;
    std::string password;
    std::string fullName;
    std::string email;
    UserRole role;
    bool isActive;
    std::string lastLoginDate;

public:
    // Constructors
    User();
    User(int id, const std::string &username, const std::string &password,
         const std::string &fullName, const std::string &email, UserRole role);

    // Getters
    int getUserId() const { return userId; }
    const std::string &getUsername() const { return username; }
    const std::string &getPassword() const { return password; }
    const std::string &getFullName() const { return fullName; }
    const std::string &getEmail() const { return email; }
    UserRole getRole() const { return role; }
    bool getIsActive() const { return isActive; }
    const std::string &getLastLoginDate() const { return lastLoginDate; }

    // Setters
    void setUserId(int id) { userId = id; }
    void setUsername(const std::string &username) { this->username = username; }
    void setPassword(const std::string &password) { this->password = password; }
    void setFullName(const std::string &fullName) { this->fullName = fullName; }
    void setEmail(const std::string &email) { this->email = email; }
    void setRole(UserRole role) { this->role = role; }
    void setIsActive(bool active) { isActive = active; }
    void setLastLoginDate(const std::string &date) { lastLoginDate = date; }

    // Authentication
    bool verifyPassword(const std::string &inputPassword) const;
    void updateLastLogin();

    // Role-based access control
    bool canManageUsers() const;
    bool canManageProducts() const;
    bool canManageOrders() const;
    bool canViewReports() const;
    std::string getRoleString() const;
    static std::string roleToString(UserRole role);
    static UserRole stringToRole(const std::string &roleStr);

    // Utility methods
    std::string toString() const;
    bool isValid() const;

    // Serialization
    std::string serialize() const;
    static User deserialize(const std::string &data);
};