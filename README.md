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

### Late edit:
After a day on another project, I came back and found/fixed a few of the issues
mentioned in the known limitations section. I have left that section unedited, as
editing it does not feel in the spirit of the assessment. I have fixed the following:
- the "property of consistency" unit test works. - the 'early exit' check needed to be
done outside of the relaxation block
  - the hash function for points led to inefficent use of the maps `prev` 
    and `dist` - the previous hash function was simply an xor of the `x` and `y`
    component of the point. This could only yield 512 different hashes for the 
    entire 512x512 grid, and the distribution among buckets in the unordered_map 
    would be uneven. All this would lead to very long lookups compared to a proper
    hash function. 
    - With these changes the time speedup of a long path (e.x. 0,0 to 511,511) 
  is significant. Timing a few of these by hand take the old time of ~5s to ~1.75s.
      - These changes took about 10 minutes to find and fix.

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