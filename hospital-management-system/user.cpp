#include "User.hpp"
#include "Utils.hpp"
#include "Functions.hpp"

User::User()
	:mUserType(UserType::Guest), mUsername("Guest"), mPassword(""), mJoinDate(DateTime())
{}

User::User(UserType type)
	: mUserType(type), mUsername("Guest"), mPassword(""), mJoinDate(DateTime())
{}

User::User(time_t creationTime)
    :mJoinDate(DateTime(creationTime)), mUserType(UserType::Guest), mUsername("Guest"), mPassword("")
{}

User::User(std::string username, std::string password)
    : mUsername(username), mPassword(password), mJoinDate(DateTime()), mUserType(UserType::Guest)
{
}

User::User(std::string username, std::string password, UserType userType)
    : mUsername(username), mPassword(password), mUserType(userType), mJoinDate(DateTime())
{}

User::User(std::string username, std::string password, UserType userType, time_t creationTime)
    : mUsername(username), mPassword(password), mUserType(userType), mJoinDate(DateTime(creationTime))
{}

void User::setUsername(const std::string& username)
{
    mUsername = username;
}

void User::setPassword(const std::string& password)
{
    mPassword = password;
}

void User::setUserType(const UserType& type)
{
    mUserType = type;
}

std::string User::getUsername() const
{
    return mUsername;
}

std::string User::getPassword() const
{
    return mPassword;
}

UserType User::getUserType() const
{
    return mUserType;
}

DateTime User::getJoinDate() const
{
    return mJoinDate;
}

std::string User::userInformation() const
{
    std::string information = "Username: " + mUsername + '\n';
    information.append("User Type: " + userTypeToString(mUserType) + '\n');
    information.append("Joined At: " + mJoinDate.mString + '\n');

    return information;
}
