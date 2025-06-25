#include <gtest/gtest.h>
#include "models/Order.h"

class OrderTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        validOrder = Order(1, 100, "John Doe");
        emptyOrder = Order();

        // Create test items
        testItem1 = OrderItem(1, "Laptop", 2, 999.99);
        testItem2 = OrderItem(2, "Mouse", 1, 29.99);
        testItem3 = OrderItem(3, "Keyboard", 1, 79.99);
    }

    Order validOrder;
    Order emptyOrder;
    OrderItem testItem1;
    OrderItem testItem2;
    OrderItem testItem3;
};

// Constructor Tests
TEST_F(OrderTest, DefaultConstructor)
{
    Order order;
    EXPECT_EQ(order.getOrderId(), 0);
    EXPECT_EQ(order.getCustomerId(), 0);
    EXPECT_EQ(order.getCustomerName(), "");
    EXPECT_TRUE(order.getItems().empty());
    EXPECT_EQ(order.getStatus(), OrderStatus::PENDING);
    EXPECT_DOUBLE_EQ(order.getTotalAmount(), 0.0);
    EXPECT_DOUBLE_EQ(order.getDiscountAmount(), 0.0);
    EXPECT_DOUBLE_EQ(order.getFinalAmount(), 0.0);
}

TEST_F(OrderTest, ParameterizedConstructor)
{
    EXPECT_EQ(validOrder.getOrderId(), 1);
    EXPECT_EQ(validOrder.getCustomerId(), 100);
    EXPECT_EQ(validOrder.getCustomerName(), "John Doe");
    EXPECT_TRUE(validOrder.getItems().empty());
    EXPECT_EQ(validOrder.getStatus(), OrderStatus::PENDING);
    EXPECT_DOUBLE_EQ(validOrder.getTotalAmount(), 0.0);
}

// OrderItem Tests
TEST_F(OrderTest, OrderItemConstructor)
{
    EXPECT_EQ(testItem1.productId, 1);
    EXPECT_EQ(testItem1.productName, "Laptop");
    EXPECT_EQ(testItem1.quantity, 2);
    EXPECT_DOUBLE_EQ(testItem1.unitPrice, 999.99);
    EXPECT_DOUBLE_EQ(testItem1.totalPrice, 1999.98);
}

TEST_F(OrderTest, OrderItemTotalPriceCalculation)
{
    OrderItem item(5, "Test Product", 3, 15.50);
    EXPECT_DOUBLE_EQ(item.totalPrice, 46.50);
}

// Getter and Setter Tests
TEST_F(OrderTest, SettersAndGetters)
{
    Order order;

    order.setOrderId(500);
    EXPECT_EQ(order.getOrderId(), 500);

    order.setCustomerId(200);
    EXPECT_EQ(order.getCustomerId(), 200);

    order.setCustomerName("Jane Smith");
    EXPECT_EQ(order.getCustomerName(), "Jane Smith");

    order.setStatus(OrderStatus::CONFIRMED);
    EXPECT_EQ(order.getStatus(), OrderStatus::CONFIRMED);

    order.setShippingAddress("456 Oak St");
    EXPECT_EQ(order.getShippingAddress(), "456 Oak St");

    order.setDiscountAmount(50.0);
    EXPECT_DOUBLE_EQ(order.getDiscountAmount(), 50.0);

    order.setNotes("Test notes");
    EXPECT_EQ(order.getNotes(), "Test notes");
}

// Item Management Tests
TEST_F(OrderTest, AddItem)
{
    Order order = validOrder;

    order.addItem(testItem1);
    EXPECT_EQ(order.getItems().size(), 1);
    EXPECT_EQ(order.getItems()[0].productId, testItem1.productId);
    EXPECT_EQ(order.getItems()[0].productName, testItem1.productName);

    order.addItem(testItem2);
    EXPECT_EQ(order.getItems().size(), 2);
}

TEST_F(OrderTest, RemoveItem)
{
    Order order = validOrder;
    order.addItem(testItem1);
    order.addItem(testItem2);

    EXPECT_EQ(order.getItems().size(), 2);

    EXPECT_TRUE(order.removeItem(1)); // Remove laptop
    EXPECT_EQ(order.getItems().size(), 1);
    EXPECT_EQ(order.getItems()[0].productId, 2); // Mouse should remain

    EXPECT_FALSE(order.removeItem(999));   // Non-existent product
    EXPECT_EQ(order.getItems().size(), 1); // Size should remain same
}

TEST_F(OrderTest, UpdateItemQuantity)
{
    Order order = validOrder;
    order.addItem(testItem1);

    EXPECT_TRUE(order.updateItemQuantity(1, 5));
    EXPECT_EQ(order.getItems()[0].quantity, 5);
    EXPECT_DOUBLE_EQ(order.getItems()[0].totalPrice, 4999.95);

    EXPECT_FALSE(order.updateItemQuantity(999, 3)); // Non-existent product

    EXPECT_FALSE(order.updateItemQuantity(1, 0));  // Invalid quantity
    EXPECT_FALSE(order.updateItemQuantity(1, -1)); // Negative quantity
}

TEST_F(OrderTest, ClearItems)
{
    Order order = validOrder;
    order.addItem(testItem1);
    order.addItem(testItem2);

    EXPECT_EQ(order.getItems().size(), 2);

    order.clearItems();
    EXPECT_TRUE(order.getItems().empty());
    EXPECT_TRUE(order.isEmpty());
}

// Order Calculations Tests
TEST_F(OrderTest, CalculateTotalAmount)
{
    Order order = validOrder;
    order.addItem(testItem1); // 1999.98
    order.addItem(testItem2); // 29.99
    order.addItem(testItem3); // 79.99

    order.calculateTotalAmount();
    EXPECT_DOUBLE_EQ(order.getTotalAmount(), 2109.96);
}

TEST_F(OrderTest, CalculateFinalAmount)
{
    Order order = validOrder;
    order.addItem(testItem1);
    order.calculateTotalAmount();

    order.setDiscountAmount(100.0);
    order.calculateFinalAmount();

    EXPECT_DOUBLE_EQ(order.getFinalAmount(), order.getTotalAmount() - 100.0);
}

TEST_F(OrderTest, ApplyDiscount)
{
    Order order = validOrder;
    order.addItem(testItem1); // Total: 1999.98
    order.calculateTotalAmount();

    order.applyDiscount(10.0); // 10% discount
    EXPECT_DOUBLE_EQ(order.getDiscountAmount(), 199.998);
    EXPECT_DOUBLE_EQ(order.getFinalAmount(), 1799.982);
}

TEST_F(OrderTest, ApplyDiscountInvalidPercentage)
{
    Order order = validOrder;
    order.addItem(testItem1);
    order.calculateTotalAmount();

    double originalDiscount = order.getDiscountAmount();
    double originalFinal = order.getFinalAmount();

    order.applyDiscount(-5.0); // Negative discount
    EXPECT_DOUBLE_EQ(order.getDiscountAmount(), originalDiscount);

    order.applyDiscount(101.0); // Over 100%
    EXPECT_DOUBLE_EQ(order.getDiscountAmount(), originalDiscount);
}

// Status Management Tests
TEST_F(OrderTest, OrderStatusToString)
{
    EXPECT_EQ(Order::statusToString(OrderStatus::PENDING), "PENDING");
    EXPECT_EQ(Order::statusToString(OrderStatus::CONFIRMED), "CONFIRMED");
    EXPECT_EQ(Order::statusToString(OrderStatus::PROCESSING), "PROCESSING");
    EXPECT_EQ(Order::statusToString(OrderStatus::SHIPPED), "SHIPPED");
    EXPECT_EQ(Order::statusToString(OrderStatus::DELIVERED), "DELIVERED");
    EXPECT_EQ(Order::statusToString(OrderStatus::CANCELLED), "CANCELLED");
}

TEST_F(OrderTest, StringToOrderStatus)
{
    EXPECT_EQ(Order::stringToStatus("PENDING"), OrderStatus::PENDING);
    EXPECT_EQ(Order::stringToStatus("CONFIRMED"), OrderStatus::CONFIRMED);
    EXPECT_EQ(Order::stringToStatus("PROCESSING"), OrderStatus::PROCESSING);
    EXPECT_EQ(Order::stringToStatus("SHIPPED"), OrderStatus::SHIPPED);
    EXPECT_EQ(Order::stringToStatus("DELIVERED"), OrderStatus::DELIVERED);
    EXPECT_EQ(Order::stringToStatus("CANCELLED"), OrderStatus::CANCELLED);
}

TEST_F(OrderTest, CanChangeStatusTo)
{
    Order order = validOrder;

    // From PENDING
    EXPECT_TRUE(order.canChangeStatusTo(OrderStatus::CONFIRMED));
    EXPECT_TRUE(order.canChangeStatusTo(OrderStatus::CANCELLED));
    EXPECT_FALSE(order.canChangeStatusTo(OrderStatus::DELIVERED));

    // From CONFIRMED
    order.setStatus(OrderStatus::CONFIRMED);
    EXPECT_TRUE(order.canChangeStatusTo(OrderStatus::PROCESSING));
    EXPECT_TRUE(order.canChangeStatusTo(OrderStatus::CANCELLED));
    EXPECT_FALSE(order.canChangeStatusTo(OrderStatus::PENDING));

    // From DELIVERED
    order.setStatus(OrderStatus::DELIVERED);
    EXPECT_FALSE(order.canChangeStatusTo(OrderStatus::PENDING));
    EXPECT_FALSE(order.canChangeStatusTo(OrderStatus::SHIPPED));
    EXPECT_FALSE(order.canChangeStatusTo(OrderStatus::CANCELLED));
}

TEST_F(OrderTest, UpdateStatus)
{
    Order order = validOrder;

    EXPECT_TRUE(order.updateStatus(OrderStatus::CONFIRMED));
    EXPECT_EQ(order.getStatus(), OrderStatus::CONFIRMED);

    EXPECT_FALSE(order.updateStatus(OrderStatus::PENDING)); // Can't go back
    EXPECT_EQ(order.getStatus(), OrderStatus::CONFIRMED);   // Should remain unchanged
}

// Utility Methods Tests
TEST_F(OrderTest, GetItemCount)
{
    Order order = validOrder;
    EXPECT_EQ(order.getItemCount(), 0);

    order.addItem(testItem1);
    order.addItem(testItem2);
    EXPECT_EQ(order.getItemCount(), 2);
}

TEST_F(OrderTest, IsEmpty)
{
    Order order = validOrder;
    EXPECT_TRUE(order.isEmpty());

    order.addItem(testItem1);
    EXPECT_FALSE(order.isEmpty());

    order.clearItems();
    EXPECT_TRUE(order.isEmpty());
}

TEST_F(OrderTest, IsValid)
{
    Order order = validOrder;
    order.addItem(testItem1);
    EXPECT_TRUE(order.isValid());

    // Empty order should be invalid
    Order emptyOrder;
    EXPECT_FALSE(emptyOrder.isValid());

    // Order without items should be invalid
    Order orderNoItems = validOrder;
    EXPECT_FALSE(orderNoItems.isValid());
}

// ToString Tests
TEST_F(OrderTest, ToStringContainsOrderInfo)
{
    Order order = validOrder;
    order.addItem(testItem1);
    order.calculateTotalAmount();

    std::string result = order.toString();

    EXPECT_NE(result.find("John Doe"), std::string::npos);
    EXPECT_NE(result.find("Laptop"), std::string::npos);
    EXPECT_NE(result.find("PENDING"), std::string::npos);
}

// Serialization Tests
TEST_F(OrderTest, SerializationAndDeserialization)
{
    Order order = validOrder;
    order.addItem(testItem1);
    order.addItem(testItem2);
    order.calculateTotalAmount();
    order.setStatus(OrderStatus::CONFIRMED);
    order.setShippingAddress("123 Test St");
    order.setNotes("Test order");

    std::string serialized = order.serialize();
    EXPECT_FALSE(serialized.empty());

    Order deserialized = Order::deserialize(serialized);

    EXPECT_EQ(deserialized.getOrderId(), order.getOrderId());
    EXPECT_EQ(deserialized.getCustomerId(), order.getCustomerId());
    EXPECT_EQ(deserialized.getCustomerName(), order.getCustomerName());
    EXPECT_EQ(deserialized.getItems().size(), order.getItems().size());
    EXPECT_EQ(deserialized.getStatus(), order.getStatus());
    EXPECT_EQ(deserialized.getShippingAddress(), order.getShippingAddress());
    EXPECT_EQ(deserialized.getNotes(), order.getNotes());
    EXPECT_DOUBLE_EQ(deserialized.getTotalAmount(), order.getTotalAmount());
}

// Edge Cases
TEST_F(OrderTest, OrderWithZeroQuantityItem)
{
    OrderItem zeroItem(1, "Test", 0, 100.0);
    EXPECT_DOUBLE_EQ(zeroItem.totalPrice, 0.0);

    Order order = validOrder;
    order.addItem(zeroItem);
    EXPECT_EQ(order.getItems().size(), 1);
}

TEST_F(OrderTest, OrderWithHighQuantities)
{
    OrderItem highQuantityItem(1, "Bulk Item", 1000, 1.99);
    EXPECT_DOUBLE_EQ(highQuantityItem.totalPrice, 1990.0);

    Order order = validOrder;
    order.addItem(highQuantityItem);
    order.calculateTotalAmount();
    EXPECT_DOUBLE_EQ(order.getTotalAmount(), 1990.0);
}

TEST_F(OrderTest, OrderWithVerySmallPrices)
{
    OrderItem cheapItem(1, "Penny Item", 100, 0.01);
    EXPECT_DOUBLE_EQ(cheapItem.totalPrice, 1.0);

    Order order = validOrder;
    order.addItem(cheapItem);
    order.calculateTotalAmount();
    EXPECT_DOUBLE_EQ(order.getTotalAmount(), 1.0);
}