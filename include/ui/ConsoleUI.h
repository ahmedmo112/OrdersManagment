#pragma once
#include "managers/CustomerManager.h"
#include "managers/ProductManager.h"
#include "managers/OrderManager.h"
#include "managers/UserManager.h"
#include <memory>

class ConsoleUI
{
private:
    std::unique_ptr<UserManager> userManager;
    std::unique_ptr<CustomerManager> customerManager;
    std::unique_ptr<ProductManager> productManager;
    std::unique_ptr<OrderManager> orderManager;
    bool isRunning;

    // Menu methods
    void showMainMenu();
    void showLoginMenu();
    void showCustomerMenu();
    void showProductMenu();
    void showOrderMenu();
    void showReportsMenu();
    void showUserManagementMenu();
    void showSettingsMenu();

    // Authentication UI
    void handleLogin();
    void handleLogout();

    // Customer management UI
    void handleAddCustomer();
    void handleViewCustomers();
    void handleSearchCustomers();
    void handleUpdateCustomer();
    void handleDeleteCustomer();

    // Product management UI
    void handleAddProduct();
    void handleViewProducts();
    void handleSearchProducts();
    void handleUpdateProduct();
    void handleDeleteProduct();
    void handleStockManagement();

    // Order management UI
    void handleCreateOrder();
    void handleViewOrders();
    void handleSearchOrders();
    void handleUpdateOrder();
    void handleOrderStatus();

    // Reports UI
    void handleSalesReports();
    void handleInventoryReports();
    void handleCustomerReports();
    void handleProductReports();
    void handleOrderReports();
    void handleSystemReports();

    // User management UI
    void handleAddUser();
    void handleViewUsers();
    void handleUpdateUser();
    void handleDeleteUser();
    void handleChangePassword();
    void handleUserPermissions();

    // Settings UI
    void handleSystemSettings();
    void handleDataBackup();
    void handleDataRestore();
    void handleLogSettings();

    // Utility UI methods
    void displayHeader(const std::string &title);
    void displayMessage(const std::string &message, bool isError = false);
    void displaySuccess(const std::string &message);
    void displayError(const std::string &message);
    void displayWarning(const std::string &message);
    void waitForInput();
    int getMenuChoice(int minChoice, int maxChoice);
    bool confirmAction(const std::string &action);

    // Access control
    bool checkPermission(const std::string &operation);
    void displayAccessDenied();

public:
    ConsoleUI();
    ~ConsoleUI();

    // Main application control
    bool initialize();
    void run();
    void shutdown();

    // Menu navigation
    void displayWelcomeMessage();
    void displayGoodbyeMessage();
    void clearScreen();

    // Data import/export
    void handleDataImportExport();

    // Permission checks
    bool hasPermission(UserRole requiredRole) const;
    bool isLoggedIn() const;
};