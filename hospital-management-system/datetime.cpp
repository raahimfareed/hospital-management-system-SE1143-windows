#include <string>
#include <ctime>

#include "DateTime.hpp"

DateTime::DateTime()
{
    mCreationTime = time(0);
    mString = ctime(&mCreationTime);
    mpLocalTime = localtime(&mCreationTime);
    mUtcString = std::to_string(mpLocalTime->tm_year + 1900) + '-' + std::to_string(mpLocalTime->tm_mon + 1) + '-' + std::to_string(mpLocalTime->tm_mday) + 'D' + std::to_string(mpLocalTime->tm_hour) + ':' + std::to_string(mpLocalTime->tm_min) + ':' + std::to_string(mpLocalTime->tm_sec) + "T-PKT";
}