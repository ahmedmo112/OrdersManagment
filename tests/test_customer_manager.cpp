#include <gtest/gtest.h>
#include "managers/CustomerManager.h"
#include "models/Customer.h"

class CustomerManagerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        customerManager = std::make_unique<CustomerManager>();

        // Create test customers
        customer1 = Customer(1, "John Doe", "john.doe@email.com",
                             "+1234567890", "123 Main St", "New York", "USA");

        customer2 = Customer(2, "Jane Smith", "jane.smith@email.com",
                             "+1987654321", "456 Oak Ave", "Los Angeles", "USA");

        customer3 = Customer(3, "Bob Johnson", "bob.johnson@email.com",
                             "+1555666777", "789 Pine Rd", "Chicago", "USA");

        customer4 = Customer(4, "Alice Brown", "alice.brown@email.com",
                             "+1444555666", "321 Elm St", "New York", "USA");
    }

    void TearDown() override
    {
        customerManager.reset();
    }

    std::unique_ptr<CustomerManager> customerManager;
    Customer customer1, customer2, customer3, customer4;
};

// CRUD Operations Tests
TEST_F(CustomerManagerTest, AddCustomer)
{
    EXPECT_TRUE(customerManager->addCustomer(customer1));
    EXPECT_EQ(customerManager->getTotalCustomers(), 1);

    EXPECT_TRUE(customerManager->addCustomer(customer2));
    EXPECT_EQ(customerManager->getTotalCustomers(), 2);
}

TEST_F(CustomerManagerTest, GetCustomer)
{
    customerManager->addCustomer(customer1);

    Customer *found = customerManager->getCustomer(customer1.getCustomerId());
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getName(), customer1.getName());
    EXPECT_EQ(found->getEmail(), customer1.getEmail());

    Customer *notFound = customerManager->getCustomer(999);
    EXPECT_EQ(notFound, nullptr);
}

TEST_F(CustomerManagerTest, GetAllCustomers)
{
    std::vector<Customer> customers = customerManager->getAllCustomers();
    EXPECT_TRUE(customers.empty());

    customerManager->addCustomer(customer1);
    customerManager->addCustomer(customer2);

    customers = customerManager->getAllCustomers();
    EXPECT_EQ(customers.size(), 2);
}

TEST_F(CustomerManagerTest, UpdateCustomer)
{
    customerManager->addCustomer(customer1);

    Customer updated = customer1;
    updated.setName("Updated Name");
    updated.setCity("Updated City");

    EXPECT_TRUE(customerManager->updateCustomer(updated));

    Customer *found = customerManager->getCustomer(customer1.getCustomerId());
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getName(), "Updated Name");
    EXPECT_EQ(found->getCity(), "Updated City");
}

TEST_F(CustomerManagerTest, DeleteCustomer)
{
    customerManager->addCustomer(customer1);
    customerManager->addCustomer(customer2);

    EXPECT_EQ(customerManager->getTotalCustomers(), 2);

    EXPECT_TRUE(customerManager->deleteCustomer(customer1.getCustomerId()));
    EXPECT_EQ(customerManager->getTotalCustomers(), 1);

    Customer *deleted = customerManager->getCustomer(customer1.getCustomerId());
    EXPECT_EQ(deleted, nullptr);
}

// Search Tests
TEST_F(CustomerManagerTest, SearchByName)
{
    customerManager->addCustomer(customer1); // John Doe
    customerManager->addCustomer(customer2); // Jane Smith
    customerManager->addCustomer(customer3); // Bob Johnson

    std::vector<Customer> results = customerManager->searchByName("John");
    EXPECT_GE(results.size(), 1); // At least John Doe

    results = customerManager->searchByName("Jane");
    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].getName(), "Jane Smith");
}

TEST_F(CustomerManagerTest, GetCustomersByCity)
{
    customerManager->addCustomer(customer1); // New York
    customerManager->addCustomer(customer2); // Los Angeles
    customerManager->addCustomer(customer4); // New York

    std::vector<Customer> nyCustomers = customerManager->getCustomersByCity("New York");
    EXPECT_EQ(nyCustomers.size(), 2);

    std::vector<Customer> laCustomers = customerManager->getCustomersByCity("Los Angeles");
    EXPECT_EQ(laCustomers.size(), 1);
    EXPECT_EQ(laCustomers[0].getName(), "Jane Smith");
}

// Statistics Tests
TEST_F(CustomerManagerTest, GetTotalCustomers)
{
    EXPECT_EQ(customerManager->getTotalCustomers(), 0);

    customerManager->addCustomer(customer1);
    EXPECT_EQ(customerManager->getTotalCustomers(), 1);

    customerManager->addCustomer(customer2);
    EXPECT_EQ(customerManager->getTotalCustomers(), 2);

    customerManager->deleteCustomer(customer1.getCustomerId());
    EXPECT_EQ(customerManager->getTotalCustomers(), 1);
}