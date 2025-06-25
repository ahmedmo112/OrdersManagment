#pragma once
#include "models/Order.h"
#include "models/Customer.h"
#include "models/Product.h"
#include <vector>
#include <memory>
#include <map>

class ProductManager;
class CustomerManager;

class OrderManager
{
private:
    std::vector<Order> orders;
    int nextOrderId;
    ProductManager *productManager;
    CustomerManager *customerManager;

    void loadOrders();
    void saveOrders();
    int generateNextId();

public:
    OrderManager(ProductManager *prodMgr = nullptr, CustomerManager *custMgr = nullptr);
    ~OrderManager();

    // Manager dependencies
    void setProductManager(ProductManager *prodMgr) { productManager = prodMgr; }
    void setCustomerManager(CustomerManager *custMgr) { customerManager = custMgr; }

    // CRUD operations
    bool createOrder(int customerId);
    Order *getOrder(int orderId);
    std::vector<Order> getAllOrders();
    bool updateOrder(const Order &order);
    bool deleteOrder(int orderId);

    // Order item management
    bool addItemToOrder(int orderId, int productId, int quantity);
    bool removeItemFromOrder(int orderId, int productId);
    bool updateOrderItemQuantity(int orderId, int productId, int newQuantity);

    // Order status management
    bool updateOrderStatus(int orderId, OrderStatus newStatus);
    bool confirmOrder(int orderId);
    bool processOrder(int orderId);
    bool shipOrder(int orderId);
    bool deliverOrder(int orderId);
    bool cancelOrder(int orderId);

    // Search and filter operations
    std::vector<Order> getOrdersByCustomer(int customerId);
    std::vector<Order> getOrdersByStatus(OrderStatus status);
    std::vector<Order> getOrdersByDateRange(const std::string &startDate, const std::string &endDate);
    std::vector<Order> searchOrders(const std::string &searchTerm);

    // Financial operations
    bool applyDiscount(int orderId, double discountPercent);
    bool applyFixedDiscount(int orderId, double discountAmount);
    double calculateOrderTotal(int orderId);
    double getTotalRevenue();
    double getTotalRevenueByPeriod(const std::string &startDate, const std::string &endDate);

    // Validation
    bool validateOrder(const Order &order);
    bool canFulfillOrder(int orderId);
    bool checkProductAvailability(int productId, int quantity);

    // Statistics and reports
    int getTotalOrders();
    int getOrdersByStatusCount(OrderStatus status);
    std::map<OrderStatus, int> getOrderStatusDistribution();
    std::vector<std::pair<int, int>> getTopCustomers(int limit = 10); // customerId, orderCount
    std::vector<std::pair<int, int>> getTopProducts(int limit = 10);  // productId, quantity sold
    double getAverageOrderValue();

    // Reports
    void generateSalesReport();
    void generateOrderStatusReport();
    void generateCustomerOrderReport(int customerId);
    void generateProductSalesReport();
    void generateDailySalesReport(const std::string &date);
    void generateMonthlySalesReport(const std::string &month, const std::string &year);

    // Utility
    void printOrder(const Order &order);
    void printOrderSummary(const Order &order);
    void printAllOrders();
    void printOrdersByStatus(OrderStatus status);
    bool exportToCSV(const std::string &filename);
    bool importFromCSV(const std::string &filename);
};