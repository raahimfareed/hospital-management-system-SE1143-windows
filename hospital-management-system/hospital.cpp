#include "Hospital.hpp"

Hospital::Hospital()
    :mPatientRoomsFull(0), mStaffRoomsFull(0), mWaitingRoomsFull(0)
{}

unsigned int& Hospital::rPatientRoomsFull()
{
    return mPatientRoomsFull;
}

unsigned int& Hospital::rStaffRoomsFull()
{
    return mStaffRoomsFull;
}

unsigned int& Hospital::rWaitingRoomsFull()
{
    return mWaitingRoomsFull;
}

void Hospital::setPatientRoomsFull(unsigned int amount)
{
    mPatientRoomsFull = amount;
}

void Hospital::setStaffRoomsFull(unsigned int amount)
{
    mStaffRoomsFull = amount;
}

void Hospital::setWaitingRoomsFull(unsigned int amount)
{
    mWaitingRoomsFull = amount;
}

void Hospital::setPatientsCount(unsigned int amount)
{
    mPatientsCount = amount;
}

void Hospital::setStaffCount(unsigned int amount)
{
    mStaffCount = amount;
}

void Hospital::setVisitorsCount(unsigned int amount)
{
    mVisitorsCount = amount;
}

unsigned int Hospital::getPatientRoomsFull() const
{
    return mPatientRoomsFull;
}

unsigned int Hospital::getStaffRoomsFull() const
{
    return mStaffRoomsFull;
}

unsigned int Hospital::getWaitingRoomsFull() const
{
    return mWaitingRoomsFull;
}

unsigned int Hospital::getPatientsCount() const
{
    return mPatientsCount;
}

unsigned int Hospital::getStaffCount() const
{
    return mStaffCount;
}

unsigned int Hospital::getVisitorsCount() const
{
    return mVisitorsCount;
}