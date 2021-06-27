#pragma once
#include <vector>

#include "Config.hpp"
#include "Utils.hpp"
#include "User.hpp"

class Hospital
{
public:
    Hospital();

    unsigned int& rPatientRoomsFull();
    unsigned int& rStaffRoomsFull();
    unsigned int& rWaitingRoomsFull();

    unsigned int& rPatientsCount();
    unsigned int& rStaffCount();
    unsigned int& rVisitorsCount();

    void setPatientRoomsFull(unsigned int amount);
    void setStaffRoomsFull(unsigned int amount);
    void setWaitingRoomsFull(unsigned int amount);

    void setPatientsCount(unsigned int amount);
    void setStaffCount(unsigned int amount);
    void setVisitorsCount(unsigned int amount);

    unsigned int getPatientRoomsFull() const;
    unsigned int getStaffRoomsFull() const;
    unsigned int getWaitingRoomsFull() const;

    unsigned int getPatientsCount() const;
    unsigned int getStaffCount() const;
    unsigned int getVisitorsCount() const;

private:
    std::vector<User> mPatients;
    std::vector<User> mVisitors;
    std::vector<User> mDoctors;
    std::vector<User> mReceptionists;
    std::vector<User> mNurses;

    unsigned int mPatientRoomsFull;
    unsigned int mStaffRoomsFull;
    unsigned int mWaitingRoomsFull;

    unsigned int mPatientsCount;
    unsigned int mStaffCount;
    unsigned int mVisitorsCount;
};