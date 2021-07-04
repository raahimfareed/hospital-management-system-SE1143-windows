#pragma once
#include <vector>
#include <memory>

#include "User.hpp"
#include "Dispensary.hpp"

class Hospital
{
public:
    Hospital();
    std::unique_ptr<User>& rGetUser();

    Dispensary& rGetDispensary();

private:
    std::unique_ptr<User> mpUserLoggedIn;
    Dispensary mDispensary;
};