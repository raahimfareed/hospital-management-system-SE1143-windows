#pragma once
#include <memory>
#include <string>

#include "Config.hpp"
#include "Utils.hpp"
#include "User.hpp"

void loading(const int& loop = 3);

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

void inputPlaceholder(const bool hidden = false);

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

void firstTimeSetup();

bool init(bool& mainLoop, std::unique_ptr<User>& loggedInUser, std::string& menuChoice);

void processInput(std::string& userInput);

void menu(std::string userInput);

std::string encrypt(std::string text, std::string key);

bool decrypt(std::string text, std::string key, std::string encryptedText);


void run();