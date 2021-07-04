#pragma once
#include <string>
#include <ctime>

// provides a way to implement unix timestamp and convert it into string easily in a unified struct
struct DateTime
{
    tm* mpLocalTime;
    time_t mCreationTime;
    std::string mString;
    std::string mUtcString;

    DateTime();
    DateTime(time_t creationTime);
    static std::string unixTimeToString(const time_t* t);
    static std::string getCurrent();
};