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

void loading(const int& loop)
{
    using namespace std::chrono_literals;
    printf("Loading program, please wait");
    for (size_t i = 0; i < 3; ++i)
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

void inputPlaceholder(const bool hidden)
{
    if (hidden) return;

    std::string placeholder = "";
    // std::string placeholder = formatText(username + "@" + userType + "\n~", TextColor::fMagenta, TextColor::bDefault, true);

    // for (std::string location : gMenuBreadcrumbs)
    // {
    //     placeholder.append(formatText('/' + location, TextColor::fMagenta, TextColor::bDefault, true));
    // }

    placeholder.append(formatText(" > ", TextColor::fMagenta, TextColor::bDefault, true));

    printf("%s", placeholder.c_str());
}

void header()
{
    printf("----------------------------------\n");
    printf("=== %s ===\n", formatText("Hospital Management System", TextColor::fBlack, TextColor::bGreen).c_str());
    printf("----------------------------------\n");
}

void firstTimeSetup()
{
    header();
    printf("Welcome to %s!\nThis is your first time starting this program therefore you will need to create an admin account!\nDo you wish to proceed? %ses/%so: ", formatText("Extricate", TextColor::fCyan, TextColor::bDefault, true).c_str(), formatText("[Y]", TextColor::fYellow, TextColor::bDefault, true).c_str(), formatText("[N]", TextColor::fYellow, TextColor::bDefault, true).c_str());
    std::string choice;
    input(choice);
    if (toupper(choice[0]) == 'Y')
    {
        std::string username;
        std::string password;
        User admin();
        return;
    }

    printf("First time setup dialog will appear next time when you start the program!\n");
    haltProgram();
    exit(EXIT_SUCCESS);
}

bool init(bool& mainLoop, std::unique_ptr<User>& loggedInUser, std::string& menuChoice)
{
    File configFile("config.ini");
    std::string initLine = configFile.search(1);
    if (initLine == "")
    {
        firstTimeSetup();
    }
    mainLoop = false;
    menuChoice = "";
    loggedInUser = std::move(std::unique_ptr<User>());
    return true;
}

void menu(std::string userInput)
{
    system(CLEAR);

    header();

    switch (toupper(userInput[0]))
    {
    case '\0':
        printf("%s", Menu::get("root").c_str());
        break;
    }
}

void processInput(std::string& userInput)
{
    haltProgram();
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




void run()
{
    loading();
    std::unique_ptr<User> pLoggedInUser;
    bool quit;
    std::string menuChoice;
    Hospital hospital;
    bool firstBoot = init(quit, pLoggedInUser, menuChoice);
    do
    {
        menu(menuChoice);
        input(menuChoice);
        processInput(menuChoice);
    } while (!quit);
}