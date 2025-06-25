#include "models/Order.h"
#include "utils/Utils.h"
#include <sstream>
#include <algorithm>
#include <iomanip>

Order::Order()
    : orderId(0), customerId(0), status(OrderStatus::PENDING),
      totalAmount(0.0), discountAmount(0.0), finalAmount(0.0)
{
    orderDate = Utils::getCurrentDateTime();
}

Order::Order(int id, int customerId, const std::string &customerName)
    : orderId(id), customerId(customerId), customerName(customerName),
      status(OrderStatus::PENDING), totalAmount(0.0), discountAmount(0.0), finalAmount(0.0)
{
    orderDate = Utils::getCurrentDateTime();
}

void Order::addItem(const OrderItem &item)
{
    // Check if product already exists in order
    auto it = std::find_if(items.begin(), items.end(),
                           [&item](const OrderItem &existing)
                           {
                               return existing.productId == item.productId;
                           });

    if (it != items.end())
    {
        // Update existing item
        it->quantity += item.quantity;
        it->totalPrice = it->quantity * it->unitPrice;
    }
    else
    {
        // Add new item
        items.push_back(item);
    }

    calculateTotalAmount();
    calculateFinalAmount();
}

bool Order::removeItem(int productId)
{
    auto it = std::find_if(items.begin(), items.end(),
                           [productId](const OrderItem &item)
                           {
                               return item.productId == productId;
                           });

    if (it != items.end())
    {
        items.erase(it);
        calculateTotalAmount();
        calculateFinalAmount();
        return true;
    }

    return false;
}

bool Order::updateItemQuantity(int productId, int newQuantity)
{
    if (newQuantity <= 0)
    {
        return removeItem(productId);
    }

    auto it = std::find_if(items.begin(), items.end(),
                           [productId](const OrderItem &item)
                           {
                               return item.productId == productId;
                           });

    if (it != items.end())
    {
        it->quantity = newQuantity;
        it->totalPrice = it->quantity * it->unitPrice;
        calculateTotalAmount();
        calculateFinalAmount();
        return true;
    }

    return false;
}

void Order::clearItems()
{
    items.clear();
    calculateTotalAmount();
    calculateFinalAmount();
}

void Order::calculateTotalAmount()
{
    totalAmount = 0.0;
    for (const auto &item : items)
    {
        totalAmount += item.totalPrice;
    }
}

void Order::calculateFinalAmount()
{
    finalAmount = totalAmount - discountAmount;
    if (finalAmount < 0)
    {
        finalAmount = 0;
    }
}

void Order::applyDiscount(double discountPercent)
{
    if (discountPercent >= 0 && discountPercent <= 100)
    {
        discountAmount = totalAmount * (discountPercent / 100.0);
        calculateFinalAmount();
    }
}

bool Order::canChangeStatusTo(OrderStatus newStatus) const
{
    switch (status)
    {
    case OrderStatus::PENDING:
        return newStatus == OrderStatus::CONFIRMED || newStatus == OrderStatus::CANCELLED;
    case OrderStatus::CONFIRMED:
        return newStatus == OrderStatus::PROCESSING || newStatus == OrderStatus::CANCELLED;
    case OrderStatus::PROCESSING:
        return newStatus == OrderStatus::SHIPPED || newStatus == OrderStatus::CANCELLED;
    case OrderStatus::SHIPPED:
        return newStatus == OrderStatus::DELIVERED;
    case OrderStatus::DELIVERED:
    case OrderStatus::CANCELLED:
        return false;
    }
    return false;
}

bool Order::updateStatus(OrderStatus newStatus)
{
    if (canChangeStatusTo(newStatus))
    {
        status = newStatus;
        return true;
    }
    return false;
}

std::string Order::getStatusString() const
{
    return statusToString(status);
}

std::string Order::statusToString(OrderStatus status)
{
    switch (status)
    {
    case OrderStatus::PENDING:
        return "Pending";
    case OrderStatus::CONFIRMED:
        return "Confirmed";
    case OrderStatus::PROCESSING:
        return "Processing";
    case OrderStatus::SHIPPED:
        return "Shipped";
    case OrderStatus::DELIVERED:
        return "Delivered";
    case OrderStatus::CANCELLED:
        return "Cancelled";
    default:
        return "Unknown";
    }
}

OrderStatus Order::stringToStatus(const std::string &statusStr)
{
    if (statusStr == "Pending")
        return OrderStatus::PENDING;
    if (statusStr == "Confirmed")
        return OrderStatus::CONFIRMED;
    if (statusStr == "Processing")
        return OrderStatus::PROCESSING;
    if (statusStr == "Shipped")
        return OrderStatus::SHIPPED;
    if (statusStr == "Delivered")
        return OrderStatus::DELIVERED;
    if (statusStr == "Cancelled")
        return OrderStatus::CANCELLED;
    return OrderStatus::PENDING;
}

int Order::getItemCount() const
{
    int count = 0;
    for (const auto &item : items)
    {
        count += item.quantity;
    }
    return count;
}

bool Order::isEmpty() const
{
    return items.empty();
}

std::string Order::toString() const
{
    std::stringstream ss;
    ss << "Order ID: " << orderId << "\n"
       << "Customer ID: " << customerId << "\n"
       << "Customer Name: " << customerName << "\n"
       << "Order Date: " << orderDate << "\n"
       << "Status: " << getStatusString() << "\n"
       << "Shipping Address: " << shippingAddress << "\n"
       << "Items (" << items.size() << "):\n";

    for (const auto &item : items)
    {
        ss << "  - " << item.productName
           << " (ID: " << item.productId << ")"
           << " x" << item.quantity
           << " @ " << Utils::formatCurrency(item.unitPrice)
           << " = " << Utils::formatCurrency(item.totalPrice) << "\n";
    }

    ss << "Total Amount: " << Utils::formatCurrency(totalAmount) << "\n";
    if (discountAmount > 0)
    {
        ss << "Discount: " << Utils::formatCurrency(discountAmount) << "\n";
    }
    ss << "Final Amount: " << Utils::formatCurrency(finalAmount) << "\n";

    if (!notes.empty())
    {
        ss << "Notes: " << notes << "\n";
    }

    return ss.str();
}

bool Order::isValid() const
{
    return orderId > 0 &&
           customerId > 0 &&
           !customerName.empty() &&
           !items.empty() &&
           finalAmount >= 0;
}

std::string Order::serialize() const
{
    std::stringstream ss;
    ss << orderId << "|"
       << customerId << "|"
       << customerName << "|"
       << statusToString(status) << "|"
       << orderDate << "|"
       << shippingAddress << "|"
       << totalAmount << "|"
       << discountAmount << "|"
       << finalAmount << "|"
       << notes << "|";

    // Serialize items
    for (size_t i = 0; i < items.size(); ++i)
    {
        if (i > 0)
            ss << ";";
        ss << items[i].productId << ","
           << items[i].productName << ","
           << items[i].quantity << ","
           << items[i].unitPrice;
    }

    return ss.str();
}

Order Order::deserialize(const std::string &data)
{
    std::vector<std::string> parts = Utils::split(data, '|');
    Order order;

    if (parts.size() >= 11)
    {
        order.orderId = std::stoi(parts[0]);
        order.customerId = std::stoi(parts[1]);
        order.customerName = parts[2];
        order.status = stringToStatus(parts[3]);
        order.orderDate = parts[4];
        order.shippingAddress = parts[5];
        order.totalAmount = std::stod(parts[6]);
        order.discountAmount = std::stod(parts[7]);
        order.finalAmount = std::stod(parts[8]);
        order.notes = parts[9];

        // Deserialize items
        if (!parts[10].empty())
        {
            std::vector<std::string> itemStrings = Utils::split(parts[10], ';');
            for (const auto &itemStr : itemStrings)
            {
                std::vector<std::string> itemParts = Utils::split(itemStr, ',');
                if (itemParts.size() >= 4)
                {
                    OrderItem item(
                        std::stoi(itemParts[0]), // productId
                        itemParts[1],            // productName
                        std::stoi(itemParts[2]), // quantity
                        std::stod(itemParts[3])  // unitPrice
                    );
                    order.items.push_back(item);
                }
            }
        }
    }

    return order;
}