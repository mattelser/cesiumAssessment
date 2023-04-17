### Summary
This repo provides a command line tool to print the distance of the shortest path 
when given a heightmap, start, and end points. It uses the A* pathfinding algorithm, 
and has a Catch2 based test harness. 

### build/run instructions
This project is set up using cmake. The following will generate a makefile, then
run that makefile to build the project. See requirements section for dependencies
```
> cd build
> cmake ..
> make
```
Now the executables are available in the build directory. The executables are:
- pathFinder: The path finding CLI.
  `usage: pathFinder -m path/to/heightmap -s #,# -e #,#` where `#,#` are (x,y) 
  values for the start and end of the desired path
- tests: runs the test(s) for this repo

### known limitations and future work
- No part of this feels complete. Rather than sacrifice a full portion of 
  any of the project (e.x. better documentation at the expense of any test harness),
  I have ended up only mostly completing everything. 
- There is only one unit test, and it does not pass. It is a property based test
for correctness of the pathfinding algorithm. A correct shortest path algorithm 
  should find a path of the same distance if the start and end are swapped. This 
  is not the case, but time limitations have prevented finding the source.
- Support for arbitrary sized maps could be readily implemented. Ideally the files
  would embed their dimensions themselves for easy parsing, but this would require
  a formatting change and is out of spec.
- The project was only tested on one machine, a 2019 intel based Mac.   
- Visualization of the heightmap and path found would be nice.

### Requirements:
Catch2 - [installation instructions](https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md#installing-catch2-from-git-repository)

### Time Estimate:
approximately 12 hours. What I produced in the suggested 4 hours did not seem 
like an adequate representation of what work I can do. 