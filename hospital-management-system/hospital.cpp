#include "Hospital.hpp"
#include "Dispensary.hpp"

Hospital::Hospital()
    :mpUserLoggedIn(nullptr)
{}

std::unique_ptr<User>& Hospital::rGetUser()
{
    return mpUserLoggedIn;
}

Dispensary& Hospital::rGetDispensary()
{
    return mDispensary;
}
