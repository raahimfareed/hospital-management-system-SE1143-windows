#include <iostream>
#include <cstring>

#include "Config.hpp"
#include "Utils.hpp"
#include "Error.hpp"
#include "Menu.hpp"
#include "Functions.hpp"

int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);

    if (argc == 2 && !strcmp(argv[1], "-v"))
    {
        printf("Hospital Management System: %s\n", Config::mcVersion.c_str());
        return EXIT_SUCCESS;
    }
    run();
}