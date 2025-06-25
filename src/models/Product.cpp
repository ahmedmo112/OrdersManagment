#include "models/Product.h"
#include "utils/Utils.h"
#include <sstream>
#include <algorithm>

Product::Product()
    : productId(0), price(0.0), stockQuantity(0), minStockLevel(0), isActive(true)
{
}

Product::Product(int id, const std::string &name, const std::string &description,
                 const std::string &category, double price, int stockQuantity, int minStockLevel)
    : productId(id), name(name), description(description), category(category),
      price(price), stockQuantity(stockQuantity), minStockLevel(minStockLevel), isActive(true)
{
}

bool Product::reduceStock(int quantity)
{
    if (quantity <= 0 || quantity > stockQuantity)
    {
        return false;
    }
    stockQuantity -= quantity;
    return true;
}

void Product::addStock(int quantity)
{
    if (quantity > 0)
    {
        stockQuantity += quantity;
    }
}

bool Product::isLowStock() const
{
    return stockQuantity <= minStockLevel;
}

bool Product::isInStock(int quantity) const
{
    return stockQuantity >= quantity;
}

std::string Product::toString() const
{
    std::stringstream ss;
    ss << "Product ID: " << productId << "\n"
       << "Name: " << name << "\n"
       << "Description: " << description << "\n"
       << "Category: " << category << "\n"
       << "Price: " << Utils::formatCurrency(price) << "\n"
       << "Stock Quantity: " << stockQuantity << "\n"
       << "Min Stock Level: " << minStockLevel << "\n"
       << "Status: " << (isActive ? "Active" : "Inactive") << "\n"
       << "Stock Status: " << (isLowStock() ? "LOW STOCK" : "In Stock");
    return ss.str();
}

bool Product::isValid() const
{
    return !name.empty() &&
           !category.empty() &&
           price >= 0.0 &&
           stockQuantity >= 0 &&
           minStockLevel >= 0;
}

std::string Product::serialize() const
{
    std::stringstream ss;
    ss << productId << "|"
       << name << "|"
       << description << "|"
       << category << "|"
       << price << "|"
       << stockQuantity << "|"
       << minStockLevel << "|"
       << (isActive ? "1" : "0");
    return ss.str();
}

Product Product::deserialize(const std::string &data)
{
    std::vector<std::string> parts = Utils::split(data, '|');
    Product product;

    if (parts.size() >= 8)
    {
        product.productId = std::stoi(parts[0]);
        product.name = parts[1];
        product.description = parts[2];
        product.category = parts[3];
        product.price = std::stod(parts[4]);
        product.stockQuantity = std::stoi(parts[5]);
        product.minStockLevel = std::stoi(parts[6]);
        product.isActive = (parts[7] == "1");
    }

    return product;
}