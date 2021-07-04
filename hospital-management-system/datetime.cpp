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

DateTime::DateTime(time_t creationTime)
    :mCreationTime(creationTime)
{
    mString = ctime(&mCreationTime);
    mpLocalTime = localtime(&mCreationTime);
    mUtcString = std::to_string(mpLocalTime->tm_year + 1900) + '-' + std::to_string(mpLocalTime->tm_mon + 1) + '-' + std::to_string(mpLocalTime->tm_mday) + ' ' + std::to_string(mpLocalTime->tm_hour) + ':' + std::to_string(mpLocalTime->tm_min) + ':' + std::to_string(mpLocalTime->tm_sec) + " PKT";
}

std::string DateTime::unixTimeToString(const time_t* t)
{
    tm* localTime = localtime(t);
    return std::to_string(localTime->tm_year + 1900) + '-' + std::to_string(localTime->tm_mon + 1) + '-' + std::to_string(localTime->tm_mday) + ' ' + std::to_string(localTime->tm_hour) + ':' + std::to_string(localTime->tm_min) + ':' + std::to_string(localTime->tm_sec) + " PKT";
}

std::string DateTime::getCurrent()
{
    time_t t = time(0);
    tm* lt = localtime(&t);
    return std::to_string(lt->tm_year + 1900) + '-' + std::to_string(lt->tm_mon + 1) + '-' + std::to_string(lt->tm_mday) + ' ' + std::to_string(lt->tm_hour) + ':' + std::to_string(lt->tm_min) + ':' + std::to_string(lt->tm_sec) + " PKT";
}
