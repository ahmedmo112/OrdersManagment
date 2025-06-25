#include <gtest/gtest.h>
#include "managers/OrderManager.h"
#include "managers/ProductManager.h"
#include "managers/CustomerManager.h"
#include "models/Order.h"
#include "models/Product.h"
#include "models/Customer.h"

class OrderManagerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        productManager = std::make_unique<ProductManager>();
        customerManager = std::make_unique<CustomerManager>();
        orderManager = std::make_unique<OrderManager>(productManager.get(), customerManager.get());

        // Create test customers
        customer1 = Customer(1, "John Doe", "john@email.com", "+1234567890",
                             "123 Main St", "New York", "USA");
        customer2 = Customer(2, "Jane Smith", "jane@email.com", "+1987654321",
                             "456 Oak Ave", "Los Angeles", "USA");

        // Create test products
        product1 = Product(1, "Laptop", "High-performance laptop",
                           "Electronics", 999.99, 50, 10);
        product2 = Product(2, "Mouse", "Wireless mouse",
                           "Electronics", 29.99, 100, 5);
        product3 = Product(3, "Keyboard", "Mechanical keyboard",
                           "Electronics", 79.99, 75, 8);

        // Add customers and products to managers
        customerManager->addCustomer(customer1);
        customerManager->addCustomer(customer2);
        productManager->addProduct(product1);
        productManager->addProduct(product2);
        productManager->addProduct(product3);
    }

    void TearDown() override
    {
        orderManager.reset();
        productManager.reset();
        customerManager.reset();
    }

    std::unique_ptr<OrderManager> orderManager;
    std::unique_ptr<ProductManager> productManager;
    std::unique_ptr<CustomerManager> customerManager;
    Customer customer1, customer2;
    Product product1, product2, product3;
};

// CRUD Operations Tests
TEST_F(OrderManagerTest, CreateOrder)
{
    EXPECT_TRUE(orderManager->createOrder(customer1.getCustomerId()));
    EXPECT_EQ(orderManager->getTotalOrders(), 1);

    EXPECT_TRUE(orderManager->createOrder(customer2.getCustomerId()));
    EXPECT_EQ(orderManager->getTotalOrders(), 2);
}

TEST_F(OrderManagerTest, CreateOrderInvalidCustomer)
{
    EXPECT_FALSE(orderManager->createOrder(999)); // Non-existent customer
    EXPECT_EQ(orderManager->getTotalOrders(), 0);
}

TEST_F(OrderManagerTest, GetOrder)
{
    orderManager->createOrder(customer1.getCustomerId());

    // Assuming the first order gets ID 1
    Order *found = orderManager->getOrder(1);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getCustomerId(), customer1.getCustomerId());

    Order *notFound = orderManager->getOrder(999);
    EXPECT_EQ(notFound, nullptr);
}

TEST_F(OrderManagerTest, GetAllOrders)
{
    std::vector<Order> orders = orderManager->getAllOrders();
    EXPECT_TRUE(orders.empty());

    orderManager->createOrder(customer1.getCustomerId());
    orderManager->createOrder(customer2.getCustomerId());

    orders = orderManager->getAllOrders();
    EXPECT_EQ(orders.size(), 2);
}

TEST_F(OrderManagerTest, UpdateOrder)
{
    orderManager->createOrder(customer1.getCustomerId());

    Order *order = orderManager->getOrder(1);
    ASSERT_NE(order, nullptr);

    order->setNotes("Updated notes");
    order->setShippingAddress("Updated address");

    EXPECT_TRUE(orderManager->updateOrder(*order));

    Order *updated = orderManager->getOrder(1);
    ASSERT_NE(updated, nullptr);
    EXPECT_EQ(updated->getNotes(), "Updated notes");
    EXPECT_EQ(updated->getShippingAddress(), "Updated address");
}

TEST_F(OrderManagerTest, DeleteOrder)
{
    orderManager->createOrder(customer1.getCustomerId());
    orderManager->createOrder(customer2.getCustomerId());

    EXPECT_EQ(orderManager->getTotalOrders(), 2);

    EXPECT_TRUE(orderManager->deleteOrder(1));
    EXPECT_EQ(orderManager->getTotalOrders(), 1);

    Order *deleted = orderManager->getOrder(1);
    EXPECT_EQ(deleted, nullptr);
}

// Order Item Management Tests
TEST_F(OrderManagerTest, AddItemToOrder)
{
    orderManager->createOrder(customer1.getCustomerId());

    EXPECT_TRUE(orderManager->addItemToOrder(1, product1.getProductId(), 2));

    Order *order = orderManager->getOrder(1);
    ASSERT_NE(order, nullptr);
    EXPECT_EQ(order->getItems().size(), 1);
    EXPECT_EQ(order->getItems()[0].productId, product1.getProductId());
    EXPECT_EQ(order->getItems()[0].quantity, 2);
}

TEST_F(OrderManagerTest, AddItemInvalidOrder)
{
    EXPECT_FALSE(orderManager->addItemToOrder(999, product1.getProductId(), 1));
}

TEST_F(OrderManagerTest, AddItemInvalidProduct)
{
    orderManager->createOrder(customer1.getCustomerId());

    EXPECT_FALSE(orderManager->addItemToOrder(1, 999, 1)); // Non-existent product
}

TEST_F(OrderManagerTest, AddItemInsufficientStock)
{
    orderManager->createOrder(customer1.getCustomerId());

    // Try to order more than available stock
    EXPECT_FALSE(orderManager->addItemToOrder(1, product1.getProductId(), 100));

    Order *order = orderManager->getOrder(1);
    ASSERT_NE(order, nullptr);
    EXPECT_TRUE(order->getItems().empty());
}

TEST_F(OrderManagerTest, RemoveItemFromOrder)
{
    orderManager->createOrder(customer1.getCustomerId());
    orderManager->addItemToOrder(1, product1.getProductId(), 2);
    orderManager->addItemToOrder(1, product2.getProductId(), 1);

    Order *order = orderManager->getOrder(1);
    ASSERT_NE(order, nullptr);
    EXPECT_EQ(order->getItems().size(), 2);

    EXPECT_TRUE(orderManager->removeItemFromOrder(1, product1.getProductId()));

    order = orderManager->getOrder(1);
    ASSERT_NE(order, nullptr);
    EXPECT_EQ(order->getItems().size(), 1);
    EXPECT_EQ(order->getItems()[0].productId, product2.getProductId());
}

TEST_F(OrderManagerTest, UpdateOrderItemQuantity)
{
    orderManager->createOrder(customer1.getCustomerId());
    orderManager->addItemToOrder(1, product1.getProductId(), 2);

    EXPECT_TRUE(orderManager->updateOrderItemQuantity(1, product1.getProductId(), 5));

    Order *order = orderManager->getOrder(1);
    ASSERT_NE(order, nullptr);
    EXPECT_EQ(order->getItems()[0].quantity, 5);
}

TEST_F(OrderManagerTest, UpdateOrderItemQuantityInsufficientStock)
{
    orderManager->createOrder(customer1.getCustomerId());
    orderManager->addItemToOrder(1, product1.getProductId(), 2);

    EXPECT_FALSE(orderManager->updateOrderItemQuantity(1, product1.getProductId(), 100));

    Order *order = orderManager->getOrder(1);
    ASSERT_NE(order, nullptr);
    EXPECT_EQ(order->getItems()[0].quantity, 2); // Should remain unchanged
}

// Order Status Management Tests
TEST_F(OrderManagerTest, UpdateOrderStatus)
{
    orderManager->createOrder(customer1.getCustomerId());
    orderManager->addItemToOrder(1, product1.getProductId(), 1);

    EXPECT_TRUE(orderManager->updateOrderStatus(1, OrderStatus::CONFIRMED));

    Order *order = orderManager->getOrder(1);
    ASSERT_NE(order, nullptr);
    EXPECT_EQ(order->getStatus(), OrderStatus::CONFIRMED);
}

TEST_F(OrderManagerTest, UpdateOrderStatusInvalidTransition)
{
    orderManager->createOrder(customer1.getCustomerId());
    orderManager->addItemToOrder(1, product1.getProductId(), 1);

    // Try to go directly to DELIVERED from PENDING
    EXPECT_FALSE(orderManager->updateOrderStatus(1, OrderStatus::DELIVERED));

    Order *order = orderManager->getOrder(1);
    ASSERT_NE(order, nullptr);
    EXPECT_EQ(order->getStatus(), OrderStatus::PENDING); // Should remain unchanged
}

TEST_F(OrderManagerTest, ConfirmOrder)
{
    orderManager->createOrder(customer1.getCustomerId());
    orderManager->addItemToOrder(1, product1.getProductId(), 1);

    EXPECT_TRUE(orderManager->confirmOrder(1));

    Order *order = orderManager->getOrder(1);
    ASSERT_NE(order, nullptr);
    EXPECT_EQ(order->getStatus(), OrderStatus::CONFIRMED);
}

TEST_F(OrderManagerTest, ProcessOrder)
{
    orderManager->createOrder(customer1.getCustomerId());
    orderManager->addItemToOrder(1, product1.getProductId(), 1);
    orderManager->confirmOrder(1);

    EXPECT_TRUE(orderManager->processOrder(1));

    Order *order = orderManager->getOrder(1);
    ASSERT_NE(order, nullptr);
    EXPECT_EQ(order->getStatus(), OrderStatus::PROCESSING);
}

TEST_F(OrderManagerTest, ShipOrder)
{
    orderManager->createOrder(customer1.getCustomerId());
    orderManager->addItemToOrder(1, product1.getProductId(), 1);
    orderManager->confirmOrder(1);
    orderManager->processOrder(1);

    EXPECT_TRUE(orderManager->shipOrder(1));

    Order *order = orderManager->getOrder(1);
    ASSERT_NE(order, nullptr);
    EXPECT_EQ(order->getStatus(), OrderStatus::SHIPPED);
}

TEST_F(OrderManagerTest, DeliverOrder)
{
    orderManager->createOrder(customer1.getCustomerId());
    orderManager->addItemToOrder(1, product1.getProductId(), 1);
    orderManager->confirmOrder(1);
    orderManager->processOrder(1);
    orderManager->shipOrder(1);

    EXPECT_TRUE(orderManager->deliverOrder(1));

    Order *order = orderManager->getOrder(1);
    ASSERT_NE(order, nullptr);
    EXPECT_EQ(order->getStatus(), OrderStatus::DELIVERED);
}

TEST_F(OrderManagerTest, CancelOrder)
{
    orderManager->createOrder(customer1.getCustomerId());
    orderManager->addItemToOrder(1, product1.getProductId(), 1);

    EXPECT_TRUE(orderManager->cancelOrder(1));

    Order *order = orderManager->getOrder(1);
    ASSERT_NE(order, nullptr);
    EXPECT_EQ(order->getStatus(), OrderStatus::CANCELLED);
}

TEST_F(OrderManagerTest, CancelOrderAfterShipped)
{
    orderManager->createOrder(customer1.getCustomerId());
    orderManager->addItemToOrder(1, product1.getProductId(), 1);
    orderManager->confirmOrder(1);
    orderManager->processOrder(1);
    orderManager->shipOrder(1);

    // Cannot cancel after shipped
    EXPECT_FALSE(orderManager->cancelOrder(1));

    Order *order = orderManager->getOrder(1);
    ASSERT_NE(order, nullptr);
    EXPECT_EQ(order->getStatus(), OrderStatus::SHIPPED); // Should remain unchanged
}

// Search and Filter Tests
TEST_F(OrderManagerTest, GetOrdersByCustomer)
{
    orderManager->createOrder(customer1.getCustomerId());
    orderManager->createOrder(customer1.getCustomerId());
    orderManager->createOrder(customer2.getCustomerId());

    std::vector<Order> customer1Orders = orderManager->getOrdersByCustomer(customer1.getCustomerId());
    EXPECT_EQ(customer1Orders.size(), 2);

    std::vector<Order> customer2Orders = orderManager->getOrdersByCustomer(customer2.getCustomerId());
    EXPECT_EQ(customer2Orders.size(), 1);
}

TEST_F(OrderManagerTest, GetOrdersByStatus)
{
    orderManager->createOrder(customer1.getCustomerId());
    orderManager->addItemToOrder(1, product1.getProductId(), 1);

    orderManager->createOrder(customer2.getCustomerId());
    orderManager->addItemToOrder(2, product2.getProductId(), 1);
    orderManager->confirmOrder(2);

    std::vector<Order> pendingOrders = orderManager->getOrdersByStatus(OrderStatus::PENDING);
    EXPECT_EQ(pendingOrders.size(), 1);

    std::vector<Order> confirmedOrders = orderManager->getOrdersByStatus(OrderStatus::CONFIRMED);
    EXPECT_EQ(confirmedOrders.size(), 1);
}

// Financial Operations Tests
TEST_F(OrderManagerTest, ApplyDiscount)
{
    orderManager->createOrder(customer1.getCustomerId());
    orderManager->addItemToOrder(1, product1.getProductId(), 1); // 999.99

    EXPECT_TRUE(orderManager->applyDiscount(1, 10.0)); // 10% discount

    Order *order = orderManager->getOrder(1);
    ASSERT_NE(order, nullptr);
    EXPECT_DOUBLE_EQ(order->getDiscountAmount(), 99.999); // 10% of 999.99
}

TEST_F(OrderManagerTest, ApplyFixedDiscount)
{
    orderManager->createOrder(customer1.getCustomerId());
    orderManager->addItemToOrder(1, product1.getProductId(), 1); // 999.99

    EXPECT_TRUE(orderManager->applyFixedDiscount(1, 50.0));

    Order *order = orderManager->getOrder(1);
    ASSERT_NE(order, nullptr);
    EXPECT_DOUBLE_EQ(order->getDiscountAmount(), 50.0);
}

TEST_F(OrderManagerTest, CalculateOrderTotal)
{
    orderManager->createOrder(customer1.getCustomerId());
    orderManager->addItemToOrder(1, product1.getProductId(), 2); // 999.99 * 2
    orderManager->addItemToOrder(1, product2.getProductId(), 3); // 29.99 * 3

    double total = orderManager->calculateOrderTotal(1);
    double expectedTotal = (999.99 * 2) + (29.99 * 3);
    EXPECT_DOUBLE_EQ(total, expectedTotal);
}

// Validation Tests
TEST_F(OrderManagerTest, CanFulfillOrder)
{
    orderManager->createOrder(customer1.getCustomerId());
    orderManager->addItemToOrder(1, product1.getProductId(), 10); // Within stock

    EXPECT_TRUE(orderManager->canFulfillOrder(1));

    orderManager->addItemToOrder(1, product2.getProductId(), 200); // Exceeds stock
    EXPECT_FALSE(orderManager->canFulfillOrder(1));
}

TEST_F(OrderManagerTest, CheckProductAvailability)
{
    EXPECT_TRUE(orderManager->checkProductAvailability(product1.getProductId(), 10));
    EXPECT_TRUE(orderManager->checkProductAvailability(product1.getProductId(), 50));
    EXPECT_FALSE(orderManager->checkProductAvailability(product1.getProductId(), 51));
    EXPECT_FALSE(orderManager->checkProductAvailability(999, 1)); // Non-existent product
}

// Statistics Tests
TEST_F(OrderManagerTest, GetTotalOrders)
{
    EXPECT_EQ(orderManager->getTotalOrders(), 0);

    orderManager->createOrder(customer1.getCustomerId());
    EXPECT_EQ(orderManager->getTotalOrders(), 1);

    orderManager->createOrder(customer2.getCustomerId());
    EXPECT_EQ(orderManager->getTotalOrders(), 2);

    orderManager->deleteOrder(1);
    EXPECT_EQ(orderManager->getTotalOrders(), 1);
}

TEST_F(OrderManagerTest, GetOrdersByStatusCount)
{
    orderManager->createOrder(customer1.getCustomerId());
    orderManager->addItemToOrder(1, product1.getProductId(), 1);

    orderManager->createOrder(customer2.getCustomerId());
    orderManager->addItemToOrder(2, product2.getProductId(), 1);
    orderManager->confirmOrder(2);

    EXPECT_EQ(orderManager->getOrdersByStatusCount(OrderStatus::PENDING), 1);
    EXPECT_EQ(orderManager->getOrdersByStatusCount(OrderStatus::CONFIRMED), 1);
    EXPECT_EQ(orderManager->getOrdersByStatusCount(OrderStatus::CANCELLED), 0);
}

TEST_F(OrderManagerTest, GetOrderStatusDistribution)
{
    orderManager->createOrder(customer1.getCustomerId());
    orderManager->addItemToOrder(1, product1.getProductId(), 1);

    orderManager->createOrder(customer2.getCustomerId());
    orderManager->addItemToOrder(2, product2.getProductId(), 1);
    orderManager->confirmOrder(2);

    std::map<OrderStatus, int> distribution = orderManager->getOrderStatusDistribution();

    EXPECT_EQ(distribution[OrderStatus::PENDING], 1);
    EXPECT_EQ(distribution[OrderStatus::CONFIRMED], 1);
    EXPECT_EQ(distribution[OrderStatus::PROCESSING], 0);
}

TEST_F(OrderManagerTest, GetTotalRevenue)
{
    orderManager->createOrder(customer1.getCustomerId());
    orderManager->addItemToOrder(1, product1.getProductId(), 1); // 999.99
    orderManager->confirmOrder(1);

    orderManager->createOrder(customer2.getCustomerId());
    orderManager->addItemToOrder(2, product2.getProductId(), 2); // 29.99 * 2
    orderManager->confirmOrder(2);

    double expectedRevenue = 999.99 + (29.99 * 2);
    EXPECT_DOUBLE_EQ(orderManager->getTotalRevenue(), expectedRevenue);
}

// Edge Cases
TEST_F(OrderManagerTest, EmptyOrder)
{
    orderManager->createOrder(customer1.getCustomerId());

    // Try to confirm empty order
    EXPECT_FALSE(orderManager->confirmOrder(1));

    Order *order = orderManager->getOrder(1);
    ASSERT_NE(order, nullptr);
    EXPECT_EQ(order->getStatus(), OrderStatus::PENDING);
}

TEST_F(OrderManagerTest, AddDuplicateItem)
{
    orderManager->createOrder(customer1.getCustomerId());
    orderManager->addItemToOrder(1, product1.getProductId(), 1);

    // Add same product again - should update quantity
    orderManager->addItemToOrder(1, product1.getProductId(), 2);

    Order *order = orderManager->getOrder(1);
    ASSERT_NE(order, nullptr);
    EXPECT_EQ(order->getItems().size(), 1);      // Still one item
    EXPECT_EQ(order->getItems()[0].quantity, 3); // Quantity should be updated to 3
}

TEST_F(OrderManagerTest, OrderWithoutDependencies)
{
    // Test with null product and customer managers
    OrderManager standaloneManager;

    EXPECT_FALSE(standaloneManager.createOrder(1));
    EXPECT_FALSE(standaloneManager.addItemToOrder(1, 1, 1));
}

TEST_F(OrderManagerTest, LargeOrderQuantities)
{
    orderManager->createOrder(customer1.getCustomerId());

    // Add large quantities
    EXPECT_TRUE(orderManager->addItemToOrder(1, product2.getProductId(), 50)); // Half the stock

    Order *order = orderManager->getOrder(1);
    ASSERT_NE(order, nullptr);
    EXPECT_EQ(order->getItems()[0].quantity, 50);

    // Check that stock is properly reserved/checked
    EXPECT_FALSE(orderManager->addItemToOrder(1, product2.getProductId(), 60)); // Would exceed total stock
}