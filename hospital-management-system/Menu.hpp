#pragma once
#include <string>
#include <map>

class Menu
{
private:
    static std::map<std::string, std::string> mMenus;

public:
    static std::string get(std::string key);
};