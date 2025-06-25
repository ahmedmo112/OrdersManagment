#include "utils/Logger.h"
#include "utils/Utils.h"
#include <iostream>
#include <iomanip>

std::unique_ptr<Logger> Logger::instance = nullptr;

Logger::Logger() : currentLogLevel(LogLevel::INFO)
{
}

Logger &Logger::getInstance()
{
    if (!instance)
    {
        instance = std::unique_ptr<Logger>(new Logger());
    }
    return *instance;
}

bool Logger::initialize(const std::string &filename, LogLevel level)
{
    logFilePath = filename;
    currentLogLevel = level;

    // Create logs directory if it doesn't exist
    size_t lastSlash = filename.find_last_of("/\\");
    if (lastSlash != std::string::npos)
    {
        std::string directory = filename.substr(0, lastSlash);
        Utils::createDirectory(directory);
    }

    logFile.open(filename, std::ios::app);
    if (!logFile.is_open())
    {
        std::cerr << "Failed to open log file: " << filename << std::endl;
        return false;
    }

    log(LogLevel::INFO, "Logger initialized - Application started");
    return true;
}

std::string Logger::getCurrentTimestamp() const
{
    return Utils::getCurrentDateTime();
}

std::string Logger::logLevelToString(LogLevel level) const
{
    switch (level)
    {
    case LogLevel::DEBUG:
        return "DEBUG";
    case LogLevel::INFO:
        return "INFO";
    case LogLevel::WARNING:
        return "WARNING";
    case LogLevel::ERROR:
        return "ERROR";
    case LogLevel::CRITICAL:
        return "CRITICAL";
    default:
        return "UNKNOWN";
    }
}

void Logger::log(LogLevel level, const std::string &message)
{
    if (level < currentLogLevel || !logFile.is_open())
    {
        return;
    }

    std::string timestamp = getCurrentTimestamp();
    std::string levelStr = logLevelToString(level);

    // Format: [TIMESTAMP] [LEVEL] MESSAGE
    logFile << "[" << timestamp << "] [" << levelStr << "] " << message << std::endl;
    logFile.flush();

    // Also output to console for errors and critical messages
    if (level >= LogLevel::ERROR)
    {
        std::cerr << "[" << timestamp << "] [" << levelStr << "] " << message << std::endl;
    }
}

void Logger::debug(const std::string &message)
{
    log(LogLevel::DEBUG, message);
}

void Logger::info(const std::string &message)
{
    log(LogLevel::INFO, message);
}

void Logger::warning(const std::string &message)
{
    log(LogLevel::WARNING, message);
}

void Logger::error(const std::string &message)
{
    log(LogLevel::ERROR, message);
}

void Logger::critical(const std::string &message)
{
    log(LogLevel::CRITICAL, message);
}

// Special logging for operations
void Logger::logUserLogin(const std::string &username)
{
    info("User login: " + username);
}

void Logger::logUserLogout(const std::string &username)
{
    info("User logout: " + username);
}

void Logger::logOrderCreated(int orderId, int customerId)
{
    info("Order created - Order ID: " + std::to_string(orderId) +
         ", Customer ID: " + std::to_string(customerId));
}

void Logger::logOrderStatusChanged(int orderId, const std::string &oldStatus, const std::string &newStatus)
{
    info("Order status changed - Order ID: " + std::to_string(orderId) +
         ", From: " + oldStatus + ", To: " + newStatus);
}

void Logger::logProductStockUpdate(int productId, int oldStock, int newStock)
{
    info("Product stock updated - Product ID: " + std::to_string(productId) +
         ", Old Stock: " + std::to_string(oldStock) +
         ", New Stock: " + std::to_string(newStock));
}

void Logger::close()
{
    if (logFile.is_open())
    {
        log(LogLevel::INFO, "Logger closing - Application shutdown");
        logFile.close();
    }
}

Logger::~Logger()
{
    close();
}