#ifndef MAP_H
#define MAP_H
#include <string>
#include <vector>
#include "Point.h"
#include "Path.h"

class Map
{
public:
    // attrs
    int xDim = 512;
    int yDim = 512;
    int mPerCell = 30;   // 30m per cell from the spec
    int mPerHeight = 11; // 11m per unit of height, from the spec

    // methods
    Map(std::string fpath);
    Path getShortestPath(Point p1, Point p2);

private:
    // attrs
    std::vector<unsigned int> heightGrid; // store 2d data in 1d vector

    // methods
    void parseMapFile(std::string fpath);
    unsigned int getHeight(Point p);
    int getCost(Point p1, Point p2);
};

#endif