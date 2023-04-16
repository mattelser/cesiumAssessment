#include "Map.h"
#include "Point.h"
#include "Path.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <queue>
#include <map>

Map::Map(std::string fpath, int xDim, int yDim)
{
    this->xDim = xDim;
    this->yDim = yDim;

    parseMapFile(fpath);

    Path pth = getShortestPath(Point(0, 0), Point(10, 10));
    printPath(pth);
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

    mapFile.close();
}

unsigned int Map::getHeight(Point p)
{
    return heightGrid.at((p.y * xDim) + p.x);
}

bool Map::pointIsValid(Point p){
   return p.x < xDim && p.y < yDim && p.x >= 0 && p.y >= 0;
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
    // we take the abs since dropping down is not a negative cost, and we cast
    // to int because otherwise abs is ambiguous to the compiler
    int vCost = abs((int)(getHeight(p2) - getHeight(p1)) * mPerHeight);
    return vCost + mPerCell;
}

typedef std::pair<int, Point> PriPair;

struct distWithDefault
{
    // TODO explain this
    int val = INT_MAX;
};

struct compFirstOfPair
{
    bool operator()(const PriPair &lhs, const PriPair &rhs) const
    {
        return lhs.first > rhs.first;
    }
};

void getNeighbors(Point p, std::vector<Point> *vec)
{
    vec->clear(); // make sure we've got an empty vec

    vec->push_back(Point(p.x, p.y + 1));
    vec->push_back(Point(p.x, p.y - 1));
    vec->push_back(Point(p.x + 1, p.y));
    vec->push_back(Point(p.x - 1, p.y));
}

Path Map::getShortestPath(Point start, Point end)
{
    // create a priority queue of pairs of (cost, point) with a custom
    // comparison function that only uses cost as the priority
    std::priority_queue<PriPair, std::vector<PriPair>, compFirstOfPair> pq;
    std::map<Point, Point> prev;
    std::map<Point, distWithDefault> dist;

    // initialize the distance and priority queue for the start
    pq.push(std::make_pair(0, start));
    dist[start] = distWithDefault{0};

    std::vector<Point> neighbors;
    bool earlyExit = false;
    while (!pq.empty() && !earlyExit)
    {
        // extract the point with the lowest cost
        PriPair curr = pq.top();
        pq.pop();

        int currCost = curr.first;
        Point currP = curr.second;

        // if (currCost != dist[currP].val){
        //     continue;
        // }

        getNeighbors(currP, &neighbors);
        for (Point nbr : neighbors)
        {
            if (!pointIsValid(nbr)){
                continue;
            }

            int newCost = currCost + getCost(currP, nbr);
            int oldCost = dist[nbr].val;
            if (newCost < oldCost)
            {
                dist[nbr] = distWithDefault{newCost};
                prev[nbr] = currP;
                pq.emplace(newCost, nbr);
            }

            if (nbr == end)
            {
                // if we've found any path to the end, skip calculating others
                earlyExit = true;
            }
        }
    }

    // TODO handle no path found

    Path pth;

    Point currP = end;
    pth.push_front(currP);
    while (prev.find(currP) != prev.end()){
        currP = prev[currP];
        pth.push_front(currP);
    }

    return pth;
}