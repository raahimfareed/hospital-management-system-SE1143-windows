#pragma once

#include "Config.hpp"
#include "Utils.hpp"
#include "DateTime.hpp"

class User
{
public:
    User();
    User(UserType type);
    User(time_t creationTime);
    User(std::string username, std::string password);
    User(std::string username, std::string password, UserType userType);
    User(std::string username, std::string password, UserType userType, time_t creationTime);
    virtual void setUsername(const std::string& username);
    virtual void setPassword(const std::string& password);
    virtual void setUserType(const UserType& type);
    virtual std::string getUsername() const;
    virtual std::string getPassword() const;
    virtual UserType getUserType() const;
    virtual DateTime getJoinDate() const;
    virtual std::string userInformation() const;

private:
    UserType mUserType;
    std::string mUsername;
    std::string mPassword;
    DateTime mJoinDate;
};