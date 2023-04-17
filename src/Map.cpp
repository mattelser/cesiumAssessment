#include "Map.h"
#include "Point.h"
#include "Path.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <queue>
#include <unordered_map>

Map::Map(std::string fpath, int xDim, int yDim)
{
    this->xDim = xDim;
    this->yDim = yDim;

    parseMapFile(fpath);
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

int Map::heuristic(Point p1, Point end){
    // additionally consider the distance of the point in space from the end
    // note that we convert to meters to keep calculations scaled properly and
    // we use all three dimensions, since we have a height map
    int xDist = (end.x - p1.x) * mPerCell;
    int yDist = (end.y - p1.y) * mPerCell;
    int zDist = (getHeight(end) - getHeight(p1)) * mPerHeight;

    return sqrt(pow(xDist, 2) + pow(yDist, 2) + pow(zDist, 2));
}

int Map::getDist(Point p1, Point p2)
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

// -------------------------------------------
//          Begin pathfinding functions
// -------------------------------------------

// ------------- Helper functions ------------
// ----------------- and types ---------------

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


struct pointHash{
    size_t operator()(const Point& p) const {
        return std::hash<int>{}(p.x) ^ std::hash<int>{}(p.y);
    }
};

// --------- Actual shortest path alg ------------

int Map::getShortestPath(Point start, Point end, Path * pth)
{
    // create a priority queue of pairs of (cost, point) with a custom
    // comparison function that only uses cost as the priority
    std::priority_queue<PriPair, std::vector<PriPair>, compFirstOfPair> pq;
    std::unordered_map<Point, Point, pointHash> prev;
    std::unordered_map<Point, distWithDefault, pointHash> dist;

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

        if (currCost != dist[currP].val){
            continue;
        }

        getNeighbors(currP, &neighbors);
        for (Point nbr : neighbors)
        {
            if (!pointIsValid(nbr)){
                continue;
            }

            int newCost = currCost + getDist(currP, nbr) + heuristic(nbr, end);
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

    // handle no path found
    if (prev.find(end) == prev.end()){
        // return an error and leave the path defaults
        return -1;
    }

    // assemble the path working backwards, since we only know the previous cells
    pth->distance = 0;
    Point currP = end;
    pth->append(currP);
    while (prev.find(currP) != prev.end()){
        // tally the distance as we build the path
        pth->distance += getDist(currP, prev[currP]);

        // append the previous cell to our path
        currP = prev[currP];
        pth->prepend(currP);
    }


    return 0;
}