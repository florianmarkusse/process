#include <time.h>
#include <string>

std::string getCurrentFormattedTime() {

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    return "[" 
        + std::to_string(tm.tm_mday) 
        + "-" 
        + std::to_string(tm.tm_mon + 1) 
        + "-"
        + std::to_string(tm.tm_year + 1900)
        + " "
        + std::to_string(tm.tm_hour)
        + ":"
        + std::to_string(tm.tm_min)
        + ":"
        + std::to_string(tm.tm_sec)
        + "]";
}
