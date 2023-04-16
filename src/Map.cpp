#include "Map.h"
#include <fstream>
#include <iostream>
#include <math.h>

Map::Map(std::string fpath)
{
    parseMapFile(fpath);

    std::cout << getHeight(Point(0, 0)) << std::endl;
    std::cout << getCost(Point(2, 0), Point(3, 0));
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

int Map::getCost(Point p1, Point p2)
{
    int xDist = abs(p1.x - p2.x);
    int yDist = abs(p1.y - p2.y);
    if (xDist + yDist > 1)
    {
        std::cerr << "attempted to get cost between diagonal or non-adjacent points\n";
        throw -1;
    }
    else if (xDist == 0 && yDist == 0)
    {
        // the cost from one cell to that same cell is zero
        return 0;
    }

    // the cost is the difference in height plus the horizontal movement
    // we know we have moved one cell horizontally, so add the horizontal scale once
    int vCost = abs(getHeight(p2) - getHeight(p1)) * mPerHeight;
    return vCost + mPerCell;
}
