#include "models/Customer.h"
#include "utils/Utils.h"
#include <sstream>

Customer::Customer()
    : customerId(0), isActive(true)
{
}

Customer::Customer(int id, const std::string &name, const std::string &email,
                   const std::string &phone, const std::string &address,
                   const std::string &city, const std::string &country)
    : customerId(id), name(name), email(email), phone(phone),
      address(address), city(city), country(country), isActive(true)
{
}

std::string Customer::toString() const
{
    std::stringstream ss;
    ss << "Customer ID: " << customerId << "\n"
       << "Name: " << name << "\n"
       << "Email: " << email << "\n"
       << "Phone: " << phone << "\n"
       << "Address: " << address << "\n"
       << "City: " << city << "\n"
       << "Country: " << country << "\n"
       << "Status: " << (isActive ? "Active" : "Inactive");
    return ss.str();
}

bool Customer::isValid() const
{
    return !name.empty() &&
           Utils::isValidEmail(email) &&
           !phone.empty() &&
           !address.empty() &&
           !city.empty() &&
           !country.empty();
}

std::string Customer::serialize() const
{
    std::stringstream ss;
    ss << customerId << "|"
       << name << "|"
       << email << "|"
       << phone << "|"
       << address << "|"
       << city << "|"
       << country << "|"
       << (isActive ? "1" : "0");
    return ss.str();
}

Customer Customer::deserialize(const std::string &data)
{
    std::vector<std::string> parts = Utils::split(data, '|');
    Customer customer;

    if (parts.size() >= 8)
    {
        customer.customerId = std::stoi(parts[0]);
        customer.name = parts[1];
        customer.email = parts[2];
        customer.phone = parts[3];
        customer.address = parts[4];
        customer.city = parts[5];
        customer.country = parts[6];
        customer.isActive = (parts[7] == "1");
    }

    return customer;
}