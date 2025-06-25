#pragma once
#include "models/Customer.h"
#include <vector>
#include <memory>

class CustomerManager
{
private:
    std::vector<Customer> customers;
    int nextCustomerId;

    void loadCustomers();
    void saveCustomers();
    int generateNextId();

public:
    CustomerManager();
    ~CustomerManager();

    // CRUD operations
    bool addCustomer(const Customer &customer);
    Customer *getCustomer(int customerId);
    std::vector<Customer> getAllCustomers();
    std::vector<Customer> getActiveCustomers();
    bool updateCustomer(const Customer &customer);
    bool deleteCustomer(int customerId);
    bool deactivateCustomer(int customerId);
    bool activateCustomer(int customerId);

    // Search and filter operations
    std::vector<Customer> searchByName(const std::string &name);
    std::vector<Customer> searchByEmail(const std::string &email);
    std::vector<Customer> searchByPhone(const std::string &phone);
    std::vector<Customer> getCustomersByCity(const std::string &city);
    std::vector<Customer> getCustomersByCountry(const std::string &country);

    // Validation
    bool isEmailUnique(const std::string &email, int excludeCustomerId = -1);
    bool isPhoneUnique(const std::string &phone, int excludeCustomerId = -1);
    bool validateCustomer(const Customer &customer);

    // Statistics
    int getTotalCustomers();
    int getActiveCustomersCount();
    int getInactiveCustomersCount();
    std::vector<std::string> getTopCities(int limit = 5);
    std::vector<std::string> getTopCountries(int limit = 5);

    // Utility
    void printCustomer(const Customer &customer);
    void printAllCustomers();
    bool exportToCSV(const std::string &filename);
    bool importFromCSV(const std::string &filename);
};