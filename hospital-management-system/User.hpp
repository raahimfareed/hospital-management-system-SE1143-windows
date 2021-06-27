#pragma once

#include "Config.hpp"
#include "Utils.hpp"

class User
{
public:
    User();
    User(UserType type);
private:
    UserType mUserType;
    std::string mUsername;
};