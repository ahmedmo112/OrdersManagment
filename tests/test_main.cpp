#include <gtest/gtest.h>
#include "managers/CustomerManager.h"
#include "managers/ProductManager.h"
#include "managers/OrderManager.h"
#include "managers/UserManager.h"
#include "utils/Database.h"
#include "utils/Logger.h"
#include "models/Customer.h"
#include "models/Product.h"
#include "models/Order.h"
#include "models/User.h"

// Integration Tests
class IntegrationTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Initialize managers
        customerManager = std::make_unique<CustomerManager>();
        productManager = std::make_unique<ProductManager>();
        userManager = std::make_unique<UserManager>();
        orderManager = std::make_unique<OrderManager>(productManager.get(), customerManager.get());

        // Create test data
        SetupTestData();
    }

    void TearDown() override
    {
        orderManager.reset();
        userManager.reset();
        productManager.reset();
        customerManager.reset();
    }

    void SetupTestData()
    {
        // Create test users
        User admin(1, "admin", "admin123", "Administrator", "admin@company.com", UserRole::ADMIN);
        User manager(2, "manager", "manager123", "Manager User", "manager@company.com", UserRole::MANAGER);
        User employee(3, "employee", "emp123", "Employee User", "employee@company.com", UserRole::EMPLOYEE);

        userManager->addUser(admin);
        userManager->addUser(manager);
        userManager->addUser(employee);

        // Create test customers
        Customer customer1(1, "John Doe", "john@email.com", "+1234567890",
                           "123 Main St", "New York", "USA");
        Customer customer2(2, "Jane Smith", "jane@email.com", "+1987654321",
                           "456 Oak Ave", "Los Angeles", "USA");

        customerManager->addCustomer(customer1);
        customerManager->addCustomer(customer2);

        // Create test products
        Product laptop(1, "Laptop", "High-performance laptop", "Electronics", 999.99, 50, 10);
        Product mouse(2, "Mouse", "Wireless mouse", "Electronics", 29.99, 100, 5);
        Product keyboard(3, "Keyboard", "Mechanical keyboard", "Electronics", 79.99, 75, 8);

        productManager->addProduct(laptop);
        productManager->addProduct(mouse);
        productManager->addProduct(keyboard);
    }

    std::unique_ptr<CustomerManager> customerManager;
    std::unique_ptr<ProductManager> productManager;
    std::unique_ptr<OrderManager> orderManager;
    std::unique_ptr<UserManager> userManager;
};

// Full Order Lifecycle Test
TEST_F(IntegrationTest, CompleteOrderLifecycle)
{
    // Create an order
    EXPECT_TRUE(orderManager->createOrder(1)); // Customer ID 1 (John Doe)

    // Add items to the order
    EXPECT_TRUE(orderManager->addItemToOrder(1, 1, 2)); // 2 Laptops
    EXPECT_TRUE(orderManager->addItemToOrder(1, 2, 1)); // 1 Mouse

    // Calculate and verify totals
    double expectedTotal = (999.99 * 2) + (29.99 * 1); // 2029.97
    double actualTotal = orderManager->calculateOrderTotal(1);
    EXPECT_DOUBLE_EQ(actualTotal, expectedTotal);

    // Apply discount
    EXPECT_TRUE(orderManager->applyDiscount(1, 10.0)); // 10% discount

    Order *order = orderManager->getOrder(1);
    ASSERT_NE(order, nullptr);
    EXPECT_DOUBLE_EQ(order->getDiscountAmount(), expectedTotal * 0.1);

    // Progress through order statuses
    EXPECT_TRUE(orderManager->confirmOrder(1));
    EXPECT_EQ(order->getStatus(), OrderStatus::CONFIRMED);

    EXPECT_TRUE(orderManager->processOrder(1));
    EXPECT_EQ(order->getStatus(), OrderStatus::PROCESSING);

    EXPECT_TRUE(orderManager->shipOrder(1));
    EXPECT_EQ(order->getStatus(), OrderStatus::SHIPPED);

    EXPECT_TRUE(orderManager->deliverOrder(1));
    EXPECT_EQ(order->getStatus(), OrderStatus::DELIVERED);

    // Verify stock was reduced
    Product *laptop = productManager->getProduct(1);
    Product *mouse = productManager->getProduct(2);
    ASSERT_NE(laptop, nullptr);
    ASSERT_NE(mouse, nullptr);
    EXPECT_EQ(laptop->getStockQuantity(), 48); // 50 - 2
    EXPECT_EQ(mouse->getStockQuantity(), 99);  // 100 - 1
}

// User Authentication and Authorization Test
TEST_F(IntegrationTest, UserAuthenticationAndAuthorization)
{
    // Test user authentication
    User *admin = userManager->authenticateUser("admin", "admin123");
    ASSERT_NE(admin, nullptr);
    EXPECT_EQ(admin->getRole(), UserRole::ADMIN);

    User *manager = userManager->authenticateUser("manager", "manager123");
    ASSERT_NE(manager, nullptr);
    EXPECT_EQ(manager->getRole(), UserRole::MANAGER);

    // Test failed authentication
    User *failed = userManager->authenticateUser("admin", "wrongpassword");
    EXPECT_EQ(failed, nullptr);

    // Test authorization
    EXPECT_TRUE(admin->canManageUsers());
    EXPECT_TRUE(admin->canManageProducts());
    EXPECT_TRUE(admin->canManageOrders());
    EXPECT_TRUE(admin->canViewReports());

    EXPECT_FALSE(manager->canManageUsers());
    EXPECT_TRUE(manager->canManageProducts());
    EXPECT_TRUE(manager->canManageOrders());
    EXPECT_TRUE(manager->canViewReports());
}

// Stock Management Integration Test
TEST_F(IntegrationTest, StockManagementIntegration)
{
    // Check initial stock
    EXPECT_TRUE(productManager->isProductAvailable(1, 10)); // Laptop
    EXPECT_TRUE(productManager->isProductAvailable(2, 50)); // Mouse

    // Create multiple orders that consume stock
    orderManager->createOrder(1);
    orderManager->addItemToOrder(1, 1, 10); // 10 Laptops

    orderManager->createOrder(2);
    orderManager->addItemToOrder(2, 1, 5);  // 5 more Laptops
    orderManager->addItemToOrder(2, 2, 30); // 30 Mice

    // Check availability after orders
    EXPECT_TRUE(productManager->isProductAvailable(1, 35));  // 50 - 15 = 35 remaining
    EXPECT_FALSE(productManager->isProductAvailable(1, 36)); // Should not be available
    EXPECT_TRUE(productManager->isProductAvailable(2, 70));  // 100 - 30 = 70 remaining

    // Test low stock detection
    productManager->updateStock(3, 5); // Set keyboard stock to 5 (below min of 8)
    std::vector<Product> lowStockProducts = productManager->getLowStockProducts();
    EXPECT_GE(lowStockProducts.size(), 1);

    // Find keyboard in low stock list
    bool keyboardFoundInLowStock = false;
    for (const auto &product : lowStockProducts)
    {
        if (product.getProductId() == 3)
        {
            keyboardFoundInLowStock = true;
            break;
        }
    }
    EXPECT_TRUE(keyboardFoundInLowStock);
}

// Customer and Order Relationship Test
TEST_F(IntegrationTest, CustomerOrderRelationship)
{
    // Create orders for different customers
    orderManager->createOrder(1); // John Doe
    orderManager->addItemToOrder(1, 1, 1);

    orderManager->createOrder(1); // John Doe again
    orderManager->addItemToOrder(2, 2, 2);

    orderManager->createOrder(2); // Jane Smith
    orderManager->addItemToOrder(3, 3, 1);

    // Test customer order retrieval
    std::vector<Order> johnOrders = orderManager->getOrdersByCustomer(1);
    EXPECT_EQ(johnOrders.size(), 2);

    std::vector<Order> janeOrders = orderManager->getOrdersByCustomer(2);
    EXPECT_EQ(janeOrders.size(), 1);

    // Test customer search and validation
    std::vector<Customer> customers = customerManager->searchByName("John");
    EXPECT_EQ(customers.size(), 1);
    EXPECT_EQ(customers[0].getName(), "John Doe");

    // Test email uniqueness
    EXPECT_FALSE(customerManager->isEmailUnique("john@email.com"));
    EXPECT_TRUE(customerManager->isEmailUnique("new@email.com"));
}

// Data Consistency Test
TEST_F(IntegrationTest, DataConsistencyValidation)
{
    // Test product name uniqueness
    Product duplicateProduct(4, "Laptop", "Another laptop", "Electronics", 1200.0, 30, 5);
    EXPECT_FALSE(productManager->addProduct(duplicateProduct));

    // Test customer email uniqueness
    Customer duplicateCustomer(3, "Bob Johnson", "john@email.com", "+1555666777",
                               "789 Pine Rd", "Chicago", "USA");
    EXPECT_FALSE(customerManager->addCustomer(duplicateCustomer));

    // Test order validation
    orderManager->createOrder(1);

    // Cannot confirm empty order
    EXPECT_FALSE(orderManager->confirmOrder(1));

    // Add item and confirm
    orderManager->addItemToOrder(1, 1, 1);
    EXPECT_TRUE(orderManager->confirmOrder(1));

    // Cannot add items to confirmed order
    EXPECT_FALSE(orderManager->addItemToOrder(1, 2, 1));
}

// Performance Test with Larger Dataset
TEST_F(IntegrationTest, PerformanceWithLargeDataset)
{
    auto start = std::chrono::high_resolution_clock::now();

    // Add 100 customers
    for (int i = 10; i < 110; ++i)
    {
        Customer customer(i, "Customer " + std::to_string(i),
                          "customer" + std::to_string(i) + "@email.com",
                          "+1555000" + std::to_string(i),
                          "Address " + std::to_string(i),
                          "City " + std::to_string(i % 10),
                          "Country " + std::to_string(i % 5));
        customerManager->addCustomer(customer);
    }

    // Add 50 products
    for (int i = 10; i < 60; ++i)
    {
        Product product(i, "Product " + std::to_string(i),
                        "Description " + std::to_string(i),
                        "Category " + std::to_string(i % 5),
                        10.0 + (i * 5.0), 100, 10);
        productManager->addProduct(product);
    }

    // Create 20 orders
    for (int i = 1; i <= 20; ++i)
    {
        int customerId = 10 + (i % 100); // Random customer
        orderManager->createOrder(customerId);

        // Add 1-3 items per order
        for (int j = 1; j <= (i % 3) + 1; ++j)
        {
            int productId = 10 + (j % 50); // Random product
            orderManager->addItemToOrder(i, productId, j);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Verify data was created
    EXPECT_EQ(customerManager->getTotalCustomers(), 102); // 2 original + 100 new
    EXPECT_EQ(productManager->getTotalProducts(), 53);    // 3 original + 50 new
    EXPECT_EQ(orderManager->getTotalOrders(), 20);

    // Performance should be reasonable (adjust threshold as needed)
    EXPECT_LT(duration.count(), 1000); // Should complete in less than 1 second
}

// Error Handling Integration Test
TEST_F(IntegrationTest, ErrorHandlingIntegration)
{
    // Test cascade of errors

    // 1. Try to create order for non-existent customer
    EXPECT_FALSE(orderManager->createOrder(999));

    // 2. Try to add non-existent product to order
    orderManager->createOrder(1);
    EXPECT_FALSE(orderManager->addItemToOrder(1, 999, 1));

    // 3. Try to add more items than available stock
    EXPECT_FALSE(orderManager->addItemToOrder(1, 1, 100)); // Only 50 laptops

    // 4. Try invalid status transitions
    orderManager->addItemToOrder(1, 1, 1);
    EXPECT_FALSE(orderManager->updateOrderStatus(1, OrderStatus::DELIVERED)); // Can't skip steps

    // 5. Test data validation cascades
    Customer invalidCustomer(4, "", "invalid-email", "", "", "", "");
    EXPECT_FALSE(customerManager->addCustomer(invalidCustomer));

    Product invalidProduct(4, "", "", "", -100.0, -5, -1);
    EXPECT_FALSE(productManager->addProduct(invalidProduct));
}

// Main function for running tests
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    // Set up test environment
    std::cout << "Starting Order Management System Tests..." << std::endl;

    // Initialize logging for tests
    Logger &logger = Logger::getInstance();
    logger.initialize("test_logs/test.log", LogLevel::DEBUG);

    int result = RUN_ALL_TESTS();

    logger.close();

    if (result == 0)
    {
        std::cout << "All tests passed successfully!" << std::endl;
    }
    else
    {
        std::cout << "Some tests failed. Check the output above for details." << std::endl;
    }

    return result;
}