cmake_minimum_required(VERSION 3.16)
project(OrderManagement)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Create directories for output
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/data)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/logs)

# Source files (excluding main.cpp for library)
set(LIBRARY_SOURCES
    src/models/Customer.cpp
    src/models/Product.cpp
    src/models/Order.cpp
    src/models/User.cpp
    src/managers/CustomerManager.cpp
    src/managers/ProductManager.cpp
    src/managers/OrderManager.cpp
    src/managers/UserManager.cpp
    src/utils/Database.cpp
    src/utils/Logger.cpp
    src/utils/Utils.cpp
    src/ui/ConsoleUI.cpp
)

# Header files
set(HEADERS
    include/models/Customer.h
    include/models/Product.h
    include/models/Order.h
    include/models/User.h
    include/managers/CustomerManager.h
    include/managers/ProductManager.h
    include/managers/OrderManager.h
    include/managers/UserManager.h
    include/utils/Database.h
    include/utils/Logger.h
    include/utils/Utils.h
    include/ui/ConsoleUI.h
)

# Create a library for the main application logic
add_library(OrderManagementLib ${LIBRARY_SOURCES} ${HEADERS})

# Create main executable
add_executable(OrderManagement src/main.cpp)
target_link_libraries(OrderManagement OrderManagementLib)

# Find and include Google Test
find_package(GTest)
if(GTest_FOUND)
    enable_testing()
    
    # Test sources
    set(TEST_SOURCES
        tests/test_customer.cpp
        tests/test_product.cpp
        tests/test_order.cpp
        tests/test_user.cpp
        tests/test_customer_manager.cpp
        tests/test_product_manager.cpp
        tests/test_order_manager.cpp
        tests/test_database.cpp
        tests/test_main.cpp
    )
    
    # Create test executable
    add_executable(OrderManagementTests ${TEST_SOURCES})
    target_link_libraries(OrderManagementTests 
        OrderManagementLib 
        GTest::gtest 
        GTest::gtest_main
    )
    
    # Add test discovery
    include(GoogleTest)
    gtest_discover_tests(OrderManagementTests)
else()
    message(WARNING "Google Test not found. Tests will not be built.")
    message(STATUS "To install Google Test on Windows with vcpkg:")
    message(STATUS "  vcpkg install gtest")
    message(STATUS "Then run cmake with: -DCMAKE_TOOLCHAIN_FILE=[vcpkg root]/scripts/buildsystems/vcpkg.cmake")
endif()

# Compiler flags
if(MSVC)
    target_compile_options(OrderManagementLib PRIVATE /W4)
    target_compile_options(OrderManagement PRIVATE /W4)
    if(GTest_FOUND)
        target_compile_options(OrderManagementTests PRIVATE /W4)
    endif()
else()
    target_compile_options(OrderManagementLib PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(OrderManagement PRIVATE -Wall -Wextra -Wpedantic)
    if(GTest_FOUND)
        target_compile_options(OrderManagementTests PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endif()

# Copy data files to build directory
configure_file(${CMAKE_SOURCE_DIR}/data/users.txt ${CMAKE_BINARY_DIR}/data/users.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/data/customers.txt ${CMAKE_BINARY_DIR}/data/customers.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/data/products.txt ${CMAKE_BINARY_DIR}/data/products.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/data/orders.txt ${CMAKE_BINARY_DIR}/data/orders.txt COPYONLY) 