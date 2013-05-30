#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define WIDTH (5)
#define HEIGHT (5)

#define GRID_CELL(x,y) (x+WIDTH*y)
#define EDGES_IN_GRID(w,h) ((w-2)*(h-2)*4 + 4*2 + ((2*3*(w-2)) + 2*3*(h-2)))

typedef struct {
    unsigned int dist;
    void *parent;
    unsigned int no;
} NODE;

typedef struct {
    unsigned int src;
    unsigned int dst;
    unsigned int weight;
} EDGE;

typedef struct {
    int N, E;
    NODE ** nodes;
    EDGE ** edges;
} GRAPH;


void initializeGrid(void);
void deinitializeGrid(void);
void removeEdge(int sx, int sy, int dx, int dy);
int findEdge(int sX, int sY, int dX, int dY);

#endif