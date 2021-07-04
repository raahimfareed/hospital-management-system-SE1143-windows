#include <iostream>
#include <string>

#include "Config.hpp"
#include "Utils.hpp"
#include "Functions.hpp"
#include "User.hpp"
#include "File.hpp"
#include "Log.hpp"

void Log::login(const std::unique_ptr<User>& user)
{
	File logFile("log.db");
	
	std::string logLine = user->getUsername() + "(" + userTypeToString(user->getUserType()) + ") logged in at " + DateTime::getCurrent();

	logFile.write(logLine);
}

void Log::logout(const std::unique_ptr<User>& user)
{
	File logFile("log.db");

	std::string logLine = user->getUsername() + "(" + userTypeToString(user->getUserType()) + ") logged out at " + DateTime::getCurrent();

	logFile.write(logLine);
}

void Log::signup(const UserType& type, const std::string& username)
{
	File logFile("log.db");

	std::string logLine = username + "(" + userTypeToString(type) + ") signed up at " + DateTime::getCurrent();

	logFile.write(logLine);
}

void Log::show()
{
	File logFile("log.db");

	std::fstream* pFile = logFile.getFile();
	pFile->open("log.db", std::ios::in);

	std::string line;
	while (!pFile->eof())
	{
		std::getline(*pFile, line);
		printf("%s\n", line.c_str());
	}
}
