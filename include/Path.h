#ifndef PATH_H
#define PATH_H

#include "Point.h"
#include <list>

class Path {
public:
    Path();

    int distance;
    void prepend(Point p) {pList.push_front(p);};
    void append(Point p) {pList.push_back(p);};
    void printPath();

private:
    std::list<Point> pList;

};

#endif // PATH_H
