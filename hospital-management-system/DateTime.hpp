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

    DateTime(time_t creationTime)
        :mCreationTime(creationTime)
    {
        mString = ctime(&mCreationTime);
        mpLocalTime = localtime(&mCreationTime);
        mUtcString = std::to_string(mpLocalTime->tm_year + 1900) + '-' + std::to_string(mpLocalTime->tm_mon + 1) + '-' + std::to_string(mpLocalTime->tm_mday) + 'D' + std::to_string(mpLocalTime->tm_hour) + ':' + std::to_string(mpLocalTime->tm_min) + ':' + std::to_string(mpLocalTime->tm_sec) + "T-PKT";
    }
};