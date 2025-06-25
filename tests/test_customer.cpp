#include <gtest/gtest.h>
#include "models/Customer.h"

class CustomerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Set up test customers
        validCustomer = Customer(1, "John Doe", "john.doe@email.com",
                                 "+1234567890", "123 Main St", "New York", "USA");

        emptyCustomer = Customer();
    }

    Customer validCustomer;
    Customer emptyCustomer;
};

// Constructor Tests
TEST_F(CustomerTest, DefaultConstructor)
{
    Customer customer;
    EXPECT_EQ(customer.getCustomerId(), 0);
    EXPECT_EQ(customer.getName(), "");
    EXPECT_EQ(customer.getEmail(), "");
    EXPECT_EQ(customer.getPhone(), "");
    EXPECT_EQ(customer.getAddress(), "");
    EXPECT_EQ(customer.getCity(), "");
    EXPECT_EQ(customer.getCountry(), "");
    EXPECT_TRUE(customer.getIsActive());
}

TEST_F(CustomerTest, ParameterizedConstructor)
{
    EXPECT_EQ(validCustomer.getCustomerId(), 1);
    EXPECT_EQ(validCustomer.getName(), "John Doe");
    EXPECT_EQ(validCustomer.getEmail(), "john.doe@email.com");
    EXPECT_EQ(validCustomer.getPhone(), "+1234567890");
    EXPECT_EQ(validCustomer.getAddress(), "123 Main St");
    EXPECT_EQ(validCustomer.getCity(), "New York");
    EXPECT_EQ(validCustomer.getCountry(), "USA");
    EXPECT_TRUE(validCustomer.getIsActive());
}

// Getter and Setter Tests
TEST_F(CustomerTest, SettersAndGetters)
{
    Customer customer;

    customer.setCustomerId(100);
    EXPECT_EQ(customer.getCustomerId(), 100);

    customer.setName("Jane Smith");
    EXPECT_EQ(customer.getName(), "Jane Smith");

    customer.setEmail("jane@example.com");
    EXPECT_EQ(customer.getEmail(), "jane@example.com");

    customer.setPhone("+9876543210");
    EXPECT_EQ(customer.getPhone(), "+9876543210");

    customer.setAddress("456 Oak Ave");
    EXPECT_EQ(customer.getAddress(), "456 Oak Ave");

    customer.setCity("Los Angeles");
    EXPECT_EQ(customer.getCity(), "Los Angeles");

    customer.setCountry("USA");
    EXPECT_EQ(customer.getCountry(), "USA");

    customer.setIsActive(false);
    EXPECT_FALSE(customer.getIsActive());
}

// Validation Tests
TEST_F(CustomerTest, ValidCustomer)
{
    EXPECT_TRUE(validCustomer.isValid());
}

TEST_F(CustomerTest, InvalidCustomerEmptyName)
{
    Customer customer = validCustomer;
    customer.setName("");
    EXPECT_FALSE(customer.isValid());
}

TEST_F(CustomerTest, InvalidCustomerEmptyEmail)
{
    Customer customer = validCustomer;
    customer.setEmail("");
    EXPECT_FALSE(customer.isValid());
}

TEST_F(CustomerTest, InvalidCustomerBadEmailFormat)
{
    Customer customer = validCustomer;
    customer.setEmail("invalid-email");
    EXPECT_FALSE(customer.isValid());
}

TEST_F(CustomerTest, ValidEmailFormats)
{
    Customer customer = validCustomer;

    customer.setEmail("user@domain.com");
    EXPECT_TRUE(customer.isValid());

    customer.setEmail("test.email@example.org");
    EXPECT_TRUE(customer.isValid());

    customer.setEmail("user+tag@domain.co.uk");
    EXPECT_TRUE(customer.isValid());
}

// ToString Tests
TEST_F(CustomerTest, ToStringContainsCustomerInfo)
{
    std::string result = validCustomer.toString();

    EXPECT_NE(result.find("John Doe"), std::string::npos);
    EXPECT_NE(result.find("john.doe@email.com"), std::string::npos);
    EXPECT_NE(result.find("+1234567890"), std::string::npos);
    EXPECT_NE(result.find("New York"), std::string::npos);
    EXPECT_NE(result.find("USA"), std::string::npos);
}

// Serialization Tests
TEST_F(CustomerTest, SerializationAndDeserialization)
{
    std::string serialized = validCustomer.serialize();
    EXPECT_FALSE(serialized.empty());

    Customer deserialized = Customer::deserialize(serialized);

    EXPECT_EQ(deserialized.getCustomerId(), validCustomer.getCustomerId());
    EXPECT_EQ(deserialized.getName(), validCustomer.getName());
    EXPECT_EQ(deserialized.getEmail(), validCustomer.getEmail());
    EXPECT_EQ(deserialized.getPhone(), validCustomer.getPhone());
    EXPECT_EQ(deserialized.getAddress(), validCustomer.getAddress());
    EXPECT_EQ(deserialized.getCity(), validCustomer.getCity());
    EXPECT_EQ(deserialized.getCountry(), validCustomer.getCountry());
    EXPECT_EQ(deserialized.getIsActive(), validCustomer.getIsActive());
}

TEST_F(CustomerTest, SerializationRoundTrip)
{
    // Test multiple serialization/deserialization cycles
    Customer original = validCustomer;

    for (int i = 0; i < 3; ++i)
    {
        std::string serialized = original.serialize();
        original = Customer::deserialize(serialized);
    }

    EXPECT_EQ(original.getCustomerId(), validCustomer.getCustomerId());
    EXPECT_EQ(original.getName(), validCustomer.getName());
    EXPECT_EQ(original.getEmail(), validCustomer.getEmail());
}

// Edge Cases
TEST_F(CustomerTest, CustomerWithSpecialCharacters)
{
    Customer customer(2, "José María", "jose@email.com", "+34-123-456-789",
                      "Calle 123, Apt. 4B", "São Paulo", "Brazil");

    EXPECT_TRUE(customer.isValid());

    std::string serialized = customer.serialize();
    Customer deserialized = Customer::deserialize(serialized);

    EXPECT_EQ(deserialized.getName(), "José María");
    EXPECT_EQ(deserialized.getCity(), "São Paulo");
}

TEST_F(CustomerTest, CustomerWithLongStrings)
{
    std::string longName(100, 'A');
    std::string longAddress(200, 'B');

    Customer customer(3, longName, "long@email.com", "+1234567890",
                      longAddress, "City", "Country");

    EXPECT_TRUE(customer.isValid());
    EXPECT_EQ(customer.getName(), longName);
    EXPECT_EQ(customer.getAddress(), longAddress);
}

TEST_F(CustomerTest, InactiveCustomer)
{
    Customer customer = validCustomer;
    customer.setIsActive(false);

    EXPECT_FALSE(customer.getIsActive());
    EXPECT_TRUE(customer.isValid()); // Inactive customers should still be valid
}