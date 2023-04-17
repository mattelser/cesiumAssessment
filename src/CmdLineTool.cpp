#include "CmdLineTool.h"
#include <iostream>
#include <getopt.h>

CmdLineTool::CmdLineTool(int argc, char *argv[]){

    parse(argc, argv);

    mp = new Map(fPath);
}

int CmdLineTool::run(){
    auto pth = new Path();
    int rcode = mp->getShortestPath(start, end, pth);

    if (rcode){
        // failed to find a path
        std::cerr << "Err: failed to find a path" << std::endl;
        return -1;
    }

    printf("Length of shortest path: %dm\n", pth->distance);

    // cleanup
    delete pth;

    return 0;
}

void CmdLineTool::printUsage(){
    printf("usage: pathFinder -m path/to/heightmap -s #,# -e #,#\n");
}

Point CmdLineTool::strToPoint(char * str){
    int nums[2];
    char* numStr;
    numStr = strtok(str, ",");

    for (int i = 0; i < 2; i++) {
        nums[i] = atoi(numStr);
        // atoi returns zero for non-numeric strings
        // zero is a valid input but we do want to raise the alarm
        // if we get zero when we shouldn't
        if (nums[i] == 0 && strcmp("0", numStr)){
            fprintf(stderr, "illegal point definition\n");
            printUsage();
            exit(-1);
        }
        // set up the next comma separated string
        numStr = strtok(NULL, ",");
    }

    return Point(nums[0], nums[1]);
}

void CmdLineTool::parse(int argc, char **argv){
    if (argc < 2){
        std::cerr << "missing input file\n" << std::endl;
        printUsage();
        exit(-1);
    }
    int c;
    while((c = getopt(argc, argv, "m:s:e:h")) != -1){
        switch(c){
            case 'm':
                fPath = optarg;
                break;
            case 's':
                start = strToPoint(optarg);
                break;
            case 'e':
                end = strToPoint(optarg);
                break;
            case 'h':
                printUsage();
                exit(0);
                break;
            default:
                fprintf(stderr, "illegal/missing argument %c\n", optopt);
                printUsage();
                exit(-1);
        }
    }

}
