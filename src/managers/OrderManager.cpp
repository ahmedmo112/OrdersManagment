#include "managers/OrderManager.h"
#include "managers/ProductManager.h"
#include "managers/CustomerManager.h"
#include "utils/Database.h"
#include "utils/Logger.h"
#include "utils/Utils.h"
#include <algorithm>
#include <iostream>

OrderManager::OrderManager(ProductManager *prodMgr, CustomerManager *custMgr)
    : nextOrderId(1), productManager(prodMgr), customerManager(custMgr)
{
    loadOrders();
}

OrderManager::~OrderManager()
{
    saveOrders();
}

void OrderManager::loadOrders()
{
    Database &db = Database::getInstance();
    std::vector<std::string> data = db.loadOrders();

    orders.clear();
    for (const auto &line : data)
    {
        if (!line.empty())
        {
            Order order = Order::deserialize(line);
            orders.push_back(order);

            if (order.getOrderId() >= nextOrderId)
            {
                nextOrderId = order.getOrderId() + 1;
            }
        }
    }

    LOG_INFO("Loaded " + std::to_string(orders.size()) + " orders");
}

void OrderManager::saveOrders()
{
    std::vector<std::string> data;
    for (const auto &order : orders)
    {
        data.push_back(order.serialize());
    }

    Database &db = Database::getInstance();
    if (db.saveOrders(data))
    {
        LOG_INFO("Saved " + std::to_string(orders.size()) + " orders");
    }
    else
    {
        LOG_ERROR("Failed to save orders");
    }
}

int OrderManager::generateNextId()
{
    return nextOrderId++;
}

bool OrderManager::createOrder(int customerId)
{
    if (!customerManager)
    {
        LOG_ERROR("CustomerManager not set");
        return false;
    }

    Customer *customer = customerManager->getCustomer(customerId);
    if (!customer)
    {
        LOG_WARNING("Customer not found: " + std::to_string(customerId));
        return false;
    }

    Order order(generateNextId(), customerId, customer->getName());
    order.setShippingAddress(customer->getAddress() + ", " + customer->getCity() + ", " + customer->getCountry());

    orders.push_back(order);
    saveOrders();

    LOG_INFO("Created order " + std::to_string(order.getOrderId()) + " for customer " + std::to_string(customerId));
    return true;
}

Order *OrderManager::getOrder(int orderId)
{
    auto it = std::find_if(orders.begin(), orders.end(),
                           [orderId](const Order &o)
                           {
                               return o.getOrderId() == orderId;
                           });

    return (it != orders.end()) ? &(*it) : nullptr;
}

std::vector<Order> OrderManager::getAllOrders()
{
    return orders;
}

bool OrderManager::updateOrder(const Order &order)
{
    auto it = std::find_if(orders.begin(), orders.end(),
                           [&order](const Order &o)
                           {
                               return o.getOrderId() == order.getOrderId();
                           });

    if (it != orders.end())
    {
        *it = order;
        saveOrders();
        LOG_INFO("Updated order: " + std::to_string(order.getOrderId()));
        return true;
    }

    return false;
}

bool OrderManager::deleteOrder(int orderId)
{
    auto it = std::find_if(orders.begin(), orders.end(),
                           [orderId](const Order &o)
                           {
                               return o.getOrderId() == orderId;
                           });

    if (it != orders.end())
    {
        orders.erase(it);
        saveOrders();
        LOG_INFO("Deleted order: " + std::to_string(orderId));
        return true;
    }

    return false;
}

bool OrderManager::addItemToOrder(int orderId, int productId, int quantity)
{
    if (!productManager)
    {
        LOG_ERROR("ProductManager not set");
        return false;
    }

    Order *order = getOrder(orderId);
    Product *product = productManager->getProduct(productId);

    if (!order || !product)
    {
        return false;
    }

    if (!product->isInStock(quantity))
    {
        LOG_WARNING("Insufficient stock for product " + std::to_string(productId));
        return false;
    }

    OrderItem item(productId, product->getName(), quantity, product->getPrice());
    order->addItem(item);

    saveOrders();
    LOG_INFO("Added item to order " + std::to_string(orderId) +
             ": " + product->getName() + " x" + std::to_string(quantity));
    return true;
}

bool OrderManager::removeItemFromOrder(int orderId, int productId)
{
    Order *order = getOrder(orderId);
    if (order && order->removeItem(productId))
    {
        saveOrders();
        LOG_INFO("Removed item from order " + std::to_string(orderId) +
                 ": product " + std::to_string(productId));
        return true;
    }
    return false;
}

bool OrderManager::updateOrderItemQuantity(int orderId, int productId, int newQuantity)
{
    Order *order = getOrder(orderId);
    if (order && order->updateItemQuantity(productId, newQuantity))
    {
        saveOrders();
        LOG_INFO("Updated item quantity in order " + std::to_string(orderId) +
                 ": product " + std::to_string(productId) + " to " + std::to_string(newQuantity));
        return true;
    }
    return false;
}

bool OrderManager::updateOrderStatus(int orderId, OrderStatus newStatus)
{
    Order *order = getOrder(orderId);
    if (order)
    {
        std::string oldStatus = order->getStatusString();
        if (order->updateStatus(newStatus))
        {
            saveOrders();
            LOG_INFO("Updated order " + std::to_string(orderId) +
                     " status from " + oldStatus + " to " + order->getStatusString());
            return true;
        }
    }
    return false;
}

bool OrderManager::confirmOrder(int orderId)
{
    return updateOrderStatus(orderId, OrderStatus::CONFIRMED);
}

bool OrderManager::processOrder(int orderId)
{
    return updateOrderStatus(orderId, OrderStatus::PROCESSING);
}

bool OrderManager::shipOrder(int orderId)
{
    return updateOrderStatus(orderId, OrderStatus::SHIPPED);
}

bool OrderManager::deliverOrder(int orderId)
{
    return updateOrderStatus(orderId, OrderStatus::DELIVERED);
}

bool OrderManager::cancelOrder(int orderId)
{
    return updateOrderStatus(orderId, OrderStatus::CANCELLED);
}

std::vector<Order> OrderManager::getOrdersByCustomer(int customerId)
{
    std::vector<Order> results;
    std::copy_if(orders.begin(), orders.end(),
                 std::back_inserter(results),
                 [customerId](const Order &o)
                 {
                     return o.getCustomerId() == customerId;
                 });
    return results;
}

std::vector<Order> OrderManager::getOrdersByStatus(OrderStatus status)
{
    std::vector<Order> results;
    std::copy_if(orders.begin(), orders.end(),
                 std::back_inserter(results),
                 [status](const Order &o)
                 {
                     return o.getStatus() == status;
                 });
    return results;
}

bool OrderManager::validateOrder(const Order &order)
{
    return order.isValid();
}

bool OrderManager::canFulfillOrder(int orderId)
{
    Order *order = getOrder(orderId);
    if (!order || !productManager)
    {
        return false;
    }

    for (const auto &item : order->getItems())
    {
        if (!productManager->isProductAvailable(item.productId, item.quantity))
        {
            return false;
        }
    }

    return true;
}

bool OrderManager::checkProductAvailability(int productId, int quantity)
{
    return productManager && productManager->isProductAvailable(productId, quantity);
}

int OrderManager::getTotalOrders()
{
    return static_cast<int>(orders.size());
}

int OrderManager::getOrdersByStatusCount(OrderStatus status)
{
    return static_cast<int>(std::count_if(orders.begin(), orders.end(),
                                          [status](const Order &o)
                                          { return o.getStatus() == status; }));
}

void OrderManager::printOrder(const Order &order)
{
    std::cout << order.toString() << std::endl;
}

void OrderManager::printOrderSummary(const Order &order)
{
    std::cout << "Order #" << order.getOrderId()
              << " - Customer: " << order.getCustomerName()
              << " - Status: " << order.getStatusString()
              << " - Total: " << Utils::formatCurrency(order.getFinalAmount())
              << std::endl;
}

void OrderManager::printAllOrders()
{
    Utils::printHeader("All Orders");
    for (const auto &order : orders)
    {
        printOrderSummary(order);
    }
}

void OrderManager::printOrdersByStatus(OrderStatus status)
{
    Utils::printHeader("Orders with status: " + Order::statusToString(status));
    for (const auto &order : orders)
    {
        if (order.getStatus() == status)
        {
            printOrderSummary(order);
        }
    }
}

// Placeholder implementations
std::vector<Order> OrderManager::getOrdersByDateRange(const std::string &startDate, const std::string &endDate) { return std::vector<Order>(); }
std::vector<Order> OrderManager::searchOrders(const std::string &searchTerm) { return std::vector<Order>(); }
bool OrderManager::applyDiscount(int orderId, double discountPercent) { return false; }
bool OrderManager::applyFixedDiscount(int orderId, double discountAmount) { return false; }
double OrderManager::calculateOrderTotal(int orderId) { return 0.0; }
double OrderManager::getTotalRevenue() { return 0.0; }
double OrderManager::getTotalRevenueByPeriod(const std::string &startDate, const std::string &endDate) { return 0.0; }
std::map<OrderStatus, int> OrderManager::getOrderStatusDistribution() { return std::map<OrderStatus, int>(); }
std::vector<std::pair<int, int>> OrderManager::getTopCustomers(int limit) { return std::vector<std::pair<int, int>>(); }
std::vector<std::pair<int, int>> OrderManager::getTopProducts(int limit) { return std::vector<std::pair<int, int>>(); }
double OrderManager::getAverageOrderValue() { return 0.0; }
void OrderManager::generateSalesReport() {}
void OrderManager::generateOrderStatusReport() {}
void OrderManager::generateCustomerOrderReport(int customerId) {}
void OrderManager::generateProductSalesReport() {}
void OrderManager::generateDailySalesReport(const std::string &date) {}
void OrderManager::generateMonthlySalesReport(const std::string &month, const std::string &year) {}
bool OrderManager::exportToCSV(const std::string &filename) { return false; }
bool OrderManager::importFromCSV(const std::string &filename) { return false; }