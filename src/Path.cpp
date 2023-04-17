#include "Path.h"
#include <stdio.h>

Path::Path(){
    distance = INT_MAX;
    pList = std::list<Point>();
}

void Path::printPath() {
    for (auto i : pList) {
        printf("(%d, %d) ", i.x, i.y);
    }
    printf("\n");
}