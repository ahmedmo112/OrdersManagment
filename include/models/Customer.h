#pragma once
#include <string>
#include <vector>

class Customer
{
private:
    int customerId;
    std::string name;
    std::string email;
    std::string phone;
    std::string address;
    std::string city;
    std::string country;
    bool isActive;

public:
    // Constructors
    Customer();
    Customer(int id, const std::string &name, const std::string &email,
             const std::string &phone, const std::string &address,
             const std::string &city, const std::string &country);

    // Getters
    int getCustomerId() const { return customerId; }
    const std::string &getName() const { return name; }
    const std::string &getEmail() const { return email; }
    const std::string &getPhone() const { return phone; }
    const std::string &getAddress() const { return address; }
    const std::string &getCity() const { return city; }
    const std::string &getCountry() const { return country; }
    bool getIsActive() const { return isActive; }

    // Setters
    void setCustomerId(int id) { customerId = id; }
    void setName(const std::string &name) { this->name = name; }
    void setEmail(const std::string &email) { this->email = email; }
    void setPhone(const std::string &phone) { this->phone = phone; }
    void setAddress(const std::string &address) { this->address = address; }
    void setCity(const std::string &city) { this->city = city; }
    void setCountry(const std::string &country) { this->country = country; }
    void setIsActive(bool active) { isActive = active; }

    // Utility methods
    std::string toString() const;
    bool isValid() const;

    // Serialization
    std::string serialize() const;
    static Customer deserialize(const std::string &data);
};