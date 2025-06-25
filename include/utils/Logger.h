#pragma once
#include <string>
#include <fstream>
#include <memory>

enum class LogLevel
{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class Logger
{
private:
    static std::unique_ptr<Logger> instance;
    std::ofstream logFile;
    LogLevel currentLogLevel;
    std::string logFilePath;

    Logger();
    std::string getCurrentTimestamp() const;
    std::string logLevelToString(LogLevel level) const;

public:
    static Logger &getInstance();

    // Configuration
    bool initialize(const std::string &filename = "logs/application.log",
                    LogLevel level = LogLevel::INFO);
    void setLogLevel(LogLevel level) { currentLogLevel = level; }
    LogLevel getLogLevel() const { return currentLogLevel; }

    // Logging methods
    void log(LogLevel level, const std::string &message);
    void debug(const std::string &message);
    void info(const std::string &message);
    void warning(const std::string &message);
    void error(const std::string &message);
    void critical(const std::string &message);

    // Special logging for operations
    void logUserLogin(const std::string &username);
    void logUserLogout(const std::string &username);
    void logOrderCreated(int orderId, int customerId);
    void logOrderStatusChanged(int orderId, const std::string &oldStatus, const std::string &newStatus);
    void logProductStockUpdate(int productId, int oldStock, int newStock);

    // Cleanup
    void close();
    ~Logger();

    // Delete copy constructor and assignment operator
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;
};

// Convenience macros for logging
#define LOG_DEBUG(msg) Logger::getInstance().debug(msg)
#define LOG_INFO(msg) Logger::getInstance().info(msg)
#define LOG_WARNING(msg) Logger::getInstance().warning(msg)
#define LOG_ERROR(msg) Logger::getInstance().error(msg)
#define LOG_CRITICAL(msg) Logger::getInstance().critical(msg)