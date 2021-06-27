#pragma once
#include <string>
#include <map>

// static error handling class used with maps as key:error
class Error
{
private:
    static std::map<std::string, std::string> mErrors;

public:
    static std::string get(std::string key);
};