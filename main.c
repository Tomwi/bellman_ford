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
    removeEdge(0, 0, 0, 1);
   
    // apply the algorithm with starting cell 0,0
    bellman_ford(0, 0);
    
    printRoute(0, 0, 9, 9);
    // free used resources for building up the grid
    deinitializeGrid();
    return (EXIT_SUCCESS);
}

