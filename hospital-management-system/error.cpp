#include <string>
#include <map>

#include "Error.hpp"

std::string Error::get(std::string key)
{
    return mErrors[key];
}

// all errors implemented
std::map<std::string, std::string> Error::mErrors = {
    {"username-small", "Your username cannot be empty!"},
    {"username-invalid", "Your username is invalid, it can only contain alphabets and spaces."},
    {"user-exists", "This user already exists!"},
    {"password-small", "Your password must be at least 8 characters long."},
    {"user-not-found", "User not found"},
    {"password-invalid", "Your password is invalid"}
};
