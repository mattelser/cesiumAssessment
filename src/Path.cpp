#include "Path.h"
#include <stdio.h>

void printPath(Path p)
{
    for (auto i : p)
    {
        printf("(%d, %d) ", i.x, i.y);
    }
    printf("\n");
}