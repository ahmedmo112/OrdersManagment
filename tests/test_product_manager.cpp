#include <gtest/gtest.h>
#include "managers/ProductManager.h"
#include "models/Product.h"

class ProductManagerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        productManager = std::make_unique<ProductManager>();

        // Create test products
        product1 = Product(1, "Laptop", "High-performance laptop",
                           "Electronics", 999.99, 50, 10);

        product2 = Product(2, "Mouse", "Wireless mouse",
                           "Electronics", 29.99, 100, 5);

        product3 = Product(3, "Desk Chair", "Ergonomic office chair",
                           "Furniture", 199.99, 25, 3);

        product4 = Product(4, "Coffee Mug", "Ceramic coffee mug",
                           "Kitchen", 9.99, 200, 20);

        lowStockProduct = Product(5, "Low Stock Item", "Item with low stock",
                                  "Test", 50.0, 2, 10); // Stock below minimum
    }

    void TearDown() override
    {
        productManager.reset();
    }

    std::unique_ptr<ProductManager> productManager;
    Product product1, product2, product3, product4, lowStockProduct;
};

// CRUD Operations Tests
TEST_F(ProductManagerTest, AddProduct)
{
    EXPECT_TRUE(productManager->addProduct(product1));
    EXPECT_EQ(productManager->getTotalProducts(), 1);

    EXPECT_TRUE(productManager->addProduct(product2));
    EXPECT_EQ(productManager->getTotalProducts(), 2);
}

TEST_F(ProductManagerTest, AddDuplicateName)
{
    productManager->addProduct(product1);

    Product duplicate = product2;
    duplicate.setName(product1.getName()); // Same name

    EXPECT_FALSE(productManager->addProduct(duplicate));
    EXPECT_EQ(productManager->getTotalProducts(), 1);
}

TEST_F(ProductManagerTest, AddInvalidProduct)
{
    Product invalid;
    invalid.setName(""); // Invalid name

    EXPECT_FALSE(productManager->addProduct(invalid));
    EXPECT_EQ(productManager->getTotalProducts(), 0);
}

TEST_F(ProductManagerTest, GetProduct)
{
    productManager->addProduct(product1);

    Product *found = productManager->getProduct(product1.getProductId());
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getName(), product1.getName());
    EXPECT_DOUBLE_EQ(found->getPrice(), product1.getPrice());

    Product *notFound = productManager->getProduct(999);
    EXPECT_EQ(notFound, nullptr);
}

TEST_F(ProductManagerTest, GetAllProducts)
{
    std::vector<Product> products = productManager->getAllProducts();
    EXPECT_TRUE(products.empty());

    productManager->addProduct(product1);
    productManager->addProduct(product2);

    products = productManager->getAllProducts();
    EXPECT_EQ(products.size(), 2);
}

TEST_F(ProductManagerTest, GetActiveProducts)
{
    productManager->addProduct(product1);
    productManager->addProduct(product2);

    // Deactivate one product
    productManager->deactivateProduct(product1.getProductId());

    std::vector<Product> activeProducts = productManager->getActiveProducts();
    EXPECT_EQ(activeProducts.size(), 1);
    EXPECT_EQ(activeProducts[0].getProductId(), product2.getProductId());
}

TEST_F(ProductManagerTest, UpdateProduct)
{
    productManager->addProduct(product1);

    Product updated = product1;
    updated.setName("Updated Laptop");
    updated.setPrice(1099.99);

    EXPECT_TRUE(productManager->updateProduct(updated));

    Product *found = productManager->getProduct(product1.getProductId());
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getName(), "Updated Laptop");
    EXPECT_DOUBLE_EQ(found->getPrice(), 1099.99);
}

TEST_F(ProductManagerTest, DeleteProduct)
{
    productManager->addProduct(product1);
    productManager->addProduct(product2);

    EXPECT_EQ(productManager->getTotalProducts(), 2);

    EXPECT_TRUE(productManager->deleteProduct(product1.getProductId()));
    EXPECT_EQ(productManager->getTotalProducts(), 1);

    Product *deleted = productManager->getProduct(product1.getProductId());
    EXPECT_EQ(deleted, nullptr);
}

// Stock Management Tests
TEST_F(ProductManagerTest, UpdateStock)
{
    productManager->addProduct(product1);

    EXPECT_TRUE(productManager->updateStock(product1.getProductId(), 75));

    Product *found = productManager->getProduct(product1.getProductId());
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getStockQuantity(), 75);
}

TEST_F(ProductManagerTest, AddStock)
{
    productManager->addProduct(product1);
    int originalStock = product1.getStockQuantity();

    EXPECT_TRUE(productManager->addStock(product1.getProductId(), 25));

    Product *found = productManager->getProduct(product1.getProductId());
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getStockQuantity(), originalStock + 25);
}

TEST_F(ProductManagerTest, ReduceStock)
{
    productManager->addProduct(product1);
    int originalStock = product1.getStockQuantity();

    EXPECT_TRUE(productManager->reduceStock(product1.getProductId(), 10));

    Product *found = productManager->getProduct(product1.getProductId());
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getStockQuantity(), originalStock - 10);
}

TEST_F(ProductManagerTest, ReduceStockInsufficientQuantity)
{
    productManager->addProduct(product1);
    int originalStock = product1.getStockQuantity();

    EXPECT_FALSE(productManager->reduceStock(product1.getProductId(), 100));

    Product *found = productManager->getProduct(product1.getProductId());
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getStockQuantity(), originalStock); // Should remain unchanged
}

TEST_F(ProductManagerTest, GetLowStockProducts)
{
    productManager->addProduct(product1);        // Normal stock
    productManager->addProduct(lowStockProduct); // Low stock

    std::vector<Product> lowStockProducts = productManager->getLowStockProducts();
    EXPECT_EQ(lowStockProducts.size(), 1);
    EXPECT_EQ(lowStockProducts[0].getProductId(), lowStockProduct.getProductId());
}

TEST_F(ProductManagerTest, GetOutOfStockProducts)
{
    productManager->addProduct(product1);

    // Reduce stock to zero
    productManager->updateStock(product1.getProductId(), 0);

    std::vector<Product> outOfStockProducts = productManager->getOutOfStockProducts();
    EXPECT_EQ(outOfStockProducts.size(), 1);
    EXPECT_EQ(outOfStockProducts[0].getProductId(), product1.getProductId());
}

TEST_F(ProductManagerTest, IsProductAvailable)
{
    productManager->addProduct(product1); // 50 in stock

    EXPECT_TRUE(productManager->isProductAvailable(product1.getProductId(), 1));
    EXPECT_TRUE(productManager->isProductAvailable(product1.getProductId(), 50));
    EXPECT_FALSE(productManager->isProductAvailable(product1.getProductId(), 51));

    // Test default quantity (1)
    EXPECT_TRUE(productManager->isProductAvailable(product1.getProductId()));
}

// Search and Filter Tests
TEST_F(ProductManagerTest, SearchByName)
{
    productManager->addProduct(product1); // Laptop
    productManager->addProduct(product2); // Mouse
    productManager->addProduct(product3); // Desk Chair

    std::vector<Product> results = productManager->searchByName("Laptop");
    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].getName(), "Laptop");

    results = productManager->searchByName("mouse");
    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].getName(), "Mouse");

    results = productManager->searchByName("NonExistent");
    EXPECT_TRUE(results.empty());
}

TEST_F(ProductManagerTest, GetProductsByCategory)
{
    productManager->addProduct(product1); // Electronics
    productManager->addProduct(product2); // Electronics
    productManager->addProduct(product3); // Furniture
    productManager->addProduct(product4); // Kitchen

    std::vector<Product> electronics = productManager->getProductsByCategory("Electronics");
    EXPECT_EQ(electronics.size(), 2);

    std::vector<Product> furniture = productManager->getProductsByCategory("Furniture");
    EXPECT_EQ(furniture.size(), 1);
    EXPECT_EQ(furniture[0].getName(), "Desk Chair");
}

TEST_F(ProductManagerTest, GetProductsByPriceRange)
{
    productManager->addProduct(product1); // 999.99
    productManager->addProduct(product2); // 29.99
    productManager->addProduct(product3); // 199.99
    productManager->addProduct(product4); // 9.99

    std::vector<Product> results = productManager->getProductsByPriceRange(20.0, 200.0);
    EXPECT_EQ(results.size(), 2); // Mouse (29.99) and Desk Chair (199.99)

    results = productManager->getProductsByPriceRange(0.0, 50.0);
    EXPECT_EQ(results.size(), 2); // Mouse (29.99) and Coffee Mug (9.99)
}

TEST_F(ProductManagerTest, GetProductsInStock)
{
    productManager->addProduct(product1);
    productManager->addProduct(product2);

    // Set one product to zero stock
    productManager->updateStock(product1.getProductId(), 0);

    std::vector<Product> inStock = productManager->getProductsInStock();
    EXPECT_EQ(inStock.size(), 1);
    EXPECT_EQ(inStock[0].getProductId(), product2.getProductId());
}

// Price Management Tests
TEST_F(ProductManagerTest, UpdatePrice)
{
    productManager->addProduct(product1);

    EXPECT_TRUE(productManager->updatePrice(product1.getProductId(), 1199.99));

    Product *found = productManager->getProduct(product1.getProductId());
    ASSERT_NE(found, nullptr);
    EXPECT_DOUBLE_EQ(found->getPrice(), 1199.99);
}

TEST_F(ProductManagerTest, ApplyDiscount)
{
    productManager->addProduct(product1); // 999.99

    EXPECT_TRUE(productManager->applyDiscount(product1.getProductId(), 10.0)); // 10% discount

    Product *found = productManager->getProduct(product1.getProductId());
    ASSERT_NE(found, nullptr);
    EXPECT_DOUBLE_EQ(found->getPrice(), 899.991); // 999.99 * 0.9
}

TEST_F(ProductManagerTest, ApplyBulkDiscount)
{
    productManager->addProduct(product1); // Electronics, 999.99
    productManager->addProduct(product2); // Electronics, 29.99
    productManager->addProduct(product3); // Furniture, 199.99

    EXPECT_TRUE(productManager->applyBulkDiscount("Electronics", 20.0)); // 20% discount

    Product *laptop = productManager->getProduct(product1.getProductId());
    Product *mouse = productManager->getProduct(product2.getProductId());
    Product *chair = productManager->getProduct(product3.getProductId());

    ASSERT_NE(laptop, nullptr);
    ASSERT_NE(mouse, nullptr);
    ASSERT_NE(chair, nullptr);

    EXPECT_DOUBLE_EQ(laptop->getPrice(), 799.992); // 999.99 * 0.8
    EXPECT_DOUBLE_EQ(mouse->getPrice(), 23.992);   // 29.99 * 0.8
    EXPECT_DOUBLE_EQ(chair->getPrice(), 199.99);   // Unchanged (different category)
}

// Category Tests
TEST_F(ProductManagerTest, GetAllCategories)
{
    productManager->addProduct(product1); // Electronics
    productManager->addProduct(product2); // Electronics
    productManager->addProduct(product3); // Furniture
    productManager->addProduct(product4); // Kitchen

    std::vector<std::string> categories = productManager->getAllCategories();
    EXPECT_EQ(categories.size(), 3); // Electronics, Furniture, Kitchen

    // Should contain all unique categories
    EXPECT_NE(std::find(categories.begin(), categories.end(), "Electronics"), categories.end());
    EXPECT_NE(std::find(categories.begin(), categories.end(), "Furniture"), categories.end());
    EXPECT_NE(std::find(categories.begin(), categories.end(), "Kitchen"), categories.end());
}

TEST_F(ProductManagerTest, GetProductCountByCategory)
{
    productManager->addProduct(product1); // Electronics
    productManager->addProduct(product2); // Electronics
    productManager->addProduct(product3); // Furniture

    EXPECT_EQ(productManager->getProductCountByCategory("Electronics"), 2);
    EXPECT_EQ(productManager->getProductCountByCategory("Furniture"), 1);
    EXPECT_EQ(productManager->getProductCountByCategory("NonExistent"), 0);
}

// Validation Tests
TEST_F(ProductManagerTest, IsProductNameUnique)
{
    productManager->addProduct(product1);

    EXPECT_FALSE(productManager->isProductNameUnique(product1.getName()));
    EXPECT_TRUE(productManager->isProductNameUnique("Unique Product"));

    // Should be unique when excluding the same product
    EXPECT_TRUE(productManager->isProductNameUnique(product1.getName(), product1.getProductId()));
}

TEST_F(ProductManagerTest, ValidateProduct)
{
    EXPECT_TRUE(productManager->validateProduct(product1));

    Product invalid = product1;
    invalid.setPrice(-10.0); // Invalid price
    EXPECT_FALSE(productManager->validateProduct(invalid));
}

// Statistics Tests
TEST_F(ProductManagerTest, GetTotalProducts)
{
    EXPECT_EQ(productManager->getTotalProducts(), 0);

    productManager->addProduct(product1);
    EXPECT_EQ(productManager->getTotalProducts(), 1);

    productManager->addProduct(product2);
    EXPECT_EQ(productManager->getTotalProducts(), 2);

    productManager->deleteProduct(product1.getProductId());
    EXPECT_EQ(productManager->getTotalProducts(), 1);
}

TEST_F(ProductManagerTest, GetActiveProductsCount)
{
    productManager->addProduct(product1);
    productManager->addProduct(product2);
    productManager->addProduct(product3);

    EXPECT_EQ(productManager->getActiveProductsCount(), 3);

    productManager->deactivateProduct(product1.getProductId());
    EXPECT_EQ(productManager->getActiveProductsCount(), 2);
}

TEST_F(ProductManagerTest, GetTotalInventoryValue)
{
    productManager->addProduct(product1); // 999.99 * 50 = 49999.5
    productManager->addProduct(product2); // 29.99 * 100 = 2999

    double expectedValue = (999.99 * 50) + (29.99 * 100);
    EXPECT_DOUBLE_EQ(productManager->getTotalInventoryValue(), expectedValue);
}

TEST_F(ProductManagerTest, GetAveragePrice)
{
    productManager->addProduct(product1); // 999.99
    productManager->addProduct(product2); // 29.99
    productManager->addProduct(product4); // 9.99

    double expectedAverage = (999.99 + 29.99 + 9.99) / 3;
    EXPECT_DOUBLE_EQ(productManager->getAveragePrice(), expectedAverage);
}

TEST_F(ProductManagerTest, GetTotalStockQuantity)
{
    productManager->addProduct(product1); // 50
    productManager->addProduct(product2); // 100
    productManager->addProduct(product3); // 25

    EXPECT_EQ(productManager->getTotalStockQuantity(), 175);
}

// Edge Cases
TEST_F(ProductManagerTest, EmptySearchQueries)
{
    productManager->addProduct(product1);

    std::vector<Product> results = productManager->searchByName("");
    EXPECT_TRUE(results.empty());
}

TEST_F(ProductManagerTest, InvalidPriceRange)
{
    productManager->addProduct(product1);

    // Min price greater than max price
    std::vector<Product> results = productManager->getProductsByPriceRange(100.0, 50.0);
    EXPECT_TRUE(results.empty());
}

TEST_F(ProductManagerTest, NegativeStockOperations)
{
    productManager->addProduct(product1);

    EXPECT_FALSE(productManager->addStock(product1.getProductId(), -10));
    EXPECT_FALSE(productManager->reduceStock(product1.getProductId(), -5));
    EXPECT_FALSE(productManager->updateStock(product1.getProductId(), -20));
}

TEST_F(ProductManagerTest, InvalidDiscountPercentage)
{
    productManager->addProduct(product1);
    double originalPrice = product1.getPrice();

    EXPECT_FALSE(productManager->applyDiscount(product1.getProductId(), -10.0)); // Negative
    EXPECT_FALSE(productManager->applyDiscount(product1.getProductId(), 101.0)); // Over 100%

    Product *found = productManager->getProduct(product1.getProductId());
    ASSERT_NE(found, nullptr);
    EXPECT_DOUBLE_EQ(found->getPrice(), originalPrice); // Should remain unchanged
}