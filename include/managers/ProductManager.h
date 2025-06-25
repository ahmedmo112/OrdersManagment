#pragma once
#include "models/Product.h"
#include <vector>
#include <memory>

class ProductManager
{
private:
    std::vector<Product> products;
    int nextProductId;

    void loadProducts();
    void saveProducts();
    int generateNextId();

public:
    ProductManager();
    ~ProductManager();

    // CRUD operations
    bool addProduct(const Product &product);
    Product *getProduct(int productId);
    std::vector<Product> getAllProducts();
    std::vector<Product> getActiveProducts();
    bool updateProduct(const Product &product);
    bool deleteProduct(int productId);
    bool deactivateProduct(int productId);
    bool activateProduct(int productId);

    // Stock management
    bool updateStock(int productId, int newQuantity);
    bool addStock(int productId, int quantity);
    bool reduceStock(int productId, int quantity);
    std::vector<Product> getLowStockProducts();
    std::vector<Product> getOutOfStockProducts();
    bool isProductAvailable(int productId, int quantity = 1);

    // Search and filter operations
    std::vector<Product> searchByName(const std::string &name);
    std::vector<Product> getProductsByCategory(const std::string &category);
    std::vector<Product> getProductsByPriceRange(double minPrice, double maxPrice);
    std::vector<Product> getProductsInStock();

    // Price management
    bool updatePrice(int productId, double newPrice);
    bool applyDiscount(int productId, double discountPercent);
    bool applyBulkDiscount(const std::string &category, double discountPercent);

    // Categories
    std::vector<std::string> getAllCategories();
    int getProductCountByCategory(const std::string &category);

    // Validation
    bool isProductNameUnique(const std::string &name, int excludeProductId = -1);
    bool validateProduct(const Product &product);

    // Statistics
    int getTotalProducts();
    int getActiveProductsCount();
    int getInactiveProductsCount();
    double getTotalInventoryValue();
    double getAveragePrice();
    int getTotalStockQuantity();

    // Reports
    void generateInventoryReport();
    void generateLowStockReport();
    void generateCategoryReport();

    // Utility
    void printProduct(const Product &product);
    void printAllProducts();
    void printProductsTable();
    bool exportToCSV(const std::string &filename);
    bool importFromCSV(const std::string &filename);
};