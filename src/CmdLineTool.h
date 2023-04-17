#ifndef PATHFINDER_CMDLINETOOL_H
#define PATHFINDER_CMDLINETOOL_H

#include "Map.h"
#include "Point.h"
#include <string>

class CmdLineTool {
public:
    CmdLineTool(int argc, char *argv[]);
    int run();

private:
    std::string fPath;
    Map *mp;
    Point start;
    Point end;

    void parse(int agc, char *argv[]);
    Point strToPoint(char * str);
    void printUsage();

};

#endif
