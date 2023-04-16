//
//

#ifndef POINT_H
#define POINT_H


class Point
{
public:
    int x;
    int y;
    Point();
    Point(int x, int y);
    Point(const Point &p);
    bool operator<(const Point &p2) const;
    bool operator==(const Point &p2) const;
};

#endif // POINT_H
