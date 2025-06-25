#include "ui/ConsoleUI.h"
#include "utils/Utils.h"
#include "utils/Logger.h"
#include <iostream>
#include <iomanip>

ConsoleUI::ConsoleUI() : isRunning(false)
{
}

ConsoleUI::~ConsoleUI()
{
    shutdown();
}

bool ConsoleUI::initialize()
{
    try
    {
        // Initialize managers
        userManager = std::make_unique<UserManager>();
        customerManager = std::make_unique<CustomerManager>();
        productManager = std::make_unique<ProductManager>();
        orderManager = std::make_unique<OrderManager>(productManager.get(), customerManager.get());

        LOG_INFO("Console UI initialized successfully");
        return true;
    }
    catch (const std::exception &e)
    {
        LOG_ERROR("Failed to initialize ConsoleUI: " + std::string(e.what()));
        return false;
    }
}

void ConsoleUI::run()
{
    isRunning = true;

    while (isRunning)
    {
        if (!userManager->isLoggedIn())
        {
            showLoginMenu();
        }
        else
        {
            showMainMenu();
        }
    }
}

void ConsoleUI::shutdown()
{
    if (userManager && userManager->isLoggedIn())
    {
        handleLogout();
    }

    // Reset managers
    orderManager.reset();
    productManager.reset();
    customerManager.reset();
    userManager.reset();

    LOG_INFO("Console UI shutdown completed");
}

void ConsoleUI::showLoginMenu()
{
    clearScreen();
    displayHeader("ORDER MANAGEMENT SYSTEM - LOGIN");

    std::cout << "1. Login\n";
    std::cout << "2. Exit\n";

    int choice = getMenuChoice(1, 2);

    switch (choice)
    {
    case 1:
        handleLogin();
        break;
    case 2:
        displayGoodbyeMessage();
        isRunning = false;
        break;
    }
}

void ConsoleUI::showMainMenu()
{
    clearScreen();
    displayHeader("ORDER MANAGEMENT SYSTEM - MAIN MENU");

    User *currentUser = userManager->getCurrentUser();
    if (currentUser)
    {
        std::cout << "Welcome, " << currentUser->getFullName()
                  << " (" << currentUser->getRoleString() << ")\n\n";
    }

    std::cout << "1. Customer Management\n";
    std::cout << "2. Product Management\n";
    std::cout << "3. Order Management\n";
    std::cout << "4. Reports\n";

    if (userManager->canManageUsers())
    {
        std::cout << "5. User Management\n";
        std::cout << "6. Settings\n";
        std::cout << "7. Logout\n";
        std::cout << "8. Exit\n";
    }
    else
    {
        std::cout << "5. Logout\n";
        std::cout << "6. Exit\n";
    }

    int maxChoice = userManager->canManageUsers() ? 8 : 6;
    int choice = getMenuChoice(1, maxChoice);

    if (userManager->canManageUsers())
    {
        switch (choice)
        {
        case 1:
            showCustomerMenu();
            break;
        case 2:
            showProductMenu();
            break;
        case 3:
            showOrderMenu();
            break;
        case 4:
            showReportsMenu();
            break;
        case 5:
            showUserManagementMenu();
            break;
        case 6:
            showSettingsMenu();
            break;
        case 7:
            handleLogout();
            break;
        case 8:
            displayGoodbyeMessage();
            isRunning = false;
            break;
        }
    }
    else
    {
        switch (choice)
        {
        case 1:
            showCustomerMenu();
            break;
        case 2:
            showProductMenu();
            break;
        case 3:
            showOrderMenu();
            break;
        case 4:
            showReportsMenu();
            break;
        case 5:
            handleLogout();
            break;
        case 6:
            displayGoodbyeMessage();
            isRunning = false;
            break;
        }
    }
}

void ConsoleUI::showCustomerMenu()
{
    clearScreen();
    displayHeader("CUSTOMER MANAGEMENT");

    std::cout << "1. Add Customer\n";
    std::cout << "2. View All Customers\n";
    std::cout << "3. Search Customers\n";
    std::cout << "4. Update Customer\n";
    std::cout << "5. Delete Customer\n";
    std::cout << "6. Customer Reports\n";
    std::cout << "7. Back to Main Menu\n";

    int choice = getMenuChoice(1, 7);

    switch (choice)
    {
    case 1:
        handleAddCustomer();
        break;
    case 2:
        handleViewCustomers();
        break;
    case 3:
        handleSearchCustomers();
        break;
    case 4:
        handleUpdateCustomer();
        break;
    case 5:
        handleDeleteCustomer();
        break;
    case 6:
        handleCustomerReports();
        break;
    case 7:
        return;
    }

    waitForInput();
}

void ConsoleUI::showProductMenu()
{
    clearScreen();
    displayHeader("PRODUCT MANAGEMENT");

    std::cout << "1. Add Product\n";
    std::cout << "2. View All Products\n";
    std::cout << "3. Search Products\n";
    std::cout << "4. Update Product\n";
    std::cout << "5. Delete Product\n";
    std::cout << "6. Stock Management\n";
    std::cout << "7. Product Reports\n";
    std::cout << "8. Back to Main Menu\n";

    int choice = getMenuChoice(1, 8);

    switch (choice)
    {
    case 1:
        handleAddProduct();
        break;
    case 2:
        handleViewProducts();
        break;
    case 3:
        handleSearchProducts();
        break;
    case 4:
        handleUpdateProduct();
        break;
    case 5:
        handleDeleteProduct();
        break;
    case 6:
        handleStockManagement();
        break;
    case 7:
        handleProductReports();
        break;
    case 8:
        return;
    }

    waitForInput();
}

void ConsoleUI::showOrderMenu()
{
    clearScreen();
    displayHeader("ORDER MANAGEMENT");

    std::cout << "1. Create Order\n";
    std::cout << "2. View All Orders\n";
    std::cout << "3. Search Orders\n";
    std::cout << "4. Update Order\n";
    std::cout << "5. Update Order Status\n";
    std::cout << "6. Order Reports\n";
    std::cout << "7. Back to Main Menu\n";

    int choice = getMenuChoice(1, 7);

    switch (choice)
    {
    case 1:
        handleCreateOrder();
        break;
    case 2:
        handleViewOrders();
        break;
    case 3:
        handleSearchOrders();
        break;
    case 4:
        handleUpdateOrder();
        break;
    case 5:
        handleOrderStatus();
        break;
    case 6:
        handleOrderReports();
        break;
    case 7:
        return;
    }

    waitForInput();
}

void ConsoleUI::showReportsMenu()
{
    clearScreen();
    displayHeader("REPORTS");

    std::cout << "1. Sales Reports\n";
    std::cout << "2. Inventory Reports\n";
    std::cout << "3. Customer Reports\n";
    std::cout << "4. System Reports\n";
    std::cout << "5. Back to Main Menu\n";

    int choice = getMenuChoice(1, 5);

    switch (choice)
    {
    case 1:
        handleSalesReports();
        break;
    case 2:
        handleInventoryReports();
        break;
    case 3:
        handleCustomerReports();
        break;
    case 4:
        handleSystemReports();
        break;
    case 5:
        return;
    }

    waitForInput();
}

void ConsoleUI::showUserManagementMenu()
{
    if (!checkPermission("manage_users"))
        return;

    clearScreen();
    displayHeader("USER MANAGEMENT");

    std::cout << "1. Add User\n";
    std::cout << "2. View Users\n";
    std::cout << "3. Update User\n";
    std::cout << "4. Delete User\n";
    std::cout << "5. Change Password\n";
    std::cout << "6. User Permissions\n";
    std::cout << "7. Back to Main Menu\n";

    int choice = getMenuChoice(1, 7);

    switch (choice)
    {
    case 1:
        handleAddUser();
        break;
    case 2:
        handleViewUsers();
        break;
    case 3:
        handleUpdateUser();
        break;
    case 4:
        handleDeleteUser();
        break;
    case 5:
        handleChangePassword();
        break;
    case 6:
        handleUserPermissions();
        break;
    case 7:
        return;
    }

    waitForInput();
}

void ConsoleUI::showSettingsMenu()
{
    if (!checkPermission("manage_settings"))
        return;

    clearScreen();
    displayHeader("SYSTEM SETTINGS");

    std::cout << "1. System Settings\n";
    std::cout << "2. Data Backup\n";
    std::cout << "3. Data Restore\n";
    std::cout << "4. Log Settings\n";
    std::cout << "5. Back to Main Menu\n";

    int choice = getMenuChoice(1, 5);

    switch (choice)
    {
    case 1:
        handleSystemSettings();
        break;
    case 2:
        handleDataBackup();
        break;
    case 3:
        handleDataRestore();
        break;
    case 4:
        handleLogSettings();
        break;
    case 5:
        return;
    }

    waitForInput();
}

void ConsoleUI::handleLogin()
{
    clearScreen();
    displayHeader("USER LOGIN");

    std::string username = Utils::getStringInput("Username: ");
    std::string password = Utils::getStringInput("Password: ");

    if (userManager->login(username, password))
    {
        displaySuccess("Login successful!");
        LOG_INFO("User logged in: " + username);
    }
    else
    {
        displayError("Invalid username or password!");
        LOG_WARNING("Failed login attempt for username: " + username);
    }

    waitForInput();
}

void ConsoleUI::handleLogout()
{
    if (userManager->isLoggedIn())
    {
        std::string username = userManager->getCurrentUser()->getUsername();
        userManager->logout();
        displaySuccess("Logged out successfully!");
        LOG_INFO("User logged out: " + username);
    }
}

// Basic implementations for essential handlers
void ConsoleUI::handleAddCustomer()
{
    if (!checkPermission("manage_customers"))
        return;

    clearScreen();
    displayHeader("ADD NEW CUSTOMER");

    std::string name = Utils::getStringInput("Customer Name: ");
    std::string email = Utils::getStringInput("Email: ");
    std::string phone = Utils::getStringInput("Phone: ");
    std::string address = Utils::getStringInput("Address: ");
    std::string city = Utils::getStringInput("City: ");
    std::string country = Utils::getStringInput("Country: ");

    Customer customer(0, name, email, phone, address, city, country);

    if (customerManager->addCustomer(customer))
    {
        displaySuccess("Customer added successfully!");
    }
    else
    {
        displayError("Failed to add customer!");
    }
}

void ConsoleUI::handleViewCustomers()
{
    clearScreen();
    displayHeader("ALL CUSTOMERS");

    auto customers = customerManager->getAllCustomers();

    if (customers.empty())
    {
        displayMessage("No customers found.");
        return;
    }

    std::cout << std::left << std::setw(5) << "ID"
              << std::setw(20) << "Name"
              << std::setw(25) << "Email"
              << std::setw(15) << "Phone"
              << std::setw(15) << "City"
              << std::setw(10) << "Status" << std::endl;
    Utils::printSeparator('-', 90);

    for (const auto &customer : customers)
    {
        std::cout << std::left << std::setw(5) << customer.getCustomerId()
                  << std::setw(20) << customer.getName().substr(0, 19)
                  << std::setw(25) << customer.getEmail().substr(0, 24)
                  << std::setw(15) << customer.getPhone().substr(0, 14)
                  << std::setw(15) << customer.getCity().substr(0, 14)
                  << std::setw(10) << (customer.getIsActive() ? "Active" : "Inactive") << std::endl;
    }
}

// Placeholder implementations for other handlers
void ConsoleUI::handleSearchCustomers() { displayMessage("Search Customers - Not implemented yet"); }
void ConsoleUI::handleUpdateCustomer() { displayMessage("Update Customer - Not implemented yet"); }
void ConsoleUI::handleDeleteCustomer() { displayMessage("Delete Customer - Not implemented yet"); }
void ConsoleUI::handleCustomerReports() { displayMessage("Customer Reports - Not implemented yet"); }
void ConsoleUI::handleAddProduct() { displayMessage("Add Product - Not implemented yet"); }
void ConsoleUI::handleViewProducts() { displayMessage("View Products - Not implemented yet"); }
void ConsoleUI::handleSearchProducts() { displayMessage("Search Products - Not implemented yet"); }
void ConsoleUI::handleUpdateProduct() { displayMessage("Update Product - Not implemented yet"); }
void ConsoleUI::handleDeleteProduct() { displayMessage("Delete Product - Not implemented yet"); }
void ConsoleUI::handleStockManagement() { displayMessage("Stock Management - Not implemented yet"); }
void ConsoleUI::handleProductReports() { displayMessage("Product Reports - Not implemented yet"); }
void ConsoleUI::handleCreateOrder() { displayMessage("Create Order - Not implemented yet"); }
void ConsoleUI::handleViewOrders() { displayMessage("View Orders - Not implemented yet"); }
void ConsoleUI::handleSearchOrders() { displayMessage("Search Orders - Not implemented yet"); }
void ConsoleUI::handleUpdateOrder() { displayMessage("Update Order - Not implemented yet"); }
void ConsoleUI::handleOrderStatus() { displayMessage("Order Status - Not implemented yet"); }
void ConsoleUI::handleOrderReports() { displayMessage("Order Reports - Not implemented yet"); }
void ConsoleUI::handleSalesReports() { displayMessage("Sales Reports - Not implemented yet"); }
void ConsoleUI::handleInventoryReports() { displayMessage("Inventory Reports - Not implemented yet"); }
void ConsoleUI::handleSystemReports() { displayMessage("System Reports - Not implemented yet"); }
void ConsoleUI::handleAddUser() { displayMessage("Add User - Not implemented yet"); }
void ConsoleUI::handleViewUsers() { displayMessage("View Users - Not implemented yet"); }
void ConsoleUI::handleUpdateUser() { displayMessage("Update User - Not implemented yet"); }
void ConsoleUI::handleDeleteUser() { displayMessage("Delete User - Not implemented yet"); }
void ConsoleUI::handleChangePassword() { displayMessage("Change Password - Not implemented yet"); }
void ConsoleUI::handleUserPermissions() { displayMessage("User Permissions - Not implemented yet"); }
void ConsoleUI::handleSystemSettings() { displayMessage("System Settings - Not implemented yet"); }
void ConsoleUI::handleDataBackup() { displayMessage("Data Backup - Not implemented yet"); }
void ConsoleUI::handleDataRestore() { displayMessage("Data Restore - Not implemented yet"); }
void ConsoleUI::handleLogSettings() { displayMessage("Log Settings - Not implemented yet"); }

// Utility UI methods
void ConsoleUI::displayHeader(const std::string &title)
{
    Utils::printHeader(title);
}

void ConsoleUI::displayMessage(const std::string &message, bool isError)
{
    if (isError)
    {
        Utils::printError(message);
    }
    else
    {
        std::cout << message << std::endl;
    }
}

void ConsoleUI::displaySuccess(const std::string &message)
{
    Utils::printSuccess(message);
}

void ConsoleUI::displayError(const std::string &message)
{
    Utils::printError(message);
}

void ConsoleUI::displayWarning(const std::string &message)
{
    Utils::printWarning(message);
}

void ConsoleUI::waitForInput()
{
    Utils::pauseForInput();
}

int ConsoleUI::getMenuChoice(int minChoice, int maxChoice)
{
    return Utils::getIntInput("Please enter your choice: ", minChoice, maxChoice);
}

bool ConsoleUI::confirmAction(const std::string &action)
{
    return Utils::getYesNoInput("Are you sure you want to " + action + "?");
}

bool ConsoleUI::checkPermission(const std::string &operation)
{
    if (!userManager->hasPermission(operation))
    {
        displayAccessDenied();
        return false;
    }
    return true;
}

void ConsoleUI::displayAccessDenied()
{
    displayError("Access denied! You don't have permission to perform this operation.");
    waitForInput();
}

void ConsoleUI::displayWelcomeMessage()
{
    clearScreen();
    std::cout << R"(
╔══════════════════════════════════════════════════════════════════════════════╗
║                          WELCOME TO ORDER MANAGEMENT SYSTEM                 ║
║                                                                              ║
║  A comprehensive solution for managing customers, products, and orders       ║
║  with role-based access control and advanced reporting capabilities.         ║
║                                                                              ║
║  Features:                                                                   ║
║  • Customer Management                                                       ║
║  • Product Inventory Management                                              ║
║  • Order Processing & Tracking                                               ║
║  • Sales & Inventory Reports                                                 ║
║  • User Management & Security                                                ║
║                                                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝
)" << std::endl;

    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
}

void ConsoleUI::displayGoodbyeMessage()
{
    clearScreen();
    std::cout << R"(
╔══════════════════════════════════════════════════════════════════════════════╗
║                      THANK YOU FOR USING ORDER MANAGEMENT SYSTEM            ║
║                                                                              ║
║                              Goodbye and have a great day!                  ║
║                                                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝
)" << std::endl;
}

void ConsoleUI::clearScreen()
{
    Utils::clearScreen();
}