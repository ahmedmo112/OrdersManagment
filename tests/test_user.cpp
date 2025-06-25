#include <gtest/gtest.h>
#include "models/User.h"

class UserTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        validUser = User(1, "john.doe", "password123", "John Doe",
                         "john.doe@email.com", UserRole::EMPLOYEE);

        adminUser = User(2, "admin", "admin123", "Administrator",
                         "admin@company.com", UserRole::ADMIN);

        managerUser = User(3, "manager", "manager123", "Manager User",
                           "manager@company.com", UserRole::MANAGER);

        guestUser = User(4, "guest", "guest123", "Guest User",
                         "guest@company.com", UserRole::GUEST);
    }

    User validUser;
    User adminUser;
    User managerUser;
    User guestUser;
};

// Constructor Tests
TEST_F(UserTest, DefaultConstructor)
{
    User user;
    EXPECT_EQ(user.getUserId(), 0);
    EXPECT_EQ(user.getUsername(), "");
    EXPECT_EQ(user.getPassword(), "");
    EXPECT_EQ(user.getFullName(), "");
    EXPECT_EQ(user.getEmail(), "");
    EXPECT_EQ(user.getRole(), UserRole::GUEST);
    EXPECT_TRUE(user.getIsActive());
    EXPECT_EQ(user.getLastLoginDate(), "");
}

TEST_F(UserTest, ParameterizedConstructor)
{
    EXPECT_EQ(validUser.getUserId(), 1);
    EXPECT_EQ(validUser.getUsername(), "john.doe");
    EXPECT_EQ(validUser.getPassword(), "password123");
    EXPECT_EQ(validUser.getFullName(), "John Doe");
    EXPECT_EQ(validUser.getEmail(), "john.doe@email.com");
    EXPECT_EQ(validUser.getRole(), UserRole::EMPLOYEE);
    EXPECT_TRUE(validUser.getIsActive());
}

// Getter and Setter Tests
TEST_F(UserTest, SettersAndGetters)
{
    User user;

    user.setUserId(100);
    EXPECT_EQ(user.getUserId(), 100);

    user.setUsername("test.user");
    EXPECT_EQ(user.getUsername(), "test.user");

    user.setPassword("newpassword");
    EXPECT_EQ(user.getPassword(), "newpassword");

    user.setFullName("Test User");
    EXPECT_EQ(user.getFullName(), "Test User");

    user.setEmail("test@example.com");
    EXPECT_EQ(user.getEmail(), "test@example.com");

    user.setRole(UserRole::MANAGER);
    EXPECT_EQ(user.getRole(), UserRole::MANAGER);

    user.setIsActive(false);
    EXPECT_FALSE(user.getIsActive());

    user.setLastLoginDate("2024-01-15");
    EXPECT_EQ(user.getLastLoginDate(), "2024-01-15");
}

// Authentication Tests
TEST_F(UserTest, VerifyPasswordCorrect)
{
    EXPECT_TRUE(validUser.verifyPassword("password123"));
}

TEST_F(UserTest, VerifyPasswordIncorrect)
{
    EXPECT_FALSE(validUser.verifyPassword("wrongpassword"));
    EXPECT_FALSE(validUser.verifyPassword(""));
    EXPECT_FALSE(validUser.verifyPassword("Password123")); // Case sensitive
}

TEST_F(UserTest, UpdateLastLogin)
{
    User user = validUser;
    std::string originalDate = user.getLastLoginDate();

    user.updateLastLogin();

    // The date should be updated (not empty and different from original if it was empty)
    EXPECT_FALSE(user.getLastLoginDate().empty());
    if (originalDate.empty())
    {
        EXPECT_NE(user.getLastLoginDate(), originalDate);
    }
}

// Role-based Access Control Tests
TEST_F(UserTest, AdminPermissions)
{
    EXPECT_TRUE(adminUser.canManageUsers());
    EXPECT_TRUE(adminUser.canManageProducts());
    EXPECT_TRUE(adminUser.canManageOrders());
    EXPECT_TRUE(adminUser.canViewReports());
}

TEST_F(UserTest, ManagerPermissions)
{
    EXPECT_FALSE(managerUser.canManageUsers()); // Assuming managers can't manage users
    EXPECT_TRUE(managerUser.canManageProducts());
    EXPECT_TRUE(managerUser.canManageOrders());
    EXPECT_TRUE(managerUser.canViewReports());
}

TEST_F(UserTest, EmployeePermissions)
{
    EXPECT_FALSE(validUser.canManageUsers());
    EXPECT_FALSE(validUser.canManageProducts()); // Assuming employees can't manage products
    EXPECT_TRUE(validUser.canManageOrders());
    EXPECT_FALSE(validUser.canViewReports()); // Assuming employees can't view reports
}

TEST_F(UserTest, GuestPermissions)
{
    EXPECT_FALSE(guestUser.canManageUsers());
    EXPECT_FALSE(guestUser.canManageProducts());
    EXPECT_FALSE(guestUser.canManageOrders());
    EXPECT_FALSE(guestUser.canViewReports());
}

// Role String Conversion Tests
TEST_F(UserTest, GetRoleString)
{
    EXPECT_EQ(adminUser.getRoleString(), "ADMIN");
    EXPECT_EQ(managerUser.getRoleString(), "MANAGER");
    EXPECT_EQ(validUser.getRoleString(), "EMPLOYEE");
    EXPECT_EQ(guestUser.getRoleString(), "GUEST");
}

TEST_F(UserTest, RoleToString)
{
    EXPECT_EQ(User::roleToString(UserRole::ADMIN), "ADMIN");
    EXPECT_EQ(User::roleToString(UserRole::MANAGER), "MANAGER");
    EXPECT_EQ(User::roleToString(UserRole::EMPLOYEE), "EMPLOYEE");
    EXPECT_EQ(User::roleToString(UserRole::GUEST), "GUEST");
}

TEST_F(UserTest, StringToRole)
{
    EXPECT_EQ(User::stringToRole("ADMIN"), UserRole::ADMIN);
    EXPECT_EQ(User::stringToRole("MANAGER"), UserRole::MANAGER);
    EXPECT_EQ(User::stringToRole("EMPLOYEE"), UserRole::EMPLOYEE);
    EXPECT_EQ(User::stringToRole("GUEST"), UserRole::GUEST);

    // Test case insensitive conversion (if implemented)
    EXPECT_EQ(User::stringToRole("admin"), UserRole::ADMIN);
    EXPECT_EQ(User::stringToRole("Manager"), UserRole::MANAGER);
}

// Validation Tests
TEST_F(UserTest, ValidUser)
{
    EXPECT_TRUE(validUser.isValid());
    EXPECT_TRUE(adminUser.isValid());
    EXPECT_TRUE(managerUser.isValid());
}

TEST_F(UserTest, InvalidUserEmptyUsername)
{
    User user = validUser;
    user.setUsername("");
    EXPECT_FALSE(user.isValid());
}

TEST_F(UserTest, InvalidUserEmptyPassword)
{
    User user = validUser;
    user.setPassword("");
    EXPECT_FALSE(user.isValid());
}

TEST_F(UserTest, InvalidUserEmptyFullName)
{
    User user = validUser;
    user.setFullName("");
    EXPECT_FALSE(user.isValid());
}

TEST_F(UserTest, InvalidUserEmptyEmail)
{
    User user = validUser;
    user.setEmail("");
    EXPECT_FALSE(user.isValid());
}

TEST_F(UserTest, InvalidUserBadEmailFormat)
{
    User user = validUser;
    user.setEmail("invalid-email");
    EXPECT_FALSE(user.isValid());

    user.setEmail("no-at-symbol.com");
    EXPECT_FALSE(user.isValid());

    user.setEmail("@no-local-part.com");
    EXPECT_FALSE(user.isValid());
}

TEST_F(UserTest, ValidEmailFormats)
{
    User user = validUser;

    user.setEmail("user@domain.com");
    EXPECT_TRUE(user.isValid());

    user.setEmail("test.email@example.org");
    EXPECT_TRUE(user.isValid());

    user.setEmail("user+tag@domain.co.uk");
    EXPECT_TRUE(user.isValid());
}

// ToString Tests
TEST_F(UserTest, ToStringContainsUserInfo)
{
    std::string result = validUser.toString();

    EXPECT_NE(result.find("john.doe"), std::string::npos);
    EXPECT_NE(result.find("John Doe"), std::string::npos);
    EXPECT_NE(result.find("john.doe@email.com"), std::string::npos);
    EXPECT_NE(result.find("EMPLOYEE"), std::string::npos);

    // Password should NOT be in the string representation
    EXPECT_EQ(result.find("password123"), std::string::npos);
}

// Serialization Tests
TEST_F(UserTest, SerializationAndDeserialization)
{
    User user = validUser;
    user.setLastLoginDate("2024-01-15");
    user.setIsActive(true);

    std::string serialized = user.serialize();
    EXPECT_FALSE(serialized.empty());

    User deserialized = User::deserialize(serialized);

    EXPECT_EQ(deserialized.getUserId(), user.getUserId());
    EXPECT_EQ(deserialized.getUsername(), user.getUsername());
    EXPECT_EQ(deserialized.getPassword(), user.getPassword());
    EXPECT_EQ(deserialized.getFullName(), user.getFullName());
    EXPECT_EQ(deserialized.getEmail(), user.getEmail());
    EXPECT_EQ(deserialized.getRole(), user.getRole());
    EXPECT_EQ(deserialized.getIsActive(), user.getIsActive());
    EXPECT_EQ(deserialized.getLastLoginDate(), user.getLastLoginDate());
}

TEST_F(UserTest, SerializationRoundTrip)
{
    User original = adminUser;

    for (int i = 0; i < 3; ++i)
    {
        std::string serialized = original.serialize();
        original = User::deserialize(serialized);
    }

    EXPECT_EQ(original.getUserId(), adminUser.getUserId());
    EXPECT_EQ(original.getUsername(), adminUser.getUsername());
    EXPECT_EQ(original.getRole(), adminUser.getRole());
}

// Edge Cases
TEST_F(UserTest, UserWithSpecialCharacters)
{
    User user(5, "josé.maría", "contraseña123", "José María González",
              "jose.maria@empresa.es", UserRole::EMPLOYEE);

    EXPECT_TRUE(user.isValid());

    std::string serialized = user.serialize();
    User deserialized = User::deserialize(serialized);

    EXPECT_EQ(deserialized.getUsername(), "josé.maría");
    EXPECT_EQ(deserialized.getFullName(), "José María González");
}

TEST_F(UserTest, UserWithLongStrings)
{
    std::string longUsername(50, 'a');
    std::string longFullName(100, 'B');

    User user(6, longUsername, "password", longFullName,
              "long@email.com", UserRole::EMPLOYEE);

    EXPECT_TRUE(user.isValid());
    EXPECT_EQ(user.getUsername(), longUsername);
    EXPECT_EQ(user.getFullName(), longFullName);
}

TEST_F(UserTest, InactiveUser)
{
    User user = validUser;
    user.setIsActive(false);

    EXPECT_FALSE(user.getIsActive());
    EXPECT_TRUE(user.isValid()); // Inactive users should still be valid for data integrity
}

TEST_F(UserTest, UserWithWeakPassword)
{
    User user = validUser;
    user.setPassword("123");

    // Depending on business rules, this might be valid or invalid
    // For now, assume any non-empty password is valid at the model level
    EXPECT_TRUE(user.isValid());
}

// Password Security Tests
TEST_F(UserTest, PasswordCaseSensitivity)
{
    User user = validUser;
    user.setPassword("Password123");

    EXPECT_TRUE(user.verifyPassword("Password123"));
    EXPECT_FALSE(user.verifyPassword("password123"));
    EXPECT_FALSE(user.verifyPassword("PASSWORD123"));
}

TEST_F(UserTest, EmptyPasswordVerification)
{
    User user = validUser;
    user.setPassword("");

    EXPECT_FALSE(user.verifyPassword(""));
    EXPECT_FALSE(user.verifyPassword("anything"));
}

// Role Hierarchy Tests (if applicable)
TEST_F(UserTest, RoleHierarchy)
{
    // Test that admin has more permissions than manager
    EXPECT_TRUE(adminUser.canManageUsers());
    EXPECT_FALSE(managerUser.canManageUsers());

    // Test that manager has more permissions than employee
    EXPECT_TRUE(managerUser.canViewReports());
    EXPECT_FALSE(validUser.canViewReports());

    // Test that employee has more permissions than guest
    EXPECT_TRUE(validUser.canManageOrders());
    EXPECT_FALSE(guestUser.canManageOrders());
}