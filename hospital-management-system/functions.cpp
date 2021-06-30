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
    File configFile("config.ini");
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
    switch (loggedInUser->getUserType())
    {
        case UserType::Admin:
            break;
        case UserType::Patient:
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
                        printf("%s Logged In!\n", formatText("[SUCCESS]:", TextColor::fGreen).c_str());
                        userLoggedIn = true;
                        break;
                    }

                    printf("%s, %d tries left\n", Error::get("password-invalid").c_str(), 3 - tries);
                    ++tries;
                }

                // Max retries reached error message
                if (userLoggedIn)
                {
                    //
                }

                haltProgram();
                break;
            }
        }
    }
    pFile->close();

    if (!userExists)
    {
        printf("%s %s\n", formatText("[Error]: ", TextColor::fRed, TextColor::bDefault, true).c_str(), Error::get("user-not-found").c_str());
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
        printf("%s %s \nPlease enter your %s again: ", formatText("[Error]: ", TextColor::fRed, TextColor::bDefault, true).c_str(), Error::get("username-small").c_str(), formatText("username", TextColor::fDefault, TextColor::bDefault, true).c_str());
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

        if ((UserType)std::stoi(userInformation[0]) == UserType::Patient)
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
        std::string row = std::to_string((int)userType) + '|' + username + '|' + encrypt(password, username) + '|' + currentDate.mUtcString;
        userDb.write(row);
        printf("%s Your account has been created.\n", formatText("[SUCCESS]:", TextColor::fGreen).c_str());
        haltProgram();
    }

    currentMenu = MenuLevel::Root;
    breadcrumb.clear();
}






void run()
{
    loading(1);
    bool quit;
    Hospital hospital;
    MenuLevel currentMenu;
    std::string menuChoice;
    std::vector<std::string> menuBreadcrumbs;
    std::unique_ptr<User> pLoggedInUser = nullptr;
    init(quit, pLoggedInUser, currentMenu, menuChoice);
    do
    {
        menu(pLoggedInUser, currentMenu, menuBreadcrumbs);
        input(menuChoice);
        processInput(menuChoice, menuBreadcrumbs, pLoggedInUser, hospital, currentMenu, quit);
    } while (!quit);
}