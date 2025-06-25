#include "managers/ProductManager.h"
#include "utils/Database.h"
#include "utils/Logger.h"
#include "utils/Utils.h"
#include <algorithm>
#include <iostream>

ProductManager::ProductManager() : nextProductId(1)
{
    loadProducts();
}

ProductManager::~ProductManager()
{
    saveProducts();
}

void ProductManager::loadProducts()
{
    Database &db = Database::getInstance();
    std::vector<std::string> data = db.loadProducts();

    products.clear();
    for (const auto &line : data)
    {
        if (!line.empty())
        {
            Product product = Product::deserialize(line);
            products.push_back(product);

            if (product.getProductId() >= nextProductId)
            {
                nextProductId = product.getProductId() + 1;
            }
        }
    }

    LOG_INFO("Loaded " + std::to_string(products.size()) + " products");
}

void ProductManager::saveProducts()
{
    std::vector<std::string> data;
    for (const auto &product : products)
    {
        data.push_back(product.serialize());
    }

    Database &db = Database::getInstance();
    if (db.saveProducts(data))
    {
        LOG_INFO("Saved " + std::to_string(products.size()) + " products");
    }
    else
    {
        LOG_ERROR("Failed to save products");
    }
}

int ProductManager::generateNextId()
{
    return nextProductId++;
}

bool ProductManager::addProduct(const Product &product)
{
    if (!validateProduct(product))
    {
        return false;
    }

    Product newProduct = product;
    newProduct.setProductId(generateNextId());

    products.push_back(newProduct);
    saveProducts();

    LOG_INFO("Added new product: " + newProduct.getName());
    return true;
}

Product *ProductManager::getProduct(int productId)
{
    auto it = std::find_if(products.begin(), products.end(),
                           [productId](const Product &p)
                           {
                               return p.getProductId() == productId;
                           });

    return (it != products.end()) ? &(*it) : nullptr;
}

std::vector<Product> ProductManager::getAllProducts()
{
    return products;
}

std::vector<Product> ProductManager::getActiveProducts()
{
    std::vector<Product> activeProducts;
    std::copy_if(products.begin(), products.end(),
                 std::back_inserter(activeProducts),
                 [](const Product &p)
                 { return p.getIsActive(); });
    return activeProducts;
}

bool ProductManager::updateProduct(const Product &product)
{
    auto it = std::find_if(products.begin(), products.end(),
                           [&product](const Product &p)
                           {
                               return p.getProductId() == product.getProductId();
                           });

    if (it != products.end())
    {
        if (!validateProduct(product))
        {
            return false;
        }

        *it = product;
        saveProducts();
        LOG_INFO("Updated product: " + product.getName());
        return true;
    }

    return false;
}

bool ProductManager::deleteProduct(int productId)
{
    auto it = std::find_if(products.begin(), products.end(),
                           [productId](const Product &p)
                           {
                               return p.getProductId() == productId;
                           });

    if (it != products.end())
    {
        std::string productName = it->getName();
        products.erase(it);
        saveProducts();
        LOG_INFO("Deleted product: " + productName);
        return true;
    }

    return false;
}

bool ProductManager::validateProduct(const Product &product)
{
    if (!product.isValid())
    {
        return false;
    }

    if (!isProductNameUnique(product.getName(), product.getProductId()))
    {
        LOG_WARNING("Product name already exists: " + product.getName());
        return false;
    }

    return true;
}

bool ProductManager::isProductNameUnique(const std::string &name, int excludeProductId)
{
    return std::none_of(products.begin(), products.end(),
                        [&name, excludeProductId](const Product &p)
                        {
                            return p.getProductId() != excludeProductId &&
                                   Utils::toLower(p.getName()) == Utils::toLower(name);
                        });
}

int ProductManager::getTotalProducts()
{
    return static_cast<int>(products.size());
}

int ProductManager::getActiveProductsCount()
{
    return static_cast<int>(std::count_if(products.begin(), products.end(),
                                          [](const Product &p)
                                          { return p.getIsActive(); }));
}

int ProductManager::getInactiveProductsCount()
{
    return getTotalProducts() - getActiveProductsCount();
}

void ProductManager::printProduct(const Product &product)
{
    std::cout << product.toString() << std::endl;
}

void ProductManager::printAllProducts()
{
    Utils::printHeader("All Products");
    for (const auto &product : products)
    {
        printProduct(product);
        Utils::printSeparator('-', 50);
    }
}

// Basic implementations for other methods
bool ProductManager::deactivateProduct(int productId)
{
    Product *product = getProduct(productId);
    if (product)
    {
        product->setIsActive(false);
        saveProducts();
        return true;
    }
    return false;
}

bool ProductManager::activateProduct(int productId)
{
    Product *product = getProduct(productId);
    if (product)
    {
        product->setIsActive(true);
        saveProducts();
        return true;
    }
    return false;
}

bool ProductManager::updateStock(int productId, int newQuantity)
{
    Product *product = getProduct(productId);
    if (product)
    {
        int oldStock = product->getStockQuantity();
        product->setStockQuantity(newQuantity);
        saveProducts();
        LOG_INFO("Stock updated for product " + std::to_string(productId) +
                 ": " + std::to_string(oldStock) + " -> " + std::to_string(newQuantity));
        return true;
    }
    return false;
}

bool ProductManager::addStock(int productId, int quantity)
{
    Product *product = getProduct(productId);
    if (product)
    {
        product->addStock(quantity);
        saveProducts();
        return true;
    }
    return false;
}

bool ProductManager::reduceStock(int productId, int quantity)
{
    Product *product = getProduct(productId);
    if (product && product->reduceStock(quantity))
    {
        saveProducts();
        return true;
    }
    return false;
}

std::vector<Product> ProductManager::getLowStockProducts()
{
    std::vector<Product> lowStock;
    std::copy_if(products.begin(), products.end(),
                 std::back_inserter(lowStock),
                 [](const Product &p)
                 { return p.isLowStock() && p.getIsActive(); });
    return lowStock;
}

std::vector<Product> ProductManager::getOutOfStockProducts()
{
    std::vector<Product> outOfStock;
    std::copy_if(products.begin(), products.end(),
                 std::back_inserter(outOfStock),
                 [](const Product &p)
                 { return p.getStockQuantity() == 0 && p.getIsActive(); });
    return outOfStock;
}

bool ProductManager::isProductAvailable(int productId, int quantity)
{
    Product *product = getProduct(productId);
    return product && product->isInStock(quantity);
}

std::vector<Product> ProductManager::searchByName(const std::string &name)
{
    std::vector<Product> results;
    std::string searchName = Utils::toLower(name);

    std::copy_if(products.begin(), products.end(),
                 std::back_inserter(results),
                 [&searchName](const Product &p)
                 {
                     return Utils::toLower(p.getName()).find(searchName) != std::string::npos;
                 });

    return results;
}

std::vector<Product> ProductManager::getProductsByCategory(const std::string &category)
{
    std::vector<Product> results;
    std::string searchCategory = Utils::toLower(category);

    std::copy_if(products.begin(), products.end(),
                 std::back_inserter(results),
                 [&searchCategory](const Product &p)
                 {
                     return Utils::toLower(p.getCategory()) == searchCategory;
                 });

    return results;
}

std::vector<Product> ProductManager::getProductsByPriceRange(double minPrice, double maxPrice)
{
    std::vector<Product> results;

    std::copy_if(products.begin(), products.end(),
                 std::back_inserter(results),
                 [minPrice, maxPrice](const Product &p)
                 {
                     return p.getPrice() >= minPrice && p.getPrice() <= maxPrice;
                 });

    return results;
}

std::vector<Product> ProductManager::getProductsInStock()
{
    std::vector<Product> results;

    std::copy_if(products.begin(), products.end(),
                 std::back_inserter(results),
                 [](const Product &p)
                 {
                     return p.getStockQuantity() > 0 && p.getIsActive();
                 });

    return results;
}

// Placeholder implementations
bool ProductManager::updatePrice(int productId, double newPrice) { return false; }
bool ProductManager::applyDiscount(int productId, double discountPercent) { return false; }
bool ProductManager::applyBulkDiscount(const std::string &category, double discountPercent) { return false; }
std::vector<std::string> ProductManager::getAllCategories() { return std::vector<std::string>(); }
int ProductManager::getProductCountByCategory(const std::string &category) { return 0; }
double ProductManager::getTotalInventoryValue() { return 0.0; }
double ProductManager::getAveragePrice() { return 0.0; }
int ProductManager::getTotalStockQuantity() { return 0; }
void ProductManager::generateInventoryReport() {}
void ProductManager::generateLowStockReport() {}
void ProductManager::generateCategoryReport() {}
void ProductManager::printProductsTable() {}
bool ProductManager::exportToCSV(const std::string &filename) { return false; }
bool ProductManager::importFromCSV(const std::string &filename) { return false; }