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
    // apply the algorithm with starting cell 5,4
    bellman_ford(5, 4);
    // print the shortest path between cell 5,4 and cell 3,9
    printRoute(5, 4, 3, 9);
    // free used resources for building up the grid
    deinitializeGrid();
    return (EXIT_SUCCESS);
}

