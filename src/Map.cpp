#include "Map.h"
#include <fstream>
#include <iostream>

Map::Map(std::string fpath)
{
    parseMapFile(fpath);

    std::cout << getHeight(Point(0, 0));
}

void Map::parseMapFile(std::string fpath)
{
    std::ifstream mapFile(fpath);

    if (!mapFile.good())
    {
        std::cerr << "Failed to open file\n";
    }

    // expand the height grid vector to its known final size
    // to save time on expansions
    heightGrid.reserve(xDim * yDim);

    while (mapFile.good())
    {
        heightGrid.push_back(mapFile.get());
    }
}

unsigned int Map::getHeight(Point p)
{
    // TODO explain this
    if (p.x >= xDim || p.y >= yDim)
    {
        return -1;
    }

    return heightGrid.at((p.y * xDim) + p.x);
}
