#include <string>
#include <map>

#include "Menu.hpp"
#include "Utils.hpp"
#include "Functions.hpp"

std::string Menu::get(std::pair<UserType, MenuLevel> key)
{
    return mMenus[key];
}

std::map<std::pair<UserType, MenuLevel>, std::string> Menu::mMenus = {
    {
        std::make_pair(UserType::Guest, MenuLevel::Root),
        formatText("Main Menu", TextColor::fBlue, TextColor::bDefault, true) +
        "\n----------------------------------\n" +
        formatText("[L]", TextColor::fYellow, TextColor::bDefault, true) + "ogin\n" +
        formatText("[S]", TextColor::fYellow, TextColor::bDefault, true) + "ignup\n" +
        formatText("[H]", TextColor::fYellow, TextColor::bDefault, true) + "elp\n" +
        formatText("[C]", TextColor::fYellow, TextColor::bDefault, true) + "redits\n" +
        formatText("[E]", TextColor::fYellow, TextColor::bDefault, true) + "xit\n" +
        "----------------------------------\n"
    },
    {
        std::make_pair(UserType::Guest, MenuLevel::Login),
        formatText("Login Menu", TextColor::fBlue, TextColor::bDefault, true) +
        "\n----------------------------------\n" +
        formatText("[P]", TextColor::fYellow, TextColor::bDefault, true) + "atient\n" +
        formatText("[N]", TextColor::fYellow, TextColor::bDefault, true) + "urse\n" +
        formatText("[D]", TextColor::fYellow, TextColor::bDefault, true) + "octor\n" +
        formatText("[R]", TextColor::fYellow, TextColor::bDefault, true) + "eceptionist\n" +
        formatText("[A]", TextColor::fYellow, TextColor::bDefault, true) + "dmin\n" +
        formatText("[B]", TextColor::fYellow, TextColor::bDefault, true) + "ack\n" +
        "----------------------------------\n"
    },
    {
        std::make_pair(UserType::Guest, MenuLevel::Signup),
        formatText("Signup Menu", TextColor::fBlue, TextColor::bDefault, true) +
        "\n----------------------------------\n" +
        formatText("[P]", TextColor::fYellow, TextColor::bDefault, true) + "atient\n" +
        formatText("[N]", TextColor::fYellow, TextColor::bDefault, true) + "urse\n" +
        formatText("[D]", TextColor::fYellow, TextColor::bDefault, true) + "octor\n" +
        formatText("[R]", TextColor::fYellow, TextColor::bDefault, true) + "eceptionist\n" +
        formatText("[A]", TextColor::fYellow, TextColor::bDefault, true) + "dmin\n" +
        formatText("[B]", TextColor::fYellow, TextColor::bDefault, true) + "ack\n" +
        "----------------------------------\n"
    },
};