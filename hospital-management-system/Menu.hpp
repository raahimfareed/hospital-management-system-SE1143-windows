#pragma once
#include <string>
#include <map>

#include "Utils.hpp"

class Menu
{
private:
    static std::map<std::pair<UserType, MenuLevel>, std::string > mMenus;

public:
    static std::string get(std::pair<UserType, MenuLevel> key);
};