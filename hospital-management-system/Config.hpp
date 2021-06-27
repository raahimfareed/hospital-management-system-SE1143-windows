#pragma once
#include <string>

#ifdef _WIN32
# define CLEAR "cls"
#else
# define CLEAR "clear"
#endif

struct Config
{
    static const unsigned int mcTotalFloors;
    static const unsigned int mcTotalPatientRoomsPerFloors;
    static const unsigned int mcTotalStaffRoomsPerFloors;
    static const unsigned int mcTotalWaitingRoomsPerFloors;
    static const bool mcBasement;
    static const unsigned int mcTotalPatientsPerRoom;
    static const unsigned int mcTotalStaffPerRoom;
    static const unsigned int mcTotalVisitorsPerRoom;
    static const std::string mcVersion;
};