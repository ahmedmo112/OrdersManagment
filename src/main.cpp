#include "ui/ConsoleUI.h"
#include "utils/Logger.h"
#include "utils/Database.h"
#include "utils/Utils.h"
#include <iostream>
#include <exception>

int main()
{
    try
    {
        // Initialize logger
        Logger &logger = Logger::getInstance();
        if (!logger.initialize("logs/application.log", LogLevel::INFO))
        {
            std::cerr << "Warning: Failed to initialize logger." << std::endl;
        }

        LOG_INFO("Application starting up...");

        // Initialize database
        Database &database = Database::getInstance();
        if (!database.initialize("data/"))
        {
            LOG_ERROR("Failed to initialize database");
            Utils::printError("Failed to initialize database system.");
            return 1;
        }

        // Create and initialize console UI
        ConsoleUI ui;
        if (!ui.initialize())
        {
            LOG_ERROR("Failed to initialize user interface");
            Utils::printError("Failed to initialize user interface.");
            return 1;
        }

        LOG_INFO("All systems initialized successfully");

        // Display welcome message
        ui.displayWelcomeMessage();

        // Run the main application loop
        ui.run();

        // Cleanup
        ui.shutdown();

        LOG_INFO("Application shutting down normally");
        logger.close();

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        LOG_CRITICAL("Fatal error: " + std::string(e.what()));
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown fatal error occurred" << std::endl;
        LOG_CRITICAL("Unknown fatal error occurred");
        return 1;
    }
}