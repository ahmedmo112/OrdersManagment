#include <gtest/gtest.h>
#include "models/Product.h"

class ProductTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        validProduct = Product(1, "Laptop", "High-performance laptop",
                               "Electronics", 999.99, 50, 10);

        emptyProduct = Product();
    }

    Product validProduct;
    Product emptyProduct;
};

// Constructor Tests
TEST_F(ProductTest, DefaultConstructor)
{
    Product product;
    EXPECT_EQ(product.getProductId(), 0);
    EXPECT_EQ(product.getName(), "");
    EXPECT_EQ(product.getDescription(), "");
    EXPECT_EQ(product.getCategory(), "");
    EXPECT_DOUBLE_EQ(product.getPrice(), 0.0);
    EXPECT_EQ(product.getStockQuantity(), 0);
    EXPECT_EQ(product.getMinStockLevel(), 0);
    EXPECT_TRUE(product.getIsActive());
}

TEST_F(ProductTest, ParameterizedConstructor)
{
    EXPECT_EQ(validProduct.getProductId(), 1);
    EXPECT_EQ(validProduct.getName(), "Laptop");
    EXPECT_EQ(validProduct.getDescription(), "High-performance laptop");
    EXPECT_EQ(validProduct.getCategory(), "Electronics");
    EXPECT_DOUBLE_EQ(validProduct.getPrice(), 999.99);
    EXPECT_EQ(validProduct.getStockQuantity(), 50);
    EXPECT_EQ(validProduct.getMinStockLevel(), 10);
    EXPECT_TRUE(validProduct.getIsActive());
}

// Getter and Setter Tests
TEST_F(ProductTest, SettersAndGetters)
{
    Product product;

    product.setProductId(100);
    EXPECT_EQ(product.getProductId(), 100);

    product.setName("Smartphone");
    EXPECT_EQ(product.getName(), "Smartphone");

    product.setDescription("Latest smartphone model");
    EXPECT_EQ(product.getDescription(), "Latest smartphone model");

    product.setCategory("Mobile");
    EXPECT_EQ(product.getCategory(), "Mobile");

    product.setPrice(599.99);
    EXPECT_DOUBLE_EQ(product.getPrice(), 599.99);

    product.setStockQuantity(25);
    EXPECT_EQ(product.getStockQuantity(), 25);

    product.setMinStockLevel(5);
    EXPECT_EQ(product.getMinStockLevel(), 5);

    product.setIsActive(false);
    EXPECT_FALSE(product.getIsActive());
}

// Stock Management Tests
TEST_F(ProductTest, ReduceStockValidAmount)
{
    Product product = validProduct;
    int initialStock = product.getStockQuantity();

    EXPECT_TRUE(product.reduceStock(10));
    EXPECT_EQ(product.getStockQuantity(), initialStock - 10);
}

TEST_F(ProductTest, ReduceStockInvalidAmount)
{
    Product product = validProduct;
    int initialStock = product.getStockQuantity();

    // Try to reduce more stock than available
    EXPECT_FALSE(product.reduceStock(100));
    EXPECT_EQ(product.getStockQuantity(), initialStock); // Should remain unchanged
}

TEST_F(ProductTest, ReduceStockZeroAmount)
{
    Product product = validProduct;
    int initialStock = product.getStockQuantity();

    EXPECT_TRUE(product.reduceStock(0));
    EXPECT_EQ(product.getStockQuantity(), initialStock);
}

TEST_F(ProductTest, ReduceStockNegativeAmount)
{
    Product product = validProduct;
    int initialStock = product.getStockQuantity();

    EXPECT_FALSE(product.reduceStock(-5));
    EXPECT_EQ(product.getStockQuantity(), initialStock);
}

TEST_F(ProductTest, AddStock)
{
    Product product = validProduct;
    int initialStock = product.getStockQuantity();

    product.addStock(20);
    EXPECT_EQ(product.getStockQuantity(), initialStock + 20);
}

TEST_F(ProductTest, AddZeroStock)
{
    Product product = validProduct;
    int initialStock = product.getStockQuantity();

    product.addStock(0);
    EXPECT_EQ(product.getStockQuantity(), initialStock);
}

TEST_F(ProductTest, IsLowStock)
{
    Product product = validProduct;
    product.setStockQuantity(5); // Below minStockLevel (10)

    EXPECT_TRUE(product.isLowStock());

    product.setStockQuantity(15); // Above minStockLevel
    EXPECT_FALSE(product.isLowStock());

    product.setStockQuantity(10);      // Equal to minStockLevel
    EXPECT_TRUE(product.isLowStock()); // Should be considered low when equal
}

TEST_F(ProductTest, IsInStock)
{
    Product product = validProduct;

    EXPECT_TRUE(product.isInStock(1));
    EXPECT_TRUE(product.isInStock(50));
    EXPECT_FALSE(product.isInStock(51));
    EXPECT_FALSE(product.isInStock(100));

    // Test default parameter
    EXPECT_TRUE(product.isInStock());

    // Test with zero stock
    product.setStockQuantity(0);
    EXPECT_FALSE(product.isInStock());
    EXPECT_FALSE(product.isInStock(1));
}

// Validation Tests
TEST_F(ProductTest, ValidProduct)
{
    EXPECT_TRUE(validProduct.isValid());
}

TEST_F(ProductTest, InvalidProductEmptyName)
{
    Product product = validProduct;
    product.setName("");
    EXPECT_FALSE(product.isValid());
}

TEST_F(ProductTest, InvalidProductNegativePrice)
{
    Product product = validProduct;
    product.setPrice(-10.0);
    EXPECT_FALSE(product.isValid());
}

TEST_F(ProductTest, InvalidProductZeroPrice)
{
    Product product = validProduct;
    product.setPrice(0.0);
    EXPECT_FALSE(product.isValid()); // Assuming zero price is invalid
}

TEST_F(ProductTest, InvalidProductNegativeStock)
{
    Product product = validProduct;
    product.setStockQuantity(-5);
    EXPECT_FALSE(product.isValid());
}

TEST_F(ProductTest, InvalidProductNegativeMinStock)
{
    Product product = validProduct;
    product.setMinStockLevel(-1);
    EXPECT_FALSE(product.isValid());
}

// Price Tests
TEST_F(ProductTest, PriceEdgeCases)
{
    Product product = validProduct;

    // Very small price
    product.setPrice(0.01);
    EXPECT_DOUBLE_EQ(product.getPrice(), 0.01);

    // Large price
    product.setPrice(99999.99);
    EXPECT_DOUBLE_EQ(product.getPrice(), 99999.99);
}

// ToString Tests
TEST_F(ProductTest, ToStringContainsProductInfo)
{
    std::string result = validProduct.toString();

    EXPECT_NE(result.find("Laptop"), std::string::npos);
    EXPECT_NE(result.find("999.99"), std::string::npos);
    EXPECT_NE(result.find("Electronics"), std::string::npos);
    EXPECT_NE(result.find("50"), std::string::npos);
}

// Serialization Tests
TEST_F(ProductTest, SerializationAndDeserialization)
{
    std::string serialized = validProduct.serialize();
    EXPECT_FALSE(serialized.empty());

    Product deserialized = Product::deserialize(serialized);

    EXPECT_EQ(deserialized.getProductId(), validProduct.getProductId());
    EXPECT_EQ(deserialized.getName(), validProduct.getName());
    EXPECT_EQ(deserialized.getDescription(), validProduct.getDescription());
    EXPECT_EQ(deserialized.getCategory(), validProduct.getCategory());
    EXPECT_DOUBLE_EQ(deserialized.getPrice(), validProduct.getPrice());
    EXPECT_EQ(deserialized.getStockQuantity(), validProduct.getStockQuantity());
    EXPECT_EQ(deserialized.getMinStockLevel(), validProduct.getMinStockLevel());
    EXPECT_EQ(deserialized.getIsActive(), validProduct.getIsActive());
}

TEST_F(ProductTest, SerializationRoundTrip)
{
    Product original = validProduct;

    for (int i = 0; i < 3; ++i)
    {
        std::string serialized = original.serialize();
        original = Product::deserialize(serialized);
    }

    EXPECT_EQ(original.getProductId(), validProduct.getProductId());
    EXPECT_EQ(original.getName(), validProduct.getName());
    EXPECT_DOUBLE_EQ(original.getPrice(), validProduct.getPrice());
}

// Edge Cases
TEST_F(ProductTest, ProductWithSpecialCharacters)
{
    Product product(2, "Café Table", "Handcrafted café table", "Furniture",
                    299.50, 15, 3);

    EXPECT_TRUE(product.isValid());

    std::string serialized = product.serialize();
    Product deserialized = Product::deserialize(serialized);

    EXPECT_EQ(deserialized.getName(), "Café Table");
    EXPECT_EQ(deserialized.getDescription(), "Handcrafted café table");
}

TEST_F(ProductTest, ProductWithLongDescription)
{
    std::string longDescription(500, 'A');

    Product product(3, "Test Product", longDescription, "Test",
                    100.0, 10, 2);

    EXPECT_TRUE(product.isValid());
    EXPECT_EQ(product.getDescription(), longDescription);
}

TEST_F(ProductTest, InactiveProduct)
{
    Product product = validProduct;
    product.setIsActive(false);

    EXPECT_FALSE(product.getIsActive());
    EXPECT_TRUE(product.isValid()); // Inactive products should still be valid
}

// Stock Boundary Tests
TEST_F(ProductTest, StockBoundaryConditions)
{
    Product product = validProduct;

    // Reduce stock to exactly zero
    product.setStockQuantity(10);
    EXPECT_TRUE(product.reduceStock(10));
    EXPECT_EQ(product.getStockQuantity(), 0);
    EXPECT_FALSE(product.isInStock());

    // Try to reduce from zero
    EXPECT_FALSE(product.reduceStock(1));
    EXPECT_EQ(product.getStockQuantity(), 0);

    // Add stock back
    product.addStock(5);
    EXPECT_EQ(product.getStockQuantity(), 5);
    EXPECT_TRUE(product.isInStock());
}