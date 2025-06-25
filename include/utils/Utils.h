#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <climits>
#include <cfloat>

namespace Utils
{
    // String utilities
    std::string trim(const std::string &str);
    std::vector<std::string> split(const std::string &str, char delimiter);
    std::string join(const std::vector<std::string> &parts, const std::string &delimiter);
    std::string toLower(const std::string &str);
    std::string toUpper(const std::string &str);
    bool startsWith(const std::string &str, const std::string &prefix);
    bool endsWith(const std::string &str, const std::string &suffix);

    // Date and time utilities
    std::string getCurrentDateTime();
    std::string getCurrentDate();
    std::string getCurrentTime();
    bool isValidDate(const std::string &date);

    // Validation utilities
    bool isValidEmail(const std::string &email);
    bool isValidPhone(const std::string &phone);
    bool isNumeric(const std::string &str);
    bool isAlphabetic(const std::string &str);
    bool isAlphanumeric(const std::string &str);

    // Input utilities
    int getIntInput(const std::string &prompt, int minValue = INT_MIN, int maxValue = INT_MAX);
    double getDoubleInput(const std::string &prompt, double minValue = -DBL_MAX, double maxValue = DBL_MAX);
    std::string getStringInput(const std::string &prompt, bool allowEmpty = false);
    char getCharInput(const std::string &prompt, const std::string &validChars = "");
    bool getYesNoInput(const std::string &prompt);

    // Password utilities
    std::string hashPassword(const std::string &password);
    bool verifyPassword(const std::string &password, const std::string &hashedPassword);
    std::string generateSalt();

    // Format utilities
    std::string formatCurrency(double amount, const std::string &symbol = "$");
    std::string formatNumber(double number, int precision = 2);
    std::string formatPercentage(double value);

    // File utilities
    bool createDirectory(const std::string &path);
    bool fileExists(const std::string &filename);
    std::string getFileExtension(const std::string &filename);
    long long getFileSize(const std::string &filename);

    // Console utilities
    void clearScreen();
    void pauseForInput();
    void printSeparator(char separator = '-', int length = 50);
    void printHeader(const std::string &title);
    void printError(const std::string &message);
    void printSuccess(const std::string &message);
    void printWarning(const std::string &message);
}

#endif