#include <gtest/gtest.h>
#include "utils/Database.h"
#include <filesystem>
#include <fstream>

class DatabaseTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        testDir = "test_data";
        backupDir = "test_backup";

        // Clean up any existing test directories
        std::filesystem::remove_all(testDir);
        std::filesystem::remove_all(backupDir);

        // Initialize database with test directory
        database = &Database::getInstance();
        database->initialize(testDir);
    }

    void TearDown() override
    {
        database->close();

        // Clean up test directories
        std::filesystem::remove_all(testDir);
        std::filesystem::remove_all(backupDir);
    }

    Database *database;
    std::string testDir;
    std::string backupDir;
};

// Initialization Tests
TEST_F(DatabaseTest, InitializeDatabase)
{
    EXPECT_TRUE(database->initialize(testDir));
    EXPECT_EQ(database->getDataDirectory(), testDir + "/");

    // Check if directory was created
    EXPECT_TRUE(std::filesystem::exists(testDir));
}

TEST_F(DatabaseTest, InitializeWithExistingDirectory)
{
    // Initialize again with same directory
    EXPECT_TRUE(database->initialize(testDir));
    EXPECT_EQ(database->getDataDirectory(), testDir + "/");
}

TEST_F(DatabaseTest, GetInstanceSingleton)
{
    Database &db1 = Database::getInstance();
    Database &db2 = Database::getInstance();

    EXPECT_EQ(&db1, &db2); // Should be the same instance
}

// File Operations Tests
TEST_F(DatabaseTest, SaveAndLoadFromFile)
{
    std::vector<std::string> testData = {
        "Line 1: Test data",
        "Line 2: More test data",
        "Line 3: Even more test data"};

    std::string filename = "test_file.txt";

    EXPECT_TRUE(database->saveToFile(filename, testData));

    std::vector<std::string> loadedData = database->loadFromFile(filename);

    EXPECT_EQ(loadedData.size(), testData.size());
    for (size_t i = 0; i < testData.size(); ++i)
    {
        EXPECT_EQ(loadedData[i], testData[i]);
    }
}

TEST_F(DatabaseTest, LoadFromNonExistentFile)
{
    std::vector<std::string> loadedData = database->loadFromFile("nonexistent.txt");
    EXPECT_TRUE(loadedData.empty());
}

TEST_F(DatabaseTest, SaveEmptyData)
{
    std::vector<std::string> emptyData;
    std::string filename = "empty_file.txt";

    EXPECT_TRUE(database->saveToFile(filename, emptyData));

    std::vector<std::string> loadedData = database->loadFromFile(filename);
    EXPECT_TRUE(loadedData.empty());
}

TEST_F(DatabaseTest, AppendToFile)
{
    std::string filename = "append_test.txt";
    std::vector<std::string> initialData = {"Initial line"};

    database->saveToFile(filename, initialData);

    EXPECT_TRUE(database->appendToFile(filename, "Appended line"));

    std::vector<std::string> loadedData = database->loadFromFile(filename);
    EXPECT_EQ(loadedData.size(), 2);
    EXPECT_EQ(loadedData[0], "Initial line");
    EXPECT_EQ(loadedData[1], "Appended line");
}

TEST_F(DatabaseTest, AppendToNonExistentFile)
{
    EXPECT_TRUE(database->appendToFile("new_file.txt", "First line"));

    std::vector<std::string> loadedData = database->loadFromFile("new_file.txt");
    EXPECT_EQ(loadedData.size(), 1);
    EXPECT_EQ(loadedData[0], "First line");
}

TEST_F(DatabaseTest, UpdateInFile)
{
    std::vector<std::string> testData = {
        "Line 0",
        "Line 1",
        "Line 2"};

    std::string filename = "update_test.txt";
    database->saveToFile(filename, testData);

    EXPECT_TRUE(database->updateInFile(filename, 1, "Updated Line 1"));

    std::vector<std::string> loadedData = database->loadFromFile(filename);
    EXPECT_EQ(loadedData.size(), 3);
    EXPECT_EQ(loadedData[0], "Line 0");
    EXPECT_EQ(loadedData[1], "Updated Line 1");
    EXPECT_EQ(loadedData[2], "Line 2");
}

TEST_F(DatabaseTest, UpdateInFileInvalidLineNumber)
{
    std::vector<std::string> testData = {"Line 0", "Line 1"};
    std::string filename = "update_test.txt";
    database->saveToFile(filename, testData);

    EXPECT_FALSE(database->updateInFile(filename, 5, "Invalid update"));  // Line doesn't exist
    EXPECT_FALSE(database->updateInFile(filename, -1, "Invalid update")); // Negative line number
}

TEST_F(DatabaseTest, DeleteFromFile)
{
    std::vector<std::string> testData = {
        "Line 0",
        "Line 1",
        "Line 2"};

    std::string filename = "delete_test.txt";
    database->saveToFile(filename, testData);

    EXPECT_TRUE(database->deleteFromFile(filename, 1)); // Delete middle line

    std::vector<std::string> loadedData = database->loadFromFile(filename);
    EXPECT_EQ(loadedData.size(), 2);
    EXPECT_EQ(loadedData[0], "Line 0");
    EXPECT_EQ(loadedData[1], "Line 2");
}

TEST_F(DatabaseTest, DeleteFromFileInvalidLineNumber)
{
    std::vector<std::string> testData = {"Line 0", "Line 1"};
    std::string filename = "delete_test.txt";
    database->saveToFile(filename, testData);

    EXPECT_FALSE(database->deleteFromFile(filename, 5));  // Line doesn't exist
    EXPECT_FALSE(database->deleteFromFile(filename, -1)); // Negative line number
}

// Specific Data File Operations Tests
TEST_F(DatabaseTest, SaveAndLoadUsers)
{
    std::vector<std::string> userData = {
        "1|admin|password|Administrator|admin@company.com|ADMIN|1|2024-01-01",
        "2|user1|pass123|User One|user1@company.com|EMPLOYEE|1|2024-01-02"};

    EXPECT_TRUE(database->saveUsers(userData));

    std::vector<std::string> loadedData = database->loadUsers();
    EXPECT_EQ(loadedData.size(), userData.size());
    EXPECT_EQ(loadedData[0], userData[0]);
    EXPECT_EQ(loadedData[1], userData[1]);
}

TEST_F(DatabaseTest, SaveAndLoadCustomers)
{
    std::vector<std::string> customerData = {
        "1|John Doe|john@email.com|+1234567890|123 Main St|New York|USA|1",
        "2|Jane Smith|jane@email.com|+1987654321|456 Oak Ave|Los Angeles|USA|1"};

    EXPECT_TRUE(database->saveCustomers(customerData));

    std::vector<std::string> loadedData = database->loadCustomers();
    EXPECT_EQ(loadedData.size(), customerData.size());
    EXPECT_EQ(loadedData[0], customerData[0]);
    EXPECT_EQ(loadedData[1], customerData[1]);
}

TEST_F(DatabaseTest, SaveAndLoadProducts)
{
    std::vector<std::string> productData = {
        "1|Laptop|High-performance laptop|Electronics|999.99|50|10|1",
        "2|Mouse|Wireless mouse|Electronics|29.99|100|5|1"};

    EXPECT_TRUE(database->saveProducts(productData));

    std::vector<std::string> loadedData = database->loadProducts();
    EXPECT_EQ(loadedData.size(), productData.size());
    EXPECT_EQ(loadedData[0], productData[0]);
    EXPECT_EQ(loadedData[1], productData[1]);
}

TEST_F(DatabaseTest, SaveAndLoadOrders)
{
    std::vector<std::string> orderData = {
        "1|100|John Doe|1,Laptop,2,999.99,1999.98|PENDING|2024-01-01|123 Main St|1999.98|0.0|1999.98|Test order",
        "2|101|Jane Smith|2,Mouse,1,29.99,29.99|CONFIRMED|2024-01-02|456 Oak Ave|29.99|0.0|29.99|Another order"};

    EXPECT_TRUE(database->saveOrders(orderData));

    std::vector<std::string> loadedData = database->loadOrders();
    EXPECT_EQ(loadedData.size(), orderData.size());
    EXPECT_EQ(loadedData[0], orderData[0]);
    EXPECT_EQ(loadedData[1], orderData[1]);
}

// ID Generation Tests
TEST_F(DatabaseTest, GetNextId)
{
    int userId = database->getNextId("user");
    EXPECT_GT(userId, 0);

    int nextUserId = database->getNextId("user");
    EXPECT_EQ(nextUserId, userId + 1);

    int customerId = database->getNextId("customer");
    EXPECT_GT(customerId, 0);
    // Customer ID should be independent of user ID
}

TEST_F(DatabaseTest, UpdateNextId)
{
    EXPECT_TRUE(database->updateNextId("user", 100));

    int nextId = database->getNextId("user");
    EXPECT_EQ(nextId, 100);

    int followingId = database->getNextId("user");
    EXPECT_EQ(followingId, 101);
}

TEST_F(DatabaseTest, GetNextIdDifferentEntities)
{
    int userId = database->getNextId("user");
    int customerId = database->getNextId("customer");
    int productId = database->getNextId("product");
    int orderId = database->getNextId("order");

    // All should be positive and potentially different
    EXPECT_GT(userId, 0);
    EXPECT_GT(customerId, 0);
    EXPECT_GT(productId, 0);
    EXPECT_GT(orderId, 0);
}

// Backup and Restore Tests
TEST_F(DatabaseTest, CreateBackup)
{
    // Create some test data first
    std::vector<std::string> testData = {"Test data line 1", "Test data line 2"};
    database->saveToFile("test_backup_file.txt", testData);

    EXPECT_TRUE(database->createBackup(backupDir));
    EXPECT_TRUE(std::filesystem::exists(backupDir));

    // Check if backup file exists
    std::string backupFile = backupDir + "/test_backup_file.txt";
    EXPECT_TRUE(std::filesystem::exists(backupFile));
}

TEST_F(DatabaseTest, RestoreFromBackup)
{
    // Create original data
    std::vector<std::string> originalData = {"Original data"};
    database->saveToFile("restore_test.txt", originalData);

    // Create backup
    database->createBackup(backupDir);

    // Modify original data
    std::vector<std::string> modifiedData = {"Modified data"};
    database->saveToFile("restore_test.txt", modifiedData);

    // Restore from backup
    EXPECT_TRUE(database->restoreFromBackup(backupDir));

    // Verify restoration
    std::vector<std::string> restoredData = database->loadFromFile("restore_test.txt");
    EXPECT_EQ(restoredData.size(), 1);
    EXPECT_EQ(restoredData[0], "Original data");
}

TEST_F(DatabaseTest, RestoreFromNonExistentBackup)
{
    EXPECT_FALSE(database->restoreFromBackup("nonexistent_backup"));
}

// Edge Cases and Error Handling Tests
TEST_F(DatabaseTest, SaveToFileWithSpecialCharacters)
{
    std::vector<std::string> specialData = {
        "Line with special chars: àáâãäåæçèéêë",
        "Line with symbols: !@#$%^&*()_+-={}[]|\\:;\"'<>,.?/",
        "Line with unicode: 你好世界 🌍🚀"};

    EXPECT_TRUE(database->saveToFile("special_chars.txt", specialData));

    std::vector<std::string> loadedData = database->loadFromFile("special_chars.txt");
    EXPECT_EQ(loadedData.size(), specialData.size());
    for (size_t i = 0; i < specialData.size(); ++i)
    {
        EXPECT_EQ(loadedData[i], specialData[i]);
    }
}

TEST_F(DatabaseTest, SaveLargeDataset)
{
    std::vector<std::string> largeData;
    for (int i = 0; i < 1000; ++i)
    {
        largeData.push_back("Data line " + std::to_string(i));
    }

    EXPECT_TRUE(database->saveToFile("large_file.txt", largeData));

    std::vector<std::string> loadedData = database->loadFromFile("large_file.txt");
    EXPECT_EQ(loadedData.size(), 1000);
    EXPECT_EQ(loadedData[0], "Data line 0");
    EXPECT_EQ(loadedData[999], "Data line 999");
}

TEST_F(DatabaseTest, EmptyFileOperations)
{
    std::string filename = "empty_operations.txt";

    // Update/delete operations on empty file should fail
    EXPECT_FALSE(database->updateInFile(filename, 0, "Update"));
    EXPECT_FALSE(database->deleteFromFile(filename, 0));

    // Append to empty/non-existent file should work
    EXPECT_TRUE(database->appendToFile(filename, "First line"));
}

TEST_F(DatabaseTest, ConcurrentAccess)
{
    // This is a basic test - in a real scenario you'd want more sophisticated concurrency testing
    std::string filename = "concurrent_test.txt";
    std::vector<std::string> data1 = {"Thread 1 data"};
    std::vector<std::string> data2 = {"Thread 2 data"};

    EXPECT_TRUE(database->saveToFile(filename, data1));
    EXPECT_TRUE(database->saveToFile(filename, data2)); // Should overwrite

    std::vector<std::string> result = database->loadFromFile(filename);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "Thread 2 data");
}

TEST_F(DatabaseTest, InvalidFilenames)
{
    std::vector<std::string> testData = {"Test"};

    // Test with empty filename
    EXPECT_FALSE(database->saveToFile("", testData));

    // Test with invalid characters (this may vary by OS)
    // On Windows, these characters are not allowed: < > : " | ? *
    // This test might need to be adjusted based on the OS
}

TEST_F(DatabaseTest, CloseDatabase)
{
    database->close();

    // After closing, operations should still work (assuming the database reopens internally)
    std::vector<std::string> testData = {"Post-close data"};
    EXPECT_TRUE(database->saveToFile("post_close.txt", testData));
}