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
    {
        std::make_pair(UserType::Admin, MenuLevel::Root),
        formatText("Admin Menu", TextColor::fBlue, TextColor::bDefault, true) +
        "\n----------------------------------\n" +
        formatText("[P]", TextColor::fYellow, TextColor::bDefault, true) + " List all Patients\n" +
        formatText("[N]", TextColor::fYellow, TextColor::bDefault, true) + " List all Nurses\n" +
        formatText("[D]", TextColor::fYellow, TextColor::bDefault, true) + " List all Doctors\n" +
        formatText("[R]", TextColor::fYellow, TextColor::bDefault, true) + " List all Receptionists\n" +
        formatText("[A]", TextColor::fYellow, TextColor::bDefault, true) + " List all Admins\n" +
        formatText("[M]", TextColor::fYellow, TextColor::bDefault, true) + " Show messages\n" +
        formatText("[S]", TextColor::fYellow, TextColor::bDefault, true) + " Show log\n" +
        formatText("[X]", TextColor::fYellow, TextColor::bDefault, true) + " Reset program\n" +
        formatText("[L]", TextColor::fYellow, TextColor::bDefault, true) + " Logout\n" +
        "----------------------------------\n"
    },
    {
        std::make_pair(UserType::Patient, MenuLevel::Root),
        formatText("Patient Menu", TextColor::fBlue, TextColor::bDefault, true) +
        "\n----------------------------------\n" +
        formatText("[A]", TextColor::fYellow, TextColor::bDefault, true) + " Make Appointment\n" +
        formatText("[M]", TextColor::fYellow, TextColor::bDefault, true) + " Read Messages\n" +
        formatText("[D]", TextColor::fYellow, TextColor::bDefault, true) + " Available Doctors\n" +
        formatText("[L]", TextColor::fYellow, TextColor::bDefault, true) + " Logout\n" +
        "----------------------------------\n"
    },
    {
        std::make_pair(UserType::Patient, MenuLevel::Appointments),
        formatText("Appointments Menu", TextColor::fBlue, TextColor::bDefault, true) +
        "\n----------------------------------\n" +
        "Choose the condition\n" +
        formatText("[1]", TextColor::fYellow, TextColor::bDefault, true) + " Influenca (Flu)\n" +
        formatText("[2]", TextColor::fYellow, TextColor::bDefault, true) + " COVID-19\n" +
        formatText("[3]", TextColor::fYellow, TextColor::bDefault, true) + " Conjunctivitus\n" +
        formatText("[4]", TextColor::fYellow, TextColor::bDefault, true) + " HIV/AIDS\n" +
        formatText("[5]", TextColor::fYellow, TextColor::bDefault, true) + " Tetanus\n" +
        formatText("[6]", TextColor::fYellow, TextColor::bDefault, true) + " Malaria\n" +
        formatText("[7]", TextColor::fYellow, TextColor::bDefault, true) + " Pneumonia\n" +
        formatText("[8]", TextColor::fYellow, TextColor::bDefault, true) + " Depression\n" +
        formatText("[9]", TextColor::fYellow, TextColor::bDefault, true) + " Epilepsy\n" +
        formatText("[0]", TextColor::fYellow, TextColor::bDefault, true) + " Other\n" +
        formatText("[B]", TextColor::fYellow, TextColor::bDefault, true) + " Back\n" +
        "----------------------------------\n"
    },
    {
        std::make_pair(UserType::Doctor, MenuLevel::Root),
        formatText("Doctor Menu", TextColor::fBlue, TextColor::bDefault, true) +
        "\n----------------------------------\n" +
        formatText("[A]", TextColor::fYellow, TextColor::bDefault, true) + " Show Appointment\n" +
        formatText("[M]", TextColor::fYellow, TextColor::bDefault, true) + " Send Messages\n" +
        formatText("[N]", TextColor::fYellow, TextColor::bDefault, true) + " Available Nurses\n" +
        formatText("[P]", TextColor::fYellow, TextColor::bDefault, true) + " Show Patients\n" +
        formatText("[L]", TextColor::fYellow, TextColor::bDefault, true) + " Logout\n" +
        "----------------------------------\n"
    },
    {
        std::make_pair(UserType::Nurse, MenuLevel::Root),
        formatText("Nurse Menu", TextColor::fBlue, TextColor::bDefault, true) +
        "\n----------------------------------\n" +
        formatText("[A]", TextColor::fYellow, TextColor::bDefault, true) + " Show Appointment\n" +
        formatText("[M]", TextColor::fYellow, TextColor::bDefault, true) + " Send Messages\n" +
        formatText("[P]", TextColor::fYellow, TextColor::bDefault, true) + " Show Patients\n" +
        formatText("[D]", TextColor::fYellow, TextColor::bDefault, true) + " Dispensary\n" +
        formatText("[L]", TextColor::fYellow, TextColor::bDefault, true) + " Logout\n" +
        "----------------------------------\n"
    },
    {
        std::make_pair(UserType::Nurse, MenuLevel::Dispensary),
        formatText("Dispensary Menu", TextColor::fBlue, TextColor::bDefault, true) +
        "\n----------------------------------\n" +
        formatText("[A]", TextColor::fYellow, TextColor::bDefault, true) + " Add Drug\n" +
        formatText("[S]", TextColor::fYellow, TextColor::bDefault, true) + " Show All Drugs\n" +
        formatText("[W]", TextColor::fYellow, TextColor::bDefault, true) + " Show Budget\n" +
        formatText("[B]", TextColor::fYellow, TextColor::bDefault, true) + " Back\n" +
        "----------------------------------\n"
    },
    {
        std::make_pair(UserType::Nurse, MenuLevel::Drug),
        formatText("Drug Menu", TextColor::fBlue, TextColor::bDefault, true) +
        "\n----------------------------------\n" +
        "Choose the condition\n" +
        formatText("[1]", TextColor::fYellow, TextColor::bDefault, true) + " Panadol x200 Tablets Rs312.55\n" +
        formatText("[2]", TextColor::fYellow, TextColor::bDefault, true) + " Duphalac x1 Bottle Rs371.13\n" +
        formatText("[3]", TextColor::fYellow, TextColor::bDefault, true) + " Brufen x10 Tablets Rs.15\n" +
        formatText("[4]", TextColor::fYellow, TextColor::bDefault, true) + " Hand Sanitizer x1 Bottle Rs155.00\n" +
        formatText("[5]", TextColor::fYellow, TextColor::bDefault, true) + " Insulin x1 Syringe Rs180.00\n" +
        formatText("[6]", TextColor::fYellow, TextColor::bDefault, true) + " First Aid x1 Kit Rs3000.00\n" +
        formatText("[7]", TextColor::fYellow, TextColor::bDefault, true) + " Durex x3 Protection Rs300.00\n" +
        formatText("[8]", TextColor::fYellow, TextColor::bDefault, true) + " Multilife x30 Tablets Rs650.00\n" +
        formatText("[9]", TextColor::fYellow, TextColor::bDefault, true) + " Nexum x40 Tablets Rs440.00\n" +
        formatText("[B]", TextColor::fYellow, TextColor::bDefault, true) + " Back\n" +
        "----------------------------------\n"
    },
    {
        std::make_pair(UserType::Receptionist, MenuLevel::Root),
        formatText("Nurse Menu", TextColor::fBlue, TextColor::bDefault, true) +
        "\n----------------------------------\n" +
        formatText("[A]", TextColor::fYellow, TextColor::bDefault, true) + " Show Appointment\n" +
        formatText("[M]", TextColor::fYellow, TextColor::bDefault, true) + " Show Messages\n" +
        formatText("[P]", TextColor::fYellow, TextColor::bDefault, true) + " Show Patients\n" +
        formatText("[W]", TextColor::fYellow, TextColor::bDefault, true) + " Show Funds\n" +
        formatText("[F]", TextColor::fYellow, TextColor::bDefault, true) + " Add Funds\n" +
        formatText("[L]", TextColor::fYellow, TextColor::bDefault, true) + " Logout\n" +
        "----------------------------------\n"
    },
};