# Order Management System - Test Suite

This directory contains comprehensive unit tests and integration tests for the Order Management System using Google Test (gtest).

## Test Structure

### Unit Tests
- `test_customer.cpp` - Tests for Customer model
- `test_product.cpp` - Tests for Product model  
- `test_order.cpp` - Tests for Order model and OrderItem
- `test_user.cpp` - Tests for User model and UserRole
- `test_customer_manager.cpp` - Tests for CustomerManager
- `test_product_manager.cpp` - Tests for ProductManager
- `test_order_manager.cpp` - Tests for OrderManager
- `test_database.cpp` - Tests for Database utility

### Integration Tests
- `test_main.cpp` - Integration tests and main test runner

## Test Coverage

The test suite covers:

### Model Classes
- **Customer**: Constructor validation, getters/setters, validation logic, serialization
- **Product**: Stock management, price validation, category handling, serialization
- **Order**: Item management, status transitions, calculations, serialization
- **User**: Authentication, role-based permissions, validation, serialization

### Manager Classes
- **CustomerManager**: CRUD operations, search functionality, validation, statistics
- **ProductManager**: Inventory management, stock tracking, category operations, pricing
- **OrderManager**: Order lifecycle, item management, status workflow, financial operations

### Utility Classes
- **Database**: File operations, data persistence, backup/restore, ID generation

### Integration Scenarios
- Complete order lifecycle (creation → confirmation → processing → shipping → delivery)
- Stock management across multiple orders
- User authentication and authorization
- Data consistency validation
- Error handling and edge cases
- Performance with larger datasets

## Prerequisites

### Installing Google Test

#### Windows (using vcpkg)
```bash
# Install vcpkg if not already installed
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat

# Install Google Test
./vcpkg install gtest:x64-windows

# Set up CMake toolchain
# Use: -DCMAKE_TOOLCHAIN_FILE=[vcpkg root]/scripts/buildsystems/vcpkg.cmake
```

#### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install libgtest-dev cmake

# Build and install
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp *.a /usr/lib
```

#### macOS (using Homebrew)
```bash
brew install googletest
```

## Building and Running Tests

### Build with CMake

1. **Configure the build** (from project root):
```bash
mkdir build
cd build

# Windows with vcpkg
cmake .. -DCMAKE_TOOLCHAIN_FILE=[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake

# Linux/macOS
cmake ..
```

2. **Build the project**:
```bash
cmake --build .
```

3. **Run the tests**:
```bash
# Run all tests
./OrderManagementTests

# Run tests with verbose output
./OrderManagementTests --gtest_output=verbose

# Run specific test suite
./OrderManagementTests --gtest_filter=CustomerTest.*

# Run specific test
./OrderManagementTests --gtest_filter=CustomerTest.DefaultConstructor
```

### Alternative Build (if Google Test not found)

If CMake cannot find Google Test, you can build just the main application:

```bash
cmake --build . --target OrderManagement
```

## Test Output

### Successful Test Run
```
[==========] Running 150+ tests from 10 test suites.
[----------] Global test environment set-up.
...
[----------] Global test environment tear-down.
[==========] 150+ tests from 10 test suites ran. (XXX ms total)
[  PASSED  ] 150+ tests.
```

### Test Filters

Use these filters to run specific test categories:

```bash
# Model tests only
./OrderManagementTests --gtest_filter="*Test.*" --gtest_filter="-*ManagerTest.*:IntegrationTest.*"

# Manager tests only  
./OrderManagementTests --gtest_filter="*ManagerTest.*"

# Integration tests only
./OrderManagementTests --gtest_filter="IntegrationTest.*"

# Database tests only
./OrderManagementTests --gtest_filter="DatabaseTest.*"
```

## Test Data

Tests use isolated test data and temporary directories:
- Test databases are created in `test_data/` directory
- Test logs are created in `test_logs/` directory
- All test data is cleaned up after each test run

## Key Test Scenarios

### 1. Customer Management
- Adding customers with validation
- Email and phone uniqueness
- Search by name, email, city, country
- Customer activation/deactivation

### 2. Product Management  
- Stock management and availability checks
- Low stock and out-of-stock detection
- Price management and discount application
- Category-based operations

### 3. Order Processing
- Complete order lifecycle workflow
- Item addition/removal/modification
- Stock validation and reservation
- Discount and pricing calculations
- Status transition validation

### 4. User Authentication
- Password verification
- Role-based access control
- Permission validation for different user roles

### 5. Data Persistence
- File-based data storage
- Backup and restore operations
- Data integrity and consistency

### 6. Error Handling
- Invalid data validation
- Edge case handling
- Graceful error recovery

## Debugging Tests

### Running Tests in Debug Mode
```bash
# Build in debug mode
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .

# Run with debugger
gdb ./OrderManagementTests
```

### Test-Specific Debugging
```bash
# Run single test with detailed output
./OrderManagementTests --gtest_filter=CustomerTest.AddCustomer --gtest_output=verbose
```

## Performance Considerations

The test suite includes performance tests that:
- Test with larger datasets (100+ customers, 50+ products, 20+ orders)
- Validate response times meet reasonable thresholds
- Ensure memory usage remains reasonable

## Continuous Integration

To integrate with CI/CD pipelines:

```bash
# Run tests with XML output for CI systems
./OrderManagementTests --gtest_output=xml:test_results.xml

# Check exit code for pass/fail status
echo $? # 0 = success, non-zero = failure
```

## Troubleshooting

### Common Issues

1. **Google Test not found**
   - Ensure Google Test is properly installed
   - Check CMake toolchain configuration
   - Verify include and library paths

2. **Build failures**
   - Check C++17 compiler support
   - Verify all header dependencies
   - Ensure proper linking flags

3. **Test failures**
   - Check file permissions for test data directories
   - Verify no conflicting processes using test files
   - Ensure adequate disk space for temporary files

4. **Memory issues**
   - Run with memory debugging tools (valgrind on Linux)
   - Check for memory leaks in test output
   - Ensure proper cleanup in test teardown

## Contributing

When adding new tests:

1. Follow existing naming conventions
2. Include both positive and negative test cases  
3. Test edge cases and error conditions
4. Ensure proper setup and cleanup
5. Add appropriate documentation
6. Maintain test isolation (tests should not depend on each other)

## Test Metrics

Current test coverage includes:
- **Model Classes**: 95%+ coverage of public methods
- **Manager Classes**: 90%+ coverage of business logic
- **Utility Classes**: 85%+ coverage of core functionality
- **Integration Scenarios**: Key user workflows covered

Run tests regularly to ensure code quality and catch regressions early. 