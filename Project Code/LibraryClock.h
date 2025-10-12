#ifndef LIBRARYCLOCK_H
#define LIBRARYCLOCK_H

#include <chrono>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>

class LibraryClock {
public:
    static std::string getCurrentDate() {
        auto now = std::chrono::system_clock::now();
        time_t now_time = std::chrono::system_clock::to_time_t(now);
        tm ltm;
        
        // Use localtime_s on Windows or localtime_r on POSIX for thread safety
        #ifdef _WIN32
            localtime_s(&ltm, &now_time);
        #else
            localtime_r(&now_time, &ltm);
        #endif

        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << (ltm.tm_mon + 1) << "/"  // Month
            << std::setw(2) << std::setfill('0') << ltm.tm_mday << "/"       // Day
            << (ltm.tm_year + 1900);                               // Full Year

        return oss.str();
    }
};

#endif