#ifndef MAP_H
#define MAP_H
#include <string>
#include <vector>
#include "Point.h"
#include "Path.h"

#define DEFAULT_XDIM 512
#define DEFAULT_YDIM 512

class Map
{
public:
    // attrs
    int xDim = DEFAULT_XDIM;
    int yDim = DEFAULT_YDIM;
    int mPerCell = 30;   // 30m per cell from the spec
    int mPerHeight = 11; // 11m per unit of height, from the spec

    // methods
    Map(std::string fpath, int xDim = DEFAULT_XDIM, int yDim = DEFAULT_YDIM);
    int getShortestPath(Point p1, Point p2, Path *pth);

private:
    // attrs
    std::vector<unsigned int> heightGrid; // store 2d data in 1d vector

    // methods
    void parseMapFile(std::string fpath);
    unsigned int getHeight(Point p);
    int getDist(Point p1, Point p2);
    int heuristic(Point p1, Point end);
    bool pointIsValid(Point p);
};

#endif