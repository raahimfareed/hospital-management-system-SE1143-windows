#include "User.hpp"
#include "Utils.hpp"

User::User()
	:mUserType(UserType::Guest), mUsername("Guest")
{}

User::User(UserType type)
	: mUserType(type)
{}