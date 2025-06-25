#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <memory>

class Database
{
private:
    static std::unique_ptr<Database> instance;
    std::string dataDirectory;

    Database();
    bool fileExists(const std::string &filename) const;
    bool createDirectories() const;

public:
    static Database &getInstance();

    // Configuration
    bool initialize(const std::string &dataDir = "data/");
    const std::string &getDataDirectory() const { return dataDirectory; }

    // File operations
    bool saveToFile(const std::string &filename, const std::vector<std::string> &data);
    std::vector<std::string> loadFromFile(const std::string &filename);
    bool appendToFile(const std::string &filename, const std::string &data);
    bool deleteFromFile(const std::string &filename, int lineNumber);
    bool updateInFile(const std::string &filename, int lineNumber, const std::string &newData);

    // Specific data file operations
    bool saveUsers(const std::vector<std::string> &userData);
    std::vector<std::string> loadUsers();
    bool saveCustomers(const std::vector<std::string> &customerData);
    std::vector<std::string> loadCustomers();
    bool saveProducts(const std::vector<std::string> &productData);
    std::vector<std::string> loadProducts();
    bool saveOrders(const std::vector<std::string> &orderData);
    std::vector<std::string> loadOrders();

    // ID generation
    int getNextId(const std::string &entityType);
    bool updateNextId(const std::string &entityType, int nextId);

    // Backup and restore
    bool createBackup(const std::string &backupDir);
    bool restoreFromBackup(const std::string &backupDir);

    // Cleanup
    void close();
    ~Database();

    // Delete copy constructor and assignment operator
    Database(const Database &) = delete;
    Database &operator=(const Database &) = delete;
};