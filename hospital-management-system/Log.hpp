#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "Config.hpp"
#include "Utils.hpp"
#include "DateTime.hpp"
#include "File.hpp"
#include "User.hpp"

class Log
{
public:
	static void login(const std::unique_ptr<User>& user);
	static void logout(const std::unique_ptr<User>& user);
	static void signup(const UserType& type, const std::string& username);
	static void show();
};
