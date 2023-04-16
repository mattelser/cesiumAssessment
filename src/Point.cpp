//
//

#include <math.h>

#include "Point.h"

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

Point::Point(const Point &p2)
{
    this->x = p2.x;
    this->y = p2.y;
}

Point::Point()
{
    this->x = -1;
    this->y = -1;
}

bool Point::operator<(const Point &p2) const
{
    // compare by distance from zero. Since we're just doing a size comparison
    // of size we can skip the sqrt involved in a normal distance calculation
    return (pow(x, 2) + pow(y, 2)) < (pow(p2.x, 2) + pow(p2.y, 2));
}

bool Point::operator==(const Point &p2) const
{
    return x == p2.x && y == p2.y;
}