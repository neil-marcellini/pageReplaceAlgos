# Comparison of Page Replacement Algorithms
For the final lab of my Operating Systems class my task was to compare the Least Recently Used (LRU) page replacement algorithm against the optimal page replacement algorithm (OPT). Page replacement algorithms are tested against OPT because it looks into the future and replaces the page that will not be used for the longest period of time, but because of this it can not be implemented in a real system.

The program shows each state of the memory as it reads in frames from the reference string. `*` after a page number signals it was just added and therefore a page fault occurred. `<` after a page number signals a page reference. For OPT `-1` indicates that slot in memory is empty. OPT is implemented with an array whereas LRU uses a Quasi-Stack implementation with a double linked list which means no search is required for replacement. 

After each algorithm runs it prints the number of page faults. At the end the "Quality Ratio LRU vs. OPT" is printed. This is calculated by dividing the number of page faults for LRU by the number of page faults for OPT. It will always be greater than 1, but the closer it is the better an algorithm is. The goal of this was to show that LRU is a good approximation for OPT.

## Prerequisites
This program is designed to be run on Linux.

## Getting Started
Open up the replace folder in terminal. To compile and run:
```
cd cmake-build-debug
cmake ..
make
./replace <num of frames> <ref string length> [<upper page number bound>]
```
## Configuration
If you run ./replace with no extra parameters it will show you the usage. 

`<num of frames>` is the size of your memory, the max number of pages that it can hold. `<ref string length>` controls how many pages are passed into the program. The reference string is generated pseudo-randomly each time. `<upper page number bound>` sets the max page number. 

## What I Learned
To implement LRU, I had to figure out which pointers to change, and in what order so as to not create a floating pointer or a segmentation fault. Doing so took me a long time, but drawing out the double linked list and changing pointers step by step on paper helped me accomplish this.

I also learned that when starting on a complex algorithm it is best to program the most simple cases first and then add the more nuanced scenarios.

## Acknowledgements
The basic structure of this program was created by Dr. Bieszczad for COMP 362 Operating Systems at CSU Channel Islands. He also answered many of my questions as I worked on the project. Anything under a `//TODO` comment is my code. 
