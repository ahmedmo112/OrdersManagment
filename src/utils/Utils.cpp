#include "utils/Utils.h"
#include <algorithm>
#include <cctype>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>
#include <ctime>
#include <climits>
#include <cfloat>
#include <random>
#include <functional>
#include <sys/stat.h>
#include <cerrno>
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/types.h>
#endif

namespace Utils
{

    // String utilities
    std::string trim(const std::string &str)
    {
        size_t first = str.find_first_not_of(' ');
        if (first == std::string::npos)
            return "";
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    std::vector<std::string> split(const std::string &str, char delimiter)
    {
        std::vector<std::string> result;
        std::stringstream ss(str);
        std::string item;
        while (std::getline(ss, item, delimiter))
        {
            result.push_back(item);
        }
        return result;
    }

    std::string join(const std::vector<std::string> &parts, const std::string &delimiter)
    {
        if (parts.empty())
            return "";

        std::stringstream ss;
        for (size_t i = 0; i < parts.size(); ++i)
        {
            if (i > 0)
                ss << delimiter;
            ss << parts[i];
        }
        return ss.str();
    }

    std::string toLower(const std::string &str)
    {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

    std::string toUpper(const std::string &str)
    {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }

    bool startsWith(const std::string &str, const std::string &prefix)
    {
        return str.length() >= prefix.length() &&
               str.compare(0, prefix.length(), prefix) == 0;
    }

    bool endsWith(const std::string &str, const std::string &suffix)
    {
        return str.length() >= suffix.length() &&
               str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
    }

    // Date and time utilities
    std::string getCurrentDateTime()
    {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

    std::string getCurrentDate()
    {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d");
        return ss.str();
    }

    std::string getCurrentTime()
    {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t), "%H:%M:%S");
        return ss.str();
    }

    bool isValidDate(const std::string &date)
    {
        std::regex dateRegex(R"(\d{4}-\d{2}-\d{2})");
        return std::regex_match(date, dateRegex);
    }

    // Validation utilities
    bool isValidEmail(const std::string &email)
    {
        std::regex emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        return std::regex_match(email, emailRegex);
    }

    bool isValidPhone(const std::string &phone)
    {
        std::regex phoneRegex(R"([\d\-\(\)\+\s]{10,})");
        return std::regex_match(phone, phoneRegex);
    }

    bool isNumeric(const std::string &str)
    {
        return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
    }

    bool isAlphabetic(const std::string &str)
    {
        return !str.empty() && std::all_of(str.begin(), str.end(), ::isalpha);
    }

    bool isAlphanumeric(const std::string &str)
    {
        return !str.empty() && std::all_of(str.begin(), str.end(), ::isalnum);
    }

    // Input utilities
    int getIntInput(const std::string &prompt, int minValue, int maxValue)
    {
        int value;
        std::string input;

        while (true)
        {
            std::cout << prompt;
            std::getline(std::cin, input);

            try
            {
                value = std::stoi(input);
                if (value >= minValue && value <= maxValue)
                {
                    return value;
                }
                else
                {
                    std::cout << "Please enter a value between " << minValue
                              << " and " << maxValue << ".\n";
                }
            }
            catch (const std::exception &)
            {
                std::cout << "Please enter a valid number.\n";
            }
        }
    }

    double getDoubleInput(const std::string &prompt, double minValue, double maxValue)
    {
        double value;
        std::string input;

        while (true)
        {
            std::cout << prompt;
            std::getline(std::cin, input);

            try
            {
                value = std::stod(input);
                if (value >= minValue && value <= maxValue)
                {
                    return value;
                }
                else
                {
                    std::cout << "Please enter a value between " << minValue
                              << " and " << maxValue << ".\n";
                }
            }
            catch (const std::exception &)
            {
                std::cout << "Please enter a valid number.\n";
            }
        }
    }

    std::string getStringInput(const std::string &prompt, bool allowEmpty)
    {
        std::string input;

        while (true)
        {
            std::cout << prompt;
            std::getline(std::cin, input);
            input = trim(input);

            if (!input.empty() || allowEmpty)
            {
                return input;
            }
            else
            {
                std::cout << "Input cannot be empty. Please try again.\n";
            }
        }
    }

    char getCharInput(const std::string &prompt, const std::string &validChars)
    {
        std::string input;

        while (true)
        {
            std::cout << prompt;
            std::getline(std::cin, input);

            if (input.length() == 1)
            {
                char ch = input[0];
                if (validChars.empty() || validChars.find(ch) != std::string::npos)
                {
                    return ch;
                }
            }

            if (!validChars.empty())
            {
                std::cout << "Please enter one of: " << validChars << "\n";
            }
            else
            {
                std::cout << "Please enter a single character.\n";
            }
        }
    }

    bool getYesNoInput(const std::string &prompt)
    {
        char ch = getCharInput(prompt + " (y/n): ", "yYnN");
        return ch == 'y' || ch == 'Y';
    }

    // Password utilities (simple implementation)
    std::string hashPassword(const std::string &password)
    {
        // Simple hash implementation (in production, use proper hashing like bcrypt)
        std::hash<std::string> hasher;
        size_t hashValue = hasher(password + "salt");
        return std::to_string(hashValue);
    }

    bool verifyPassword(const std::string &password, const std::string &hashedPassword)
    {
        return hashPassword(password) == hashedPassword;
    }

    std::string generateSalt()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(0, 61);

        const std::string chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::string salt;

        for (int i = 0; i < 16; ++i)
        {
            salt += chars[dis(gen)];
        }

        return salt;
    }

    // Format utilities
    std::string formatCurrency(double amount, const std::string &symbol)
    {
        std::stringstream ss;
        ss << symbol << std::fixed << std::setprecision(2) << amount;
        return ss.str();
    }

    std::string formatNumber(double number, int precision)
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(precision) << number;
        return ss.str();
    }

    std::string formatPercentage(double value)
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << (value * 100) << "%";
        return ss.str();
    }

    // File utilities
    bool createDirectory(const std::string &path)
    {
#ifdef _WIN32
        return _mkdir(path.c_str()) == 0 || errno == EEXIST;
#else
        return mkdir(path.c_str(), 0755) == 0 || errno == EEXIST;
#endif
    }

    bool fileExists(const std::string &filename)
    {
        struct stat buffer;
        return (stat(filename.c_str(), &buffer) == 0);
    }

    std::string getFileExtension(const std::string &filename)
    {
        size_t lastDot = filename.find_last_of('.');
        if (lastDot != std::string::npos)
        {
            return filename.substr(lastDot + 1);
        }
        return "";
    }

    long long getFileSize(const std::string &filename)
    {
        struct stat stat_buf;
        int rc = stat(filename.c_str(), &stat_buf);
        return rc == 0 ? stat_buf.st_size : -1;
    }

    // Console utilities
    void clearScreen()
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void pauseForInput()
    {
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
    }

    void printSeparator(char separator, int length)
    {
        std::cout << std::string(length, separator) << std::endl;
    }

    void printHeader(const std::string &title)
    {
        printSeparator('=', 60);
        std::cout << "  " << title << std::endl;
        printSeparator('=', 60);
    }

    void printError(const std::string &message)
    {
        std::cout << "[ERROR] " << message << std::endl;
    }

    void printSuccess(const std::string &message)
    {
        std::cout << "[SUCCESS] " << message << std::endl;
    }

    void printWarning(const std::string &message)
    {
        std::cout << "[WARNING] " << message << std::endl;
    }

} // namespace Utils