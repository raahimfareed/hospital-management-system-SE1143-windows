#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Config.hpp"
#include "Utils.hpp"
#include "User.hpp"
#include "File.hpp"
#include "Hospital.hpp"

void loading(const size_t& loop = 3);

/*
 * @brief Formats text for styling and colors, supports only ANSI codes
 * @param text the text needed to be formatted
 * @param color text color code, dependant on TextColor enum
 * @param bgColor background color code, dependant on TextColor enum
 * @param bold if text needs to be bold
 * @param italic if text needs to be italicized
 * @param inverse swaps text color and background color
 * @return formatted text as per user requirements
 */
std::string formatText(const std::string& text, const TextColor& color = TextColor::fDefault, const TextColor& bgColor = TextColor::bDefault, const bool bold = false, const bool italic = false, const bool inverse = false);

/*
 * @brief Halts the program using cin.get()
 * @param message optional parameter, determines of pause message needs to be shown or not
 */
void haltProgram(const bool message = true);

void inputPlaceholder(const std::vector<std::string>& breadcrumbs, const std::unique_ptr<User>& loggedInUser, const bool hidden = false);
/*
 * @brief Template function for handling user input
 * @param userInput stores user input, passed by reference
 */
template <typename T>
void input(T& userInput);

/*
 * @brief Overload for template function for handling user input
 * @param userInput stores user input, passed by reference
 */
void input(std::string& userInput);

void header();

void firstTimeSetup(std::unique_ptr<User>& loggedInUser, File& configFile);

bool init(bool& mainLoop, std::unique_ptr<User>& loggedInUser, MenuLevel& menuLevel, std::string& menuChoice);

void processInput(std::string& userInput, std::vector<std::string>& breadcrumb, std::unique_ptr<User>& loggedInUser, Hospital& hospital, MenuLevel& currentMenu, bool& quit);

void menu(const std::unique_ptr<User>& loggedInUser, const MenuLevel& menuLevel, const std::vector<std::string>& breadcrumbs);

std::string encrypt(std::string text, std::string key);

bool decrypt(std::string text, std::string key, std::string encryptedText);

std::string userTypeToString(const UserType& type);




void run();