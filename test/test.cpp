#include <catch2/catch_test_macros.hpp>
#include "Map.h"
#include "Path.h"

#define NUM_ITERATIONS 50

void randPathReversed()
{
    // a property based test. The distance of the shortest path
    // found should be the same if the start/end are swapped

    Map mp("ion_dev_heightmaps/heightmap1.data");
    int x1 = std::rand() % 512;
    int y1 = std::rand() % 512;
    int x2 = std::rand() % 512;
    int y2 = std::rand() % 512;

    Path *pth1 = new Path();
    Path *pth2 = new Path();

    mp.getShortestPath(Point(x1, y1), Point(x2, y2), pth1);
    mp.getShortestPath(Point(x2, y2), Point(x1, y1), pth2);

    REQUIRE(pth1->distance == pth2->distance);

    // cleanup
    delete pth1;
    delete pth2;
}

TEST_CASE("test randPathReversed", "[randPathReversed]")
{
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        randPathReversed();
    }
}
