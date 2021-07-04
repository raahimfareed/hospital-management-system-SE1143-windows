#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>


#include "Config.hpp"
#include "Functions.hpp"
#include "Utils.hpp"
#include "File.hpp"
#include "Error.hpp"
#include "Menu.hpp"
#include "Hospital.hpp"
#include "User.hpp"
#include "Log.hpp"

void loading(const size_t& loop)
{
    using namespace std::chrono_literals;
    printf("Loading program, please wait");
    for (size_t i = 0; i < loop; ++i)
    {
        std::this_thread::sleep_for(500ms);
        printf(".");
        std::this_thread::sleep_for(500ms);
        printf(".");
        std::this_thread::sleep_for(500ms);
        printf(".");
        std::this_thread::sleep_for(500ms);
        printf("\b\b\b   \b\b\b");
    }
}

template <typename T>
void input(T& userInput)
{
    std::cin >> userInput;
    std::cin.ignore();
}

void input(std::string& userInput)
{
    std::getline(std::cin, userInput);
}

std::string formatText(const std::string& text, const TextColor& color, const TextColor& bgColor, const bool bold, const bool italic, const bool inverse)
{
    std::string finalString = "\u001b[";
    bool semiColon = false;

    if (bold)
    {
        finalString.append("1");
        semiColon = true;
    }

    if (italic)
    {
        if (semiColon)
        {
            finalString.append(";");
        }
        finalString.append("3");
        semiColon = true;
    }

    if (inverse)
    {
        if (semiColon)
        {
            finalString.append(";");
        }
        finalString.append("7");
        semiColon = true;
    }

    if (semiColon)
    {
        finalString.append(";");
    }

    switch (color)
    {
    case TextColor::fBlack:
        finalString.append("30");
        semiColon = true;
        break;
    case TextColor::fRed:
        finalString.append("31");
        semiColon = true;
        break;
    case TextColor::fGreen:
        finalString.append("32");
        semiColon = true;
        break;
    case TextColor::fYellow:
        finalString.append("33");
        semiColon = true;
        break;
    case TextColor::fBlue:
        finalString.append("34");
        semiColon = true;
        break;
    case TextColor::fMagenta:
        finalString.append("35");
        semiColon = true;
        break;
    case TextColor::fCyan:
        finalString.append("36");
        semiColon = true;
        break;
    case TextColor::fWhite:
        finalString.append("37");
        semiColon = true;
        break;
    case TextColor::fDefault:
        finalString.append("39");
        semiColon = true;
        break;
    default:
        break;
    }

    if (semiColon)
    {
        finalString.append(";");
    }

    switch (bgColor)
    {
    case TextColor::bBlack:
        finalString.append("40");
        semiColon = true;
        break;
    case TextColor::bRed:
        finalString.append("41");
        semiColon = true;
        break;
    case TextColor::bGreen:
        finalString.append("42");
        semiColon = true;
        break;
    case TextColor::bYellow:
        finalString.append("43");
        semiColon = true;
        break;
    case TextColor::bBlue:
        finalString.append("44");
        semiColon = true;
        break;
    case TextColor::bMagenta:
        finalString.append("45");
        semiColon = true;
        break;
    case TextColor::bCyan:
        finalString.append("46");
        semiColon = true;
        break;
    case TextColor::bWhite:
        finalString.append("47");
        semiColon = true;
        break;
    case TextColor::bDefault:
        finalString.append("49");
        semiColon = true;
        break;
    default:
        break;
    }

    finalString.append("m");
    finalString.append(text);
    finalString.append("\u001b[0m");

    return finalString;
}

void haltProgram(const bool message)
{
    if (message)
    {
        printf("Press %s key to continue\n", formatText("[Enter/Return]", TextColor::fYellow, TextColor::bDefault, true).c_str());
    }

    std::cin.get();
}

void inputPlaceholder(const std::vector<std::string>& breadcrumbs, const std::unique_ptr<User>& loggedInUser, const bool hidden)
{
    if (hidden) return;

    std::string placeholder = formatText(loggedInUser->getUsername() + "@" + userTypeToString(loggedInUser->getUserType()) + "\n~", TextColor::fMagenta, TextColor::bDefault, true);

    for (std::string location : breadcrumbs)
    {
        placeholder.append(formatText('/' + location, TextColor::fMagenta, TextColor::bDefault, true));
    }

    placeholder.append(formatText(" > ", TextColor::fMagenta, TextColor::bDefault, true));

    printf("%s", placeholder.c_str());
}

void header()
{
    printf("----------------------------------\n");
    printf("=== %s ===\n", formatText("Hospital Management System", TextColor::fBlack, TextColor::bGreen).c_str());
    printf("----------------------------------\n");
}

void firstTimeSetup(std::unique_ptr<User>& loggedInUser, File& configFile)
{
    system(CLEAR);
    header();
    printf("Welcome to %s!\nThis is your first time starting this program therefore you will need to create an admin account!\nDo you wish to proceed? %ses/%so: ", formatText("Extricate", TextColor::fCyan, TextColor::bDefault, true).c_str(), formatText("[Y]", TextColor::fYellow, TextColor::bDefault, true).c_str(), formatText("[N]", TextColor::fYellow, TextColor::bDefault, true).c_str());
    std::string choice;
    input(choice);
    if (toupper(choice[0]) == 'Y')
    {
        std::string username;
        std::string password;
        bool inputError;

        do
        {
            inputError = false;
            printf("Please choose a username: ");
            input(username);

            if (username.empty())
            {
                printf("%s %s\n", formatText("[Error]:", TextColor::fRed, TextColor::bDefault, true).c_str(), Error::get("username-small").c_str());

                inputError = true;
            }


        } while (inputError);

        do
        {
            inputError = false;
            printf("Please choose a password: ");
            input(password);

            if (password.empty() || password.length() < 8)
            {
                printf("%s %s\n", formatText("[Error]:", TextColor::fRed, TextColor::bDefault, true).c_str(), Error::get("password-empty").c_str());

                inputError = true;
            }
        } while (inputError);

        std::unique_ptr<User> admin = std::make_unique<User>(username, password, UserType::Admin);
        configFile.write(std::to_string((int)admin->getUserType()) + "|" + admin->getUsername() + "|" + encrypt(admin->getUsername(), admin->getPassword()) + "|" + std::to_string(admin->getJoinDate().mCreationTime));

        printf("Would you like to login as admin? %ses/%so: ", formatText("[Y]", TextColor::fYellow, TextColor::bDefault, true).c_str(), formatText("[N]", TextColor::fYellow, TextColor::bDefault, true).c_str());
        input(choice);

        if (toupper(choice[0]) == 'Y')
        {
            loggedInUser = std::move(admin);
        }
        return;
    }

    printf("First time setup dialog will appear next time when you start the program!\n");
    haltProgram();
    exit(EXIT_SUCCESS);
}

bool init(bool& mainLoop, std::unique_ptr<User>& loggedInUser, MenuLevel& menuLevel, std::string& menuChoice)
{
    File configFile("users.db");
    std::string initLine = configFile.search(1);
    loggedInUser = std::make_unique<User>();
    mainLoop = false;
    menuChoice = "";
    menuLevel = MenuLevel::Root;
    if (initLine == "")
    {
        firstTimeSetup(loggedInUser, configFile);
    }
    return true;
}

void menu(const std::unique_ptr<User>& loggedInUser, const MenuLevel& menuLevel, const std::vector<std::string>& breadcrumbs)
{
    system(CLEAR);
    header();
    printf("%s", Menu::get(std::make_pair(loggedInUser->getUserType(), menuLevel)).c_str());
    inputPlaceholder(breadcrumbs, loggedInUser);
}

void processInput(std::string& userInput, std::vector<std::string>& breadcrumb, std::unique_ptr<User>& loggedInUser, Hospital& hospital, MenuLevel& currentMenu, bool& quit)
{
    if (currentMenu == MenuLevel::Root && toupper(userInput[0]) == 'L' && loggedInUser->getUserType() != UserType::Guest)
    {
        logout(breadcrumb, loggedInUser, currentMenu);
        return;
    }

    switch (loggedInUser->getUserType())
    {
        case UserType::Admin:
            switch (currentMenu)
            {

            // Main Menu
            case MenuLevel::Root:
                breadcrumb.clear();
                switch (toupper(userInput[0]))
                {
                case 'P':
                    showUsers(UserType::Patient);
                    break;
                case 'N':
                    showUsers(UserType::Nurse);
                    break;
                case 'D':
                    showUsers(UserType::Doctor);
                    break;
                case 'R':
                    showUsers(UserType::Receptionist);
                    break;
                case 'A':
                    showUsers(UserType::Admin);
                    break;
                case 'M':
                    showMessages();
                    break;
                case 'S':
                    Log::show();
                    haltProgram();
                    break;
                case 'X':
                    resetProgram();
                    break;
                }
                break;
            }
            break;
        case UserType::Patient:
            switch (currentMenu)
            {
            case MenuLevel::Root:
                breadcrumb.clear();
                switch (toupper(userInput[0]))
                {
                case 'A':
                    currentMenu = MenuLevel::Appointments;
                    breadcrumb.push_back("appointment");
                    makeAppointment(loggedInUser, breadcrumb, currentMenu);
                    break;
                case 'M':
                    showMessages(loggedInUser);
                    break;
                case 'D':
                    showDoctors();
                    break;
                case 'B':
                    currentMenu = MenuLevel::Root;
                    breadcrumb.pop_back();
                    break;
                }
                break;
            }
            break;
        case UserType::Doctor:
            switch (currentMenu)
            {
            case MenuLevel::Root:
                breadcrumb.clear();
                switch (toupper(userInput[0]))
                {
                case 'A':
                    currentMenu = MenuLevel::Appointments;
                    breadcrumb.push_back("appointment");
                    showAppointments();
                    currentMenu = MenuLevel::Root;
                    breadcrumb.pop_back();
                    break;
                case 'M':
                    sendMessages(loggedInUser);
                    break;
                case 'N':
                    showUsers(UserType::Nurse);
                    break;
                case 'P':
                    showUsers(UserType::Patient);
                    break;
                case 'B':
                    currentMenu = MenuLevel::Root;
                    breadcrumb.pop_back();
                    break;
                }
                break;
            }
            break;
        case UserType::Nurse:
            switch (currentMenu)
            {
            case MenuLevel::Root:
                breadcrumb.clear();
                switch (toupper(userInput[0]))
                {
                case 'A':
                    currentMenu = MenuLevel::Appointments;
                    breadcrumb.push_back("appointment");
                    showAppointments();
                    currentMenu = MenuLevel::Root;
                    breadcrumb.pop_back();
                    break;
                case 'M':
                    sendMessages(loggedInUser);
                    break;
                case 'P':
                    showUsers(UserType::Patient);
                    break;
                case 'D':
                    currentMenu = MenuLevel::Dispensary;
                    breadcrumb.push_back("dispensary");
                    break;
                }
                break;
            case MenuLevel::Dispensary:
                switch (toupper(userInput[0]))
                {
                case 'A':
                    currentMenu = MenuLevel::Drug;
                    breadcrumb.push_back("drug");
                    hospital.rGetDispensary().addDrug(loggedInUser, currentMenu, breadcrumb);
                    break;
                case 'S':
                    hospital.rGetDispensary().showAllDrugs();
                    break;
                case 'W':
                    std::cout << "Total Funds Available: " << hospital.rGetDispensary().getBudget() << '\n';
                    haltProgram();
                    break;
                case 'B':
                    currentMenu = MenuLevel::Root;
                    breadcrumb.pop_back();
                    break;
                }
                break;
            }
            break;
        case UserType::Receptionist:
            switch (currentMenu)
            {
            case MenuLevel::Root:
                breadcrumb.clear();
                switch (toupper(userInput[0]))
                {
                case 'A':
                    currentMenu = MenuLevel::Appointments;
                    breadcrumb.push_back("appointment");
                    showAppointments();
                    currentMenu = MenuLevel::Root;
                    breadcrumb.pop_back();
                    break;
                case 'M':
                    showMessages();
                    break;
                case 'P':
                    showUsers(UserType::Patient);
                    break;
                case 'W':
                    std::cout << "Total Funds Available: " << hospital.rGetDispensary().getBudget() << '\n';
                    haltProgram();
                    break;
                case 'F':
                    addFunds(hospital);
                    break;
                }
                break;
            }
            break;
        case UserType::Guest:
            switch (currentMenu)
            {

            // Main Menu
            case MenuLevel::Root:
                breadcrumb.clear();
                switch (toupper(userInput[0]))
                {
                case 'L':
                    breadcrumb.push_back("login");
                    currentMenu = MenuLevel::Login;
                    break;
                case 'S':
                    breadcrumb.push_back("signup");
                    currentMenu = MenuLevel::Signup;
                    break;
                case 'H':
                    help();
                    break;
                case 'C':
                    credits();
                    break;
                case 'E':
                    exitProgram(quit);
                    break;
                }
                break;


            // Login Menu
            case MenuLevel::Login:
                switch (toupper(userInput[0]))
                {
                case 'P':
                    breadcrumb.push_back("patient");
                    login(breadcrumb, loggedInUser, hospital, currentMenu, UserType::Patient);
                    break;
                case 'N':
                    breadcrumb.push_back("nurse");
                    login(breadcrumb, loggedInUser, hospital, currentMenu, UserType::Nurse);
                    break;
                case 'D':
                    breadcrumb.push_back("doctor");
                    login(breadcrumb, loggedInUser, hospital, currentMenu, UserType::Doctor);
                    break;
                case 'R':
                    breadcrumb.push_back("receptionist");
                    login(breadcrumb, loggedInUser, hospital, currentMenu, UserType::Receptionist);
                    break;
                case 'A':
                    breadcrumb.push_back("admin");
                    login(breadcrumb, loggedInUser, hospital, currentMenu, UserType::Admin);
                    break;
                case 'B':
                    currentMenu = MenuLevel::Root;
                    breadcrumb.pop_back();
                    break;
                }
                break;

            // Signup Menu
            case MenuLevel::Signup:
                switch (toupper(userInput[0]))
                {
                case 'P':
                    breadcrumb.push_back("patient");
                    signup(breadcrumb, loggedInUser, hospital, currentMenu, UserType::Patient);
                    break;
                case 'N':
                    breadcrumb.push_back("nurse");
                    signup(breadcrumb, loggedInUser, hospital, currentMenu, UserType::Nurse);
                    break;
                case 'D':
                    breadcrumb.push_back("doctor");
                    signup(breadcrumb, loggedInUser, hospital, currentMenu, UserType::Doctor);
                    break;
                case 'R':
                    breadcrumb.push_back("receptionist");
                    signup(breadcrumb, loggedInUser, hospital, currentMenu, UserType::Receptionist);
                    break;
                case 'A':
                    breadcrumb.push_back("admin");
                    signup(breadcrumb, loggedInUser, hospital, currentMenu, UserType::Admin);
                    break;
                case 'B':
                    currentMenu = MenuLevel::Root;
                    breadcrumb.pop_back();
                    break;
                }
                break;
            }
            break;
    }
}

std::string encrypt(std::string text, std::string key)
{
    std::string encryptedText;
    char ch;

    for (size_t i = 0, j = 0; i < text.length(); ++i, ++j)
    {
        if (j >= key.length())
        {
            j = 0;
        }

        ch = (char)(key[j] ^ text[i]);

        if (ch == '\n')
        {
            ch = '\0';
        }

        if (ch == '|')
        {
            ch = '/';
        }

        encryptedText.append(1, ch);
    }

    return encryptedText;
}

bool decrypt(std::string text, std::string key, std::string encryptedText)
{
    if (encrypt(text, key) == encryptedText)
    {
        return true;
    }
    return false;
}

std::string userTypeToString(const UserType& type)
{
    switch (type)
    {
    case UserType::Guest:
        return "Guest";
        break;
    case UserType::Patient:
        return "Patient";
        break;
    case UserType::Nurse:
        return "Nurse";
        break;
    case UserType::Doctor:
        return "Doctor";
        break;
    case UserType::Receptionist:
        return "Receptionist";
        break;
    case UserType::Admin:
        return "Admin";
        break;
    default:
        return "User";
        break;
    }
}

void exitProgram(bool& quit)
{
    system(CLEAR);
    char uInput;
    printf("%s Are you sure you want to quit? %ses/%so: ", formatText("[WARNING]:", TextColor::fRed, TextColor::bDefault, true).c_str(), formatText("[Y]", TextColor::fYellow, TextColor::bDefault, true).c_str(), formatText("[N]", TextColor::fYellow, TextColor::bDefault, true).c_str());
    input(uInput);
    if (toupper(uInput) == 'Y')
    {
        quit = true;
    }
    haltProgram();
}

void credits()
{
    printf("Made By: Raahim Fareed BSE203039\nSubject: OOP S1 SE1143\nInstructor: Faria Nasir\n");
    haltProgram();
}

void help()
{
    haltProgram();
}

void login(std::vector<std::string>& breadcrumb, std::unique_ptr<User>& loggedInUser, Hospital& hospital, MenuLevel& currentMenu, const UserType& userType)
{
    system(CLEAR);
    std::string filePath = "users.db";
    File userDb(filePath);
    std::fstream* pFile = userDb.getFile();
    bool userExists = false;
    std::string fileLine;

    pFile->open(filePath, std::ios::in);

    std::string username;
    std::string password;
    printf("Please enter your %s: ", formatText("username", TextColor::fDefault, TextColor::bDefault, true).c_str());
    input(username);

    while (username.length() == 0)
    {
        printf("%s %s\nPlease enter your %s again: ", formatText("[Error]:", TextColor::fRed, TextColor::bDefault, true).c_str(), Error::get("username-small").c_str(), formatText("username", TextColor::fDefault, TextColor::bDefault, true).c_str());
        input(username);
    }

    printf("Please enter your %s: ", formatText("password", TextColor::fDefault, TextColor::bDefault, true).c_str());
    input(password);


    std::vector<std::string> userInformation;
    while (std::getline(*pFile, fileLine))
    {
        if (fileLine[0] == ';')
            continue;


        std::stringstream ss(fileLine);
        std::string value;
        userInformation.clear();

        while (getline(ss, value, '|'))
        {
            userInformation.push_back(value);
        }

        if ((UserType)std::stoi(userInformation[0]) == userType)
        {
            if (username == userInformation[1])
            {
                userExists = true;
                unsigned int tries = 0;
                bool userLoggedIn = false;
                while (tries < 3 && !userLoggedIn)
                {

                    if (decrypt(password, username, userInformation[2]))
                    {
                        
                        loggedInUser = std::make_unique<User>(username, password, userType);
                        Log::login(loggedInUser);
                        printf("%s Logged In!\n", formatText("[SUCCESS]:", TextColor::fGreen).c_str());
                        userLoggedIn = true;
                        break;
                    }

                    printf("%s, %d tries left\n", Error::get("password-invalid").c_str(), 3 - tries);
                    ++tries;

                    printf("Please enter your %s: ", formatText("password", TextColor::fDefault, TextColor::bDefault, true).c_str());
                    input(password);
                }

                // Max retries reached error message
                if (!userLoggedIn)
                {
                    printf("%s %s\n", formatText("[Error]:", TextColor::fRed, TextColor::bDefault, true).c_str(), Error::get("max-password-tries").c_str());
                }

                haltProgram();
                break;
            }
        }
    }
    pFile->close();

    if (!userExists)
    {
        printf("%s %s\n", formatText("[Error]:", TextColor::fRed, TextColor::bDefault, true).c_str(), Error::get("user-not-found").c_str());
        haltProgram();
    }

    currentMenu = MenuLevel::Root;
    breadcrumb.clear();
}

void signup(std::vector<std::string>& breadcrumb, std::unique_ptr<User>& loggedInUser, Hospital& hospital, MenuLevel& currentMenu, const UserType& userType)
{
    system(CLEAR);
    std::string filePath = "users.db";
    File userDb(filePath);
    std::fstream* pFile = userDb.getFile();
    bool userExists = false;
    std::string fileLine;

    pFile->open(filePath, std::ios::in);

    std::string username;
    std::string password;
    printf("Please enter a %s: ", formatText("username", TextColor::fDefault, TextColor::bDefault, true).c_str());
    input(username);

    while (username.length() == 0)
    {
        printf("%s %s \nPlease enter your %s again: ", formatText("[Error]:", TextColor::fRed, TextColor::bDefault, true).c_str(), Error::get("username-small").c_str(), formatText("username", TextColor::fDefault, TextColor::bDefault, true).c_str());
        input(username);
    }

    printf("Please enter a %s, %s: ", formatText("password", TextColor::fDefault, TextColor::bDefault, true).c_str(), formatText("it should be at least 8 characters", TextColor::fDefault, TextColor::bDefault, false, true).c_str());
    input(password);

    while (password.length() < 8)
    {
        printf("%s %s\nPlease enter your %s again: ", formatText("[Error]:", TextColor::fRed, TextColor::bDefault, true).c_str(), Error::get("password-small").c_str(), formatText("password", TextColor::fDefault, TextColor::bDefault, true).c_str());
        input(password);
    }

    std::vector<std::string> userInformation;
    while (std::getline(*pFile, fileLine))
    {
        if (fileLine[0] == ';')
            continue;
        std::stringstream ss(fileLine);
        std::string value;
        userInformation.clear();

        while (getline(ss, value, '|'))
        {
            userInformation.push_back(value);
        }

        if ((UserType)std::stoi(userInformation[0]) == userType)
        {
            if (username == userInformation[1])
            {
                userExists = true;
                printf("%s %s\n", formatText("[Error]:", TextColor::fRed, TextColor::bDefault, true).c_str(), Error::get("user-exists").c_str());
                haltProgram();
                break;
            }
        }
    }
    pFile->close();

    if (!userExists)
    {
        DateTime currentDate;
        std::string row = std::to_string((int)userType) + '|' + username + '|' + encrypt(password, username) + '|' + std::to_string(currentDate.mCreationTime);
        userDb.write(row);
        printf("%s Your account has been created.\n", formatText("[SUCCESS]:", TextColor::fGreen).c_str());
        haltProgram();
    }

    currentMenu = MenuLevel::Root;
    breadcrumb.clear();
}

void logout(std::vector<std::string>& breadcrumb, std::unique_ptr<User>& loggedInUser, MenuLevel& currentMenu)
{
    loggedInUser = std::make_unique<User>();
    breadcrumb.clear();
    currentMenu = MenuLevel::Root;
}

void showUsers(const UserType& type)
{
    std::string uInput, fileLine;
    File userFile("users.db");
    std::fstream* pFile = userFile.getFile();
    pFile->open("users.db", std::ios::in);
    
    unsigned int start = 0;
    unsigned int count = 0;
    const unsigned int maxRows = 5;

    std::vector<std::string> userInformation;
    system(CLEAR);
    printf("%s Data: %d - %d\n", userTypeToString(type).c_str(), start + 1, start + maxRows);
    while (std::getline(*pFile, fileLine))
    {
        if (fileLine[0] == ';')
            continue;
        std::stringstream ss(fileLine);
        std::string value;
        userInformation.clear();

        while (getline(ss, value, '|'))
        {
            userInformation.push_back(value);
        }

        if ((UserType)std::stoi(userInformation[0]) != type) continue;

        time_t t = std::stoll(userInformation[3]);

        printf("%d\t%s\t%s\t%s\n", ++count, userInformation[1].c_str(), userTypeToString((UserType)std::stoi(userInformation[0])).c_str(), DateTime::unixTimeToString(&t).c_str());
        if (count % 5 == 0)
        {
            printf("%sext / %sxit: ", formatText("[N]", TextColor::fYellow, TextColor::bDefault, true).c_str(), formatText("[E]", TextColor::fYellow, TextColor::bDefault, true).c_str());
            input(uInput);

            if (toupper(uInput[0]) == 'N')
            {
                start += maxRows;
                system(CLEAR);
                printf("%s Data: %d - %d\n", userTypeToString(type).c_str(), start + 1, start + maxRows);
                continue;
            }

            break;
        }
    }

    if (count % 5 == 0)
    {
        printf("No records found!\n");
    }
    haltProgram();

    pFile->close();
}

void resetProgram()
{
    system(CLEAR);
    char uInput;
    printf("%s Are you sure you want to reset your program? It will delete all records! %ses/%so: ", formatText("[WARNING]:", TextColor::fRed, TextColor::bDefault, true).c_str(), formatText("[Y]", TextColor::fYellow, TextColor::bDefault, true).c_str(), formatText("[N]", TextColor::fYellow, TextColor::bDefault, true).c_str());
    input(uInput);
    if (toupper(uInput) != 'Y')
    {
        return;
    }
    remove("users.db");
    remove("log.db");
    remove("appointments.db");
    remove("messages.db");
    printf("Program has been reset, you will need to restart your program to apply changes!\n");
    haltProgram();
    exit(EXIT_SUCCESS);
}

void makeAppointment(std::unique_ptr<User>& loggedInUser, std::vector<std::string>& breadcrumb, MenuLevel& currentMenu)
{
    std::string uInput;
    menu(loggedInUser, currentMenu, breadcrumb);
    input(uInput);

    system(CLEAR);
    switch (toupper(uInput[0]))
    {
    case '1':
        printf("%s Influenza\n" \
            "%s Fever (Not common in everyone), Cough, Sore Throat, Runny/Stuffy Nose, Muscle/Body Ache, Headache, Fatigue (Tiredness), Vomiting (Kids), Diarrhea(Kids)\n" \
            "%s If not recovered in 2 weeks, Pneumonia may develop\n" \
            "%s Vitamin C Supplements, Tylenol, Relenza®, Rapivab®, Xofluza®, Tamiflu®, Anti Viral Drugs\n" \
            "%s Antibiotic drugs will not treat Influenza\n",
            formatText("[Condition]:", TextColor::fGreen, TextColor::bDefault, true).c_str(),
            formatText("[Symptoms]:", TextColor::fGreen, TextColor::bDefault, true).c_str(),
            formatText("[Complication]:", TextColor::fGreen, TextColor::bDefault, true).c_str(),
            formatText("[Medication]:", TextColor::fGreen, TextColor::bDefault, true).c_str(),
            formatText("[Note]:", TextColor::fGreen, TextColor::bDefault, true).c_str());
        break;
    case '2':
        printf("%s COVID-19\n" \
            "%s Fever, Cough, Shortness of Breath, Fatigue, Headache, Body/Muscle, Loss of Taste/Smell, Sore Throat, Congestion, Nausea, Diarrhea\n" \
            "%s Can lead to critical condition if not recovered\n" \
            "%s Wear Mask, Wash hands regulary with soap, Use hand sanitizers, Veklury, Dexamethasone, Drink excess Water\n",
            formatText("[Condition]:", TextColor::fGreen, TextColor::bDefault, true).c_str(),
            formatText("[Symptoms]:", TextColor::fGreen, TextColor::bDefault, true).c_str(),
            formatText("[Complication]:", TextColor::fGreen, TextColor::bDefault, true).c_str(),
            formatText("[Medication]:", TextColor::fGreen, TextColor::bDefault, true).c_str());
        break;
    case '3':
        printf("%s COVID-19\n" \
            "%s Pink/Red eye color, Swelling of eye, Increased tears, Feel like foreign objects are in eye, Itcing/Burning/Irritation, Discharge (Pus/Mucus), Crusting of Eyelids\n" \
            "%s Cold compresses, Artificial tears, Avoid contact lenses\n",
            formatText("[Condition]:", TextColor::fGreen, TextColor::bDefault, true).c_str(),
            formatText("[Symptoms]:", TextColor::fGreen, TextColor::bDefault, true).c_str(),
            formatText("[Medication]:", TextColor::fGreen, TextColor::bDefault, true).c_str());
        break;
    case '4':
        printf("%s HIV/AIDS\n" \
            "%s Fever, Headache, Muscle/Joint pain, Rash, Sore throat, Weight loss, Cough, Swollen Lymph glands, Night sweats, Diarrhea\n" \
            "%s TasP, PEP, PrEP, Use protection, Circumcision\n",
            formatText("[Condition]:", TextColor::fGreen, TextColor::bDefault, true).c_str(),
            formatText("[Symptoms]:", TextColor::fGreen, TextColor::bDefault, true).c_str(),
            formatText("[Medication]:", TextColor::fGreen, TextColor::bDefault, true).c_str());
        break;
    case '5':
        printf("%s Tetanus\n" \
            "%s Painful Muscle Spasms, Muscle Tension, Difficulty Swallowing, Rigid Abdominal Muscles\n" \
            "%s Care in the hospital ,Immediate treatment with medicine called human tetanus immune globulin (TIG), Aggressive wound care, Drugs to control muscle spasms, Antibiotics, Tetanus vaccination\n",
            formatText("[Condition]:", TextColor::fGreen, TextColor::bDefault, true).c_str(),
            formatText("[Symptoms]:", TextColor::fGreen, TextColor::bDefault, true).c_str(),
            formatText("[Medication]:", TextColor::fGreen, TextColor::bDefault, true).c_str());
        break;
    case '6':
        printf("%s Malaria\n" \
            "%s Fever, Chills, General feeling of discomfort, Headache, Nausea and vomiting, Diarrhea, Abdominal pain, Muscle or joint pain, Fatigue, Rapid breathing, Rapid heart rate, Cough\n" \
            "%s Chloroquine phosphate, Artemisinin-based combination therapies (ACTs), Atovaquone-proguanil (Malarone), Quinine sulfate (Qualaquin) with doxycycline (Oracea, Vibramycin, others), Primaquine phosphate\n",
            formatText("[Condition]:", TextColor::fGreen, TextColor::bDefault, true).c_str(),
            formatText("[Symptoms]:", TextColor::fGreen, TextColor::bDefault, true).c_str(),
            formatText("[Medication]:", TextColor::fGreen, TextColor::bDefault, true).c_str());
        break;
    case '7':
        printf("%s Pneumonia\n" \
            "%s Chest pain when you breathe or cough, Confusion or changes in mental awareness (in adults age 65 and older), Cough, which may produce phlegm, Fatigue, Fever, sweating and shaking chills, Lower than normal body temperature (in adults older than age 65 and people with weak immune systems), Nausea, vomiting or diarrhea, Nausea, vomiting or diarrhea\n" \
            "%s Control your fever with aspirin, Drink plenty of fluids, Do not take cough medicines without first talking to your doctor, Drink warm beverages, take steamy baths and use a humidifier, Stay away from smoke to let your lungs heal, Get lots of rest\n",
            formatText("[Condition]:", TextColor::fGreen, TextColor::bDefault, true).c_str(),
            formatText("[Symptoms]:", TextColor::fGreen, TextColor::bDefault, true).c_str(),
            formatText("[Medication]:", TextColor::fGreen, TextColor::bDefault, true).c_str());
        break;
    case '8':
        printf("%s Depression\n" \
            "%s Feelings of sadness, tearfulness, emptiness or hopelessness, Angry outbursts, irritability or frustration, even over small matters, Loss of interest or pleasure in most or all normal activities, such as sex, hobbies or sports, Sleep disturbances, including insomnia or sleeping too much, Tiredness and lack of energy, so even small tasks take extra effort, Reduced appetite and weight loss or increased cravings for food and weight gain, Anxiety, agitation or restlessness, Slowed thinking, speaking or body movements, Feelings of worthlessness or guilt, fixating on past failures or self-blame, Trouble thinking, concentrating, making decisions and remembering things, Frequent or recurrent thoughts of death, suicidal thoughts, suicide attempts or suicide, Unexplained physical problems, such as back pain or headaches\n" \
            "%s Psychotherapy, SSRI, SNRI, Consider joining a support group, Try relaxation techniques, meditation, and breathing exercises, Talk with family members and friends and explain how they can be helpful, Your therapist may recommend self-help materials, Regular exercise can reduce symptoms of depression and anxiety\n",
            formatText("[Condition]:", TextColor::fGreen, TextColor::bDefault, true).c_str(),
            formatText("[Symptoms]:", TextColor::fGreen, TextColor::bDefault, true).c_str(),
            formatText("[Medication]:", TextColor::fGreen, TextColor::bDefault, true).c_str());
        break;
    case '9':
        printf("%s Epilepsy\n" \
            "%s Temporary confusion, A staring spell, Uncontrollable jerking movements of the arms and legs, Loss of consciousness or awareness, Psychic symptoms such as fear, anxiety or deja vu, Focal seizures without loss of consciousness, Focal seizures with impaired awareness, Other siezures\n" \
            "%s Anti-seizure medications, If anti-epileptic medications don't provide satisfactory results, your doctor may suggest surgery or other therapies. You'll have regular follow-up appointments with your doctor to evaluate your condition and medications\n",
            formatText("[Condition]:", TextColor::fGreen, TextColor::bDefault, true).c_str(),
            formatText("[Symptoms]:", TextColor::fGreen, TextColor::bDefault, true).c_str(),
            formatText("[Medication]:", TextColor::fGreen, TextColor::bDefault, true).c_str());
        break;
    case '0':
        createAppointment(loggedInUser);
        break;
    case 'B': break;
    default:
        printf("%s %s\n", formatText("[Error]:", TextColor::fRed, TextColor::bDefault, true).c_str(), Error::get("invalid-option").c_str());
        break;
    }

    if (toupper(uInput[0]) != 'B')
    {
        haltProgram();
    }
    currentMenu = MenuLevel::Root;
    breadcrumb.pop_back();
}

void createAppointment(std::unique_ptr<User>& loggedInUser)
{
    std::string uInput;
    File appointmentsFile("appointments.db");
    printf("Please enter disease name: ");
    input(uInput);
    printf("A doctor will message you soon!\n");
    appointmentsFile.write(loggedInUser->getUsername() + "|" + uInput + "|" + DateTime::getCurrent());
}

void showMessages()
{
    std::string uInput, fileLine;
    File msgFile("messages.db");
    std::fstream* pFile = msgFile.getFile();
    pFile->open("messages.db", std::ios::in);

    unsigned int start = 0;
    unsigned int count = 0;
    const unsigned int maxRows = 5;

    std::vector<std::string> userInformation;
    system(CLEAR);
    printf("All Messages: %d - %d\n", start + 1, start + maxRows);
    while (std::getline(*pFile, fileLine))
    {
        if (fileLine[0] == ';')
            continue;
        std::stringstream ss(fileLine);
        std::string value;
        userInformation.clear();

        while (getline(ss, value, '|'))
        {
            userInformation.push_back(value);
        }

        printf("%d\t%s\t%s\t%s\n", ++count, userInformation[0].c_str(), userInformation[2].c_str(), userInformation[3].c_str());
        if (count % 5 == 0)
        {
            printf("%sext / %sxit: ", formatText("[N]", TextColor::fYellow, TextColor::bDefault, true).c_str(), formatText("[E]", TextColor::fYellow, TextColor::bDefault, true).c_str());
            input(uInput);

            if (toupper(uInput[0]) == 'N')
            {
                start += maxRows;
                system(CLEAR);
                printf("Messages: %d - %d\n", start + 1, start + maxRows);
                continue;
            }

            break;
        }
    }

    if (count % 5 == 0)
    {
        printf("No messages found!\n");
    }
    haltProgram();

    pFile->close();
}

void showMessages(std::unique_ptr<User>& loggedInUser)
{
    std::string uInput, fileLine;
    File msgFile("messages.db");
    std::fstream* pFile = msgFile.getFile();
    pFile->open("messages.db", std::ios::in);

    unsigned int start = 0;
    unsigned int count = 0;
    const unsigned int maxRows = 5;

    std::vector<std::string> userInformation;
    system(CLEAR);
    printf("Messages: %d - %d\n", start + 1, start + maxRows);
    while (std::getline(*pFile, fileLine))
    {
        if (fileLine[0] == ';')
            continue;
        std::stringstream ss(fileLine);
        std::string value;
        userInformation.clear();

        while (getline(ss, value, '|'))
        {
            userInformation.push_back(value);
        }

        if (userInformation[2] != loggedInUser->getUsername()) continue;

        printf("%d\t%s\t%s\t%s\n", ++count, userInformation[0].c_str(), userInformation[2].c_str(), userInformation[3].c_str());
        if (count % 5 == 0)
        {
            printf("%sext / %sxit: ", formatText("[N]", TextColor::fYellow, TextColor::bDefault, true).c_str(), formatText("[E]", TextColor::fYellow, TextColor::bDefault, true).c_str());
            input(uInput);

            if (toupper(uInput[0]) == 'N')
            {
                start += maxRows;
                system(CLEAR);
                printf("Messages: %d - %d\n", start + 1, start + maxRows);
                continue;
            }

            break;
        }
    }

    if (count % 5 == 0)
    {
        printf("No messages found!\n");
    }
    haltProgram();

    pFile->close();
}

void showDoctors()
{
    std::string uInput, fileLine;
    File userFile("users.db");
    std::fstream* pFile = userFile.getFile();
    pFile->open("users.db", std::ios::in);

    unsigned int start = 0;
    unsigned int count = 0;
    const unsigned int maxRows = 5;

    std::vector<std::string> userInformation;
    system(CLEAR);
    printf("Available Doctors: %d - %d\n", start + 1, start + maxRows);
    while (std::getline(*pFile, fileLine))
    {
        if (fileLine[0] == ';')
            continue;
        std::stringstream ss(fileLine);
        std::string value;
        userInformation.clear();

        while (getline(ss, value, '|'))
        {
            userInformation.push_back(value);
        }

        if ((UserType)std::stoi(userInformation[0]) != UserType::Doctor) continue;

        time_t t = std::stoll(userInformation[3]);

        printf("%d\t%s\t%s\t%s\n", ++count, userInformation[1].c_str(), userTypeToString((UserType)std::stoi(userInformation[0])).c_str(), DateTime::unixTimeToString(&t).c_str());
        if (count % 5 == 0)
        {
            printf("%sext / %sxit: ", formatText("[N]", TextColor::fYellow, TextColor::bDefault, true).c_str(), formatText("[E]", TextColor::fYellow, TextColor::bDefault, true).c_str());
            input(uInput);

            if (toupper(uInput[0]) == 'N')
            {
                start += maxRows;
                system(CLEAR);
                printf("Available Doctors: %d - %d\n", start + 1, start + maxRows);
                continue;
            }

            break;
        }
    }

    if (count % 5 == 0)
    {
        printf("No records found!\n");
    }
    haltProgram();

    pFile->close();
}

void showAppointments()
{
    std::string uInput, fileLine;
    File msgFile("appointments.db");
    std::fstream* pFile = msgFile.getFile();
    pFile->open("appointments.db", std::ios::in);

    unsigned int start = 0;
    unsigned int count = 0;
    const unsigned int maxRows = 5;

    std::vector<std::string> userInformation;
    system(CLEAR);
    printf("Appointments: %d - %d\n", start + 1, start + maxRows);
    while (std::getline(*pFile, fileLine))
    {
        if (fileLine[0] == ';')
            continue;
        std::stringstream ss(fileLine);
        std::string value;
        userInformation.clear();

        while (getline(ss, value, '|'))
        {
            userInformation.push_back(value);
        }

        printf("%d\t%s\t%s\t%s\n", ++count, userInformation[0].c_str(), userInformation[1].c_str(), userInformation[2].c_str());
        if (count % 5 == 0)
        {
            printf("%sext / %sxit: ", formatText("[N]", TextColor::fYellow, TextColor::bDefault, true).c_str(), formatText("[E]", TextColor::fYellow, TextColor::bDefault, true).c_str());
            input(uInput);

            if (toupper(uInput[0]) == 'N')
            {
                start += maxRows;
                system(CLEAR);
                printf("Appointments: %d - %d\n", start + 1, start + maxRows);
                continue;
            }

            break;
        }
    }

    if (count % 5 == 0)
    {
        printf("No messages found!\n");
    }
    haltProgram();

    pFile->close();
}

void sendMessages(std::unique_ptr<User>& user)
{
    system(CLEAR);
    std::string filePath = "users.db";
    File userDb(filePath);
    std::fstream* pFile = userDb.getFile();
    bool userExists = false;
    std::string fileLine;

    pFile->open(filePath, std::ios::in);

    std::string username;
    printf("Please enter %s to whom you want to message: ", formatText("username", TextColor::fDefault, TextColor::bDefault, true).c_str());
    input(username);

    while (username.length() == 0)
    {
        printf("%s %s \nPlease enter %s again: ", formatText("[Error]:", TextColor::fRed, TextColor::bDefault, true).c_str(), Error::get("username-small").c_str(), formatText("username", TextColor::fDefault, TextColor::bDefault, true).c_str());
        input(username);
    }

    std::vector<std::string> userInformation;
    while (std::getline(*pFile, fileLine))
    {
        if (fileLine[0] == ';')
            continue;
        std::stringstream ss(fileLine);
        std::string value;
        userInformation.clear();

        while (getline(ss, value, '|'))
        {
            userInformation.push_back(value);
        }

        if ((UserType)std::stoi(userInformation[0]) == UserType::Patient)
        {
            if (username == userInformation[1])
            {
                userExists = true;
                std::string message;
                printf("Please enter your message: ");
                input(message);

                File messageFile("messages.db");
                messageFile.write(user->getUsername() + "|" + username + "|" + message + "|" + DateTime::getCurrent());
                printf("Your message has been sent to %s\n", username.c_str());
                haltProgram();
                break;
            }
        }
    }
    pFile->close();

    if (!userExists)
    {
        printf("%s %s\n", formatText("[Error]:", TextColor::fRed, TextColor::bDefault, true).c_str(), Error::get("user-not-found").c_str());
        haltProgram();
    }
}

void addFunds(Hospital& rH)
{
    double funds;
    printf("Enter the amount of funds you want to deposit: ");
    input(funds);

    rH.rGetDispensary().rGetBudget() += funds;

    printf("%f funds have been added, new balance is %f\n", funds, rH.rGetDispensary().getBudget().getAmount());
    haltProgram();
}

void run()
{
    loading(1);
    bool quit;
    Hospital hospital;
    hospital.rGetUser() = nullptr;
    MenuLevel currentMenu;
    std::string menuChoice;
    std::vector<std::string> menuBreadcrumbs;
    init(quit, hospital.rGetUser(), currentMenu, menuChoice);
    do
    {
        menu(hospital.rGetUser(), currentMenu, menuBreadcrumbs);
        input(menuChoice);
        processInput(menuChoice, menuBreadcrumbs, hospital.rGetUser(), hospital, currentMenu, quit);
    } while (!quit);
}