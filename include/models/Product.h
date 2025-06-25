#pragma once
#include <string>

class Product
{
private:
    int productId;
    std::string name;
    std::string description;
    std::string category;
    double price;
    int stockQuantity;
    int minStockLevel;
    bool isActive;

public:
    // Constructors
    Product();
    Product(int id, const std::string &name, const std::string &description,
            const std::string &category, double price, int stockQuantity, int minStockLevel);

    // Getters
    int getProductId() const { return productId; }
    const std::string &getName() const { return name; }
    const std::string &getDescription() const { return description; }
    const std::string &getCategory() const { return category; }
    double getPrice() const { return price; }
    int getStockQuantity() const { return stockQuantity; }
    int getMinStockLevel() const { return minStockLevel; }
    bool getIsActive() const { return isActive; }

    // Setters
    void setProductId(int id) { productId = id; }
    void setName(const std::string &name) { this->name = name; }
    void setDescription(const std::string &description) { this->description = description; }
    void setCategory(const std::string &category) { this->category = category; }
    void setPrice(double price) { this->price = price; }
    void setStockQuantity(int quantity) { stockQuantity = quantity; }
    void setMinStockLevel(int level) { minStockLevel = level; }
    void setIsActive(bool active) { isActive = active; }

    // Stock management
    bool reduceStock(int quantity);
    void addStock(int quantity);
    bool isLowStock() const;
    bool isInStock(int quantity = 1) const;

    // Utility methods
    std::string toString() const;
    bool isValid() const;

    // Serialization
    std::string serialize() const;
    static Product deserialize(const std::string &data);
};