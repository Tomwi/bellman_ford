#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "mine.h"
#include "bellman_ford.h"

int intInList(int* list, int val, int size){
	int i;
	for(i=0; i<size; i++){
		if(list[i]==val)
			return 1;
	}
	return 0;
}

int * initMines(GRAPH* graph, int amount, int gridWidth, int gridHeight){
	srand (time(NULL));
	// We cannot place more mines than places that are available
	if(gridWidth*gridHeight < amount)
		return NULL;
		
	int * mines = malloc(sizeof(int)*amount);	
	if(mines==NULL)
		return NULL;
    int i,j;
	for(i=0; i<amount; i++){
		int edge;
		while(intInList(mines, (edge = rand()%EDGES_IN_GRID(gridWidth, gridHeight)), amount));
		mines[i] = edge;
	}
	return mines;
}