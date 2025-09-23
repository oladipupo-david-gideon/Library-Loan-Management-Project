#ifndef LIBRARYCLOCK_H
#define LIBRARYCLOCK_H

#include <chrono>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

class LibraryClock {
    public:
        static string getCurrentDate() {
            auto now = chrono::system_clock::now();
            time_t now_time = chrono::system_clock::to_time_t(now);
            tm *ltm = localtime(&now_time);
    
            ostringstream oss;
            oss << setw(2) << setfill('0') << (ltm->tm_mon + 1) << "/"  // Month
                << setw(2) << setfill('0') << ltm->tm_mday << "/"       // Day
                << (ltm->tm_year + 1900);                               // Full Year
    
            return oss.str();
        }
};

#endif