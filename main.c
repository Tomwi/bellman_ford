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
#include "mine.h"

// Explore as much as possible in  n steps
void explore(int *mines, int startX, int startY, int n){
	int pos[2];
	pos[0] = startX;
	pos[1] = startY;
	
	EDGE* visited = malloc(sizeof(EDGE*)*EDGES_IN_GRID(WIDTH, HEIGHT));
	while(n){
		
	}
}

int main(int argc, char** argv) {
    // initialize a 10x10 grid
    initializeGrid();
	int* mines = initMines(&graph, 13, WIDTH, HEIGHT);
   
    // apply the algorithm with starting cell 0,0
    bellman_ford(0, 0);
    
    printRoute(0, 0, 4, 4);
    // free used resources for building up the grid
    deinitializeGrid();
    return (EXIT_SUCCESS);
}

