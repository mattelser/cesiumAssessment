#include "Map.h"
#include "Path.h"

int main()
{
    Map mp("ion_dev_heightmaps/heightmap1.data");

    Path pth;
    mp.getShortestPath(Point(0, 0), Point(10, 10), &pth);

    printPath(pth);

    // delete pth;
    return 0;
}
