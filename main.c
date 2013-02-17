/* 
 * File:   main.c
 * Author: Tom
 *
 * Created on 16 februari 2013, 23:03
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "bellman_ford.h"

int main(int argc, char** argv) {
    // initialize a 10x10 grid
    initializeGrid();
    removeEdge(0, 0, 1, 0);
    // apply the algorithm with starting cell 0,0
    bellman_ford(0, 0);
    // print the shortest path between cell 0,0 and cell 1,0
    printRoute(0, 0, 1, 0);
    // free used resources for building up the grid
    deinitializeGrid();
    return (EXIT_SUCCESS);
}

