#include "Parser.h"
#include <iostream>
#include <string>
#include <fstream>

void parse(std::string fpath)
{
    std::ifstream mapFile(fpath);

    if (!mapFile.good())
    {
        std::cerr << "Failed to open file\n";
    }

    char c;
    int i = 100;
    while (mapFile.good())
    {
        std::cout << mapFile.get() << std::endl;
        i--;
        if (i < 0)
        {
            break;
        }
    }
}