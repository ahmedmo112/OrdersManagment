#include "utils/Database.h"
#include "utils/Utils.h"
#include "utils/Logger.h"
#include <iostream>
#include <fstream>

std::unique_ptr<Database> Database::instance = nullptr;

Database::Database() : dataDirectory("data/")
{
}

Database &Database::getInstance()
{
    if (!instance)
    {
        instance = std::unique_ptr<Database>(new Database());
    }
    return *instance;
}

bool Database::initialize(const std::string &dataDir)
{
    dataDirectory = dataDir;
    return createDirectories();
}

bool Database::fileExists(const std::string &filename) const
{
    return Utils::fileExists(dataDirectory + filename);
}

bool Database::createDirectories() const
{
    return Utils::createDirectory(dataDirectory);
}

bool Database::saveToFile(const std::string &filename, const std::vector<std::string> &data)
{
    std::string fullPath = dataDirectory + filename;
    std::ofstream file(fullPath);

    if (!file.is_open())
    {
        LOG_ERROR("Failed to open file for writing: " + fullPath);
        return false;
    }

    for (const auto &line : data)
    {
        file << line << std::endl;
    }

    file.close();
    LOG_DEBUG("Saved " + std::to_string(data.size()) + " records to " + filename);
    return true;
}

std::vector<std::string> Database::loadFromFile(const std::string &filename)
{
    std::vector<std::string> data;
    std::string fullPath = dataDirectory + filename;
    std::ifstream file(fullPath);

    if (!file.is_open())
    {
        LOG_WARNING("File not found or cannot be opened: " + fullPath);
        return data;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (!line.empty())
        {
            data.push_back(line);
        }
    }

    file.close();
    LOG_DEBUG("Loaded " + std::to_string(data.size()) + " records from " + filename);
    return data;
}

bool Database::appendToFile(const std::string &filename, const std::string &data)
{
    std::string fullPath = dataDirectory + filename;
    std::ofstream file(fullPath, std::ios::app);

    if (!file.is_open())
    {
        LOG_ERROR("Failed to open file for appending: " + fullPath);
        return false;
    }

    file << data << std::endl;
    file.close();
    return true;
}

bool Database::deleteFromFile(const std::string &filename, int lineNumber)
{
    std::vector<std::string> data = loadFromFile(filename);

    if (lineNumber < 0 || lineNumber >= static_cast<int>(data.size()))
    {
        return false;
    }

    data.erase(data.begin() + lineNumber);
    return saveToFile(filename, data);
}

bool Database::updateInFile(const std::string &filename, int lineNumber, const std::string &newData)
{
    std::vector<std::string> data = loadFromFile(filename);

    if (lineNumber < 0 || lineNumber >= static_cast<int>(data.size()))
    {
        return false;
    }

    data[lineNumber] = newData;
    return saveToFile(filename, data);
}

// Specific data file operations
bool Database::saveUsers(const std::vector<std::string> &userData)
{
    return saveToFile("users.txt", userData);
}

std::vector<std::string> Database::loadUsers()
{
    return loadFromFile("users.txt");
}

bool Database::saveCustomers(const std::vector<std::string> &customerData)
{
    return saveToFile("customers.txt", customerData);
}

std::vector<std::string> Database::loadCustomers()
{
    return loadFromFile("customers.txt");
}

bool Database::saveProducts(const std::vector<std::string> &productData)
{
    return saveToFile("products.txt", productData);
}

std::vector<std::string> Database::loadProducts()
{
    return loadFromFile("products.txt");
}

bool Database::saveOrders(const std::vector<std::string> &orderData)
{
    return saveToFile("orders.txt", orderData);
}

std::vector<std::string> Database::loadOrders()
{
    return loadFromFile("orders.txt");
}

int Database::getNextId(const std::string &entityType)
{
    std::string filename = "next_" + entityType + "_id.txt";
    std::vector<std::string> data = loadFromFile(filename);

    if (data.empty())
    {
        return 1;
    }

    try
    {
        return std::stoi(data[0]);
    }
    catch (const std::exception &)
    {
        return 1;
    }
}

bool Database::updateNextId(const std::string &entityType, int nextId)
{
    std::string filename = "next_" + entityType + "_id.txt";
    std::vector<std::string> data = {std::to_string(nextId)};
    return saveToFile(filename, data);
}

bool Database::createBackup(const std::string &backupDir)
{
    // Implementation for backup functionality
    LOG_INFO("Creating backup to " + backupDir);
    return Utils::createDirectory(backupDir);
}

bool Database::restoreFromBackup(const std::string &backupDir)
{
    // Implementation for restore functionality
    LOG_INFO("Restoring from backup " + backupDir);
    return true;
}

void Database::close()
{
    LOG_INFO("Database closed");
}

Database::~Database()
{
    close();
}