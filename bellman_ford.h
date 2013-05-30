/* 
 * File:   bellman_ford.h
 * Author: Tom
 *
 * Created on 17 februari 2013, 19:05
 */

#ifndef BELLMAN_FORD_H
#define	BELLMAN_FORD_H

#include "grid.h"

typedef struct {
    void *self;
    void *nextElement;
} LIST_ELEMENT;

void bellman_ford(unsigned int startX, unsigned int startY);
void printRoute(int strtX, int strtY, int dstX, int dstY);

extern GRAPH graph;
#endif	/* BELLMAN_FORD_H */

