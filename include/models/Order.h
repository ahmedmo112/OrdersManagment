#pragma once
#include <string>
#include <vector>
#include <chrono>
#include <map>

enum class OrderStatus
{
    PENDING,
    CONFIRMED,
    PROCESSING,
    SHIPPED,
    DELIVERED,
    CANCELLED
};

struct OrderItem
{
    int productId;
    std::string productName;
    int quantity;
    double unitPrice;
    double totalPrice;

    OrderItem(int prodId, const std::string &name, int qty, double price)
        : productId(prodId), productName(name), quantity(qty),
          unitPrice(price), totalPrice(qty * price) {}
};

class Order
{
private:
    int orderId;
    int customerId;
    std::string customerName;
    std::vector<OrderItem> items;
    OrderStatus status;
    std::string orderDate;
    std::string shippingAddress;
    double totalAmount;
    double discountAmount;
    double finalAmount;
    std::string notes;

public:
    // Constructors
    Order();
    Order(int id, int customerId, const std::string &customerName);

    // Getters
    int getOrderId() const { return orderId; }
    int getCustomerId() const { return customerId; }
    const std::string &getCustomerName() const { return customerName; }
    const std::vector<OrderItem> &getItems() const { return items; }
    OrderStatus getStatus() const { return status; }
    const std::string &getOrderDate() const { return orderDate; }
    const std::string &getShippingAddress() const { return shippingAddress; }
    double getTotalAmount() const { return totalAmount; }
    double getDiscountAmount() const { return discountAmount; }
    double getFinalAmount() const { return finalAmount; }
    const std::string &getNotes() const { return notes; }

    // Setters
    void setOrderId(int id) { orderId = id; }
    void setCustomerId(int id) { customerId = id; }
    void setCustomerName(const std::string &name) { customerName = name; }
    void setStatus(OrderStatus newStatus) { status = newStatus; }
    void setShippingAddress(const std::string &address) { shippingAddress = address; }
    void setDiscountAmount(double discount)
    {
        discountAmount = discount;
        calculateFinalAmount();
    }
    void setNotes(const std::string &notes) { this->notes = notes; }

    // Item management
    void addItem(const OrderItem &item);
    bool removeItem(int productId);
    bool updateItemQuantity(int productId, int newQuantity);
    void clearItems();

    // Order calculations
    void calculateTotalAmount();
    void calculateFinalAmount();
    void applyDiscount(double discountPercent);

    // Status management
    bool canChangeStatusTo(OrderStatus newStatus) const;
    bool updateStatus(OrderStatus newStatus);
    std::string getStatusString() const;
    static std::string statusToString(OrderStatus status);
    static OrderStatus stringToStatus(const std::string &statusStr);

    // Utility methods
    int getItemCount() const;
    bool isEmpty() const;
    std::string toString() const;
    bool isValid() const;

    // Serialization
    std::string serialize() const;
    static Order deserialize(const std::string &data);
};