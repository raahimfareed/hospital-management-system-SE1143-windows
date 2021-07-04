#pragma once

// all ANSI available colors, some terminals do not support them
enum class TextColor
{
    fBlack,
    fRed,
    fGreen,
    fYellow,
    fBlue,
    fMagenta,
    fCyan,
    fWhite,
    fDefault,

    bBlack,
    bRed,
    bGreen,
    bYellow,
    bBlue,
    bMagenta,
    bCyan,
    bWhite,
    bDefault,
};

enum class UserType
{
    Guest = 'G',
    Patient = 'P',
    Nurse = 'N',
    Doctor = 'D',
    Receptionist = 'R',
    Admin = 'A',
    Visitor = 'V',
};

enum class MenuLevel
{
    Root,
    Login,
    Signup,

    Appointments,
    Messages,
    Journal,
    Dispensary,
    Drug
};
