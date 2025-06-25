#include "managers/CustomerManager.h"
#include "utils/Database.h"
#include "utils/Logger.h"
#include "utils/Utils.h"
#include <algorithm>
#include <iostream>
#include <map>

CustomerManager::CustomerManager() : nextCustomerId(1)
{
    loadCustomers();
}

CustomerManager::~CustomerManager()
{
    saveCustomers();
}

void CustomerManager::loadCustomers()
{
    Database &db = Database::getInstance();
    std::vector<std::string> data = db.loadCustomers();

    customers.clear();
    for (const auto &line : data)
    {
        if (!line.empty())
        {
            Customer customer = Customer::deserialize(line);
            customers.push_back(customer);

            // Update next ID
            if (customer.getCustomerId() > nextCustomerId)
            {
                nextCustomerId = customer.getCustomerId() + 1;
            }
        }
    }

    LOG_INFO("Loaded " + std::to_string(customers.size()) + " customers");
}

void CustomerManager::saveCustomers()
{
    std::vector<std::string> data;
    for (const auto &customer : customers)
    {
        data.push_back(customer.serialize());
    }

    Database &db = Database::getInstance();
    if (db.saveCustomers(data))
    {
        LOG_INFO("Saved " + std::to_string(customers.size()) + " customerss");
    }
    else
    {
        LOG_ERROR("Failed to save customers");
    }
}

int CustomerManager::generateNextId()
{
    return nextCustomerId++;
}

bool CustomerManager::addCustomer(const Customer &customer)
{
    if (!validateCustomer(customer))
    {
        LOG_WARNING("Invalid customer data");
        return false;
    }

    Customer newCustomer = customer;
    newCustomer.setCustomerId(generateNextId());

    customers.push_back(newCustomer);
    saveCustomers();

    LOG_INFO("Added new customer: " + newCustomer.getName());
    return true;
}

Customer *CustomerManager::getCustomer(int customerId)
{
    auto it = std::find_if(customers.begin(), customers.end(),
                           [customerId](const Customer &c)
                           {
                               return c.getCustomerId() == customerId;
                           });

    return (it != customers.end()) ? &(*it) : nullptr;
}

std::vector<Customer> CustomerManager::getAllCustomers()
{
    return customers;
}

std::vector<Customer> CustomerManager::getActiveCustomers()
{
    std::vector<Customer> activeCustomers;
    std::copy_if(customers.begin(), customers.end(),
                 std::back_inserter(activeCustomers),
                 [](const Customer &c)
                 { return c.getIsActive(); });
    return activeCustomers;
}

bool CustomerManager::updateCustomer(const Customer &customer)
{
    auto it = std::find_if(customers.begin(), customers.end(),
                           [&customer](const Customer &c)
                           {
                               return c.getCustomerId() == customer.getCustomerId();
                           });

    if (it != customers.end())
    {
        if (!validateCustomer(customer))
        {
            return false;
        }

        *it = customer;
        saveCustomers();
        LOG_INFO("Updated customer: " + customer.getName());
        return true;
    }

    return false;
}

bool CustomerManager::deleteCustomer(int customerId)
{
    auto it = std::find_if(customers.begin(), customers.end(),
                           [customerId](const Customer &c)
                           {
                               return c.getCustomerId() == customerId;
                           });

    if (it != customers.end())
    {
        std::string customerName = it->getName();
        customers.erase(it);
        saveCustomers();
        LOG_INFO("Deleted customer: " + customerName);
        return true;
    }

    return false;
}

bool CustomerManager::deactivateCustomer(int customerId)
{
    Customer *customer = getCustomer(customerId);
    if (customer)
    {
        customer->setIsActive(false);
        saveCustomers();
        LOG_INFO("Deactivated customer: " + customer->getName());
        return true;
    }
    return false;
}

bool CustomerManager::activateCustomer(int customerId)
{
    Customer *customer = getCustomer(customerId);
    if (customer)
    {
        customer->setIsActive(true);
        saveCustomers();
        LOG_INFO("Activated customers: " + customer->getName());
        return true;
    }
    return false;
}

std::vector<Customer> CustomerManager::searchByName(const std::string &name)
{
    std::vector<Customer> results;
    std::string searchName = Utils::toLower(name);

    std::copy_if(customers.begin(), customers.end(),
                 std::back_inserter(results),
                 [&searchName](const Customer &c)
                 {
                     return Utils::toLower(c.getName()).find(searchName) != std::string::npos;
                 });

    return results;
}

std::vector<Customer> CustomerManager::searchByEmail(const std::string &email)
{
    std::vector<Customer> results;
    std::string searchEmail = Utils::toLower(email);

    std::copy_if(customers.begin(), customers.end(),
                 std::back_inserter(results),
                 [&searchEmail](const Customer &c)
                 {
                     return Utils::toLower(c.getEmail()).find(searchEmail) != std::string::npos;
                 });

    return results;
}

std::vector<Customer> CustomerManager::searchByPhone(const std::string &phone)
{
    std::vector<Customer> results;

    std::copy_if(customers.begin(), customers.end(),
                 std::back_inserter(results),
                 [&phone](const Customer &c)
                 {
                     return c.getPhone().find(phone) != std::string::npos;
                 });

    return results;
}

std::vector<Customer> CustomerManager::getCustomersByCity(const std::string &city)
{
    std::vector<Customer> results;
    std::string searchCity = Utils::toLower(city);

    std::copy_if(customers.begin(), customers.end(),
                 std::back_inserter(results),
                 [&searchCity](const Customer &c)
                 {
                     return Utils::toLower(c.getCity()) == searchCity;
                 });

    return results;
}

std::vector<Customer> CustomerManager::getCustomersByCountry(const std::string &country)
{
    std::vector<Customer> results;
    std::string searchCountry = Utils::toLower(country);

    std::copy_if(customers.begin(), customers.end(),
                 std::back_inserter(results),
                 [&searchCountry](const Customer &c)
                 {
                     return Utils::toLower(c.getCountry()) == searchCountry;
                 });

    return results;
}

bool CustomerManager::isEmailUnique(const std::string &email, int excludeCustomerId)
{
    return std::none_of(customers.begin(), customers.end(),
                        [&email, excludeCustomerId](const Customer &c)
                        {
                            return c.getCustomerId() != excludeCustomerId &&
                                   Utils::toLower(c.getEmail()) == Utils::toLower(email);
                        });
}

bool CustomerManager::isPhoneUnique(const std::string &phone, int excludeCustomerId)
{
    return std::none_of(customers.begin(), customers.end(),
                        [&phone, excludeCustomerId](const Customer &c)
                        {
                            return c.getCustomerId() != excludeCustomerId && c.getPhone() == phone;
                        });
}

bool CustomerManager::validateCustomer(const Customer &customer)
{
    if (!customer.isValid())
    {
        return false;
    }

    if (!isEmailUnique(customer.getEmail(), customer.getCustomerId()))
    {
        LOG_WARNING("Email already exists: " + customer.getEmail());
        return false;
    }

    if (!isPhoneUnique(customer.getPhone(), customer.getCustomerId()))
    {
        LOG_WARNING("Phone number already exists: " + customer.getPhone());
        return false;
    }

    return true;
}

int CustomerManager::getTotalCustomers()
{
    return static_cast<int>(customers.size());
}

int CustomerManager::getActiveCustomersCount()
{
    return static_cast<int>(std::count_if(customers.begin(), customers.end(),
                                          [](const Customer &c)
                                          { return c.getIsActive(); }));
}

int CustomerManager::getInactiveCustomersCount()
{
    return getTotalCustomers() - getActiveCustomersCount();
}

std::vector<std::string> CustomerManager::getTopCities(int limit)
{
    std::map<std::string, int> cityCount;

    for (const auto &customer : customers)
    {
        if (customer.getIsActive())
        {
            cityCount[customer.getCity()]++;
        }
    }

    std::vector<std::pair<std::string, int>> sorted(cityCount.begin(), cityCount.end());
    std::sort(sorted.begin(), sorted.end(),
              [](const auto &a, const auto &b)
              { return a.second > b.second; });

    std::vector<std::string> result;
    for (int i = 0; i < limit && i < static_cast<int>(sorted.size()); ++i)
    {
        result.push_back(sorted[i].first);
    }

    return result;
}

std::vector<std::string> CustomerManager::getTopCountries(int limit)
{
    std::map<std::string, int> countryCount;

    for (const auto &customer : customers)
    {
        if (customer.getIsActive())
        {
            countryCount[customer.getCountry()]++;
        }
    }

    std::vector<std::pair<std::string, int>> sorted(countryCount.begin(), countryCount.end());
    std::sort(sorted.begin(), sorted.end(),
              [](const auto &a, const auto &b)
              { return a.second > b.second; });

    std::vector<std::string> result;
    for (int i = 0; i < limit && i < static_cast<int>(sorted.size()); ++i)
    {
        result.push_back(sorted[i].first);
    }

    return result;
}

void CustomerManager::printCustomer(const Customer &customer)
{
    std::cout << customer.toString() << std::endl;
}

void CustomerManager::printAllCustomers()
{
    Utils::printHeader("All Customers");
    for (const auto &customer : customers)
    {
        printCustomer(customer);
        Utils::printSeparator('-', 50);
    }
}

bool CustomerManager::exportToCSV(const std::string &filename)
{
    // Implementation for CSV export
    LOG_INFO("Exporting customers to CSV: " + filename);
    return true;
}

bool CustomerManager::importFromCSV(const std::string &filename)
{
    // Implementation for CSV import
    LOG_INFO("Importing customers from CSV: " + filename);
    return true;
}