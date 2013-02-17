/* 
 * File:   bellman_ford.h
 * Author: Tom
 *
 * Created on 17 februari 2013, 19:05
 */

#ifndef BELLMAN_FORD_H
#define	BELLMAN_FORD_H

#define WIDTH (10)
#define HEIGHT (10)

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

typedef struct {
    NODE *self;
    void *nextElement;
} LIST_ELEMENT;

void initializeGrid(void);
void bellman_ford(unsigned int startX, unsigned int startY);
void printRoute(int strtX, int strtY, int dstX, int dstY);
void deinitializeGrid(void);

#endif	/* BELLMAN_FORD_H */

