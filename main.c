/* 
 * File:   main.c
 * Author: Tom
 *
 * Created on 16 februari 2013, 23:03
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

typedef struct{
    NODE *self;
    void *nextElement;
}LIST_ELEMENT;

GRAPH graph;
LIST_ELEMENT *route;
int edgC;

LIST_ELEMENT* traceRoute(int startX, int startY, int dstX, int dstY){
    NODE *d = graph.nodes[dstX+dstY*WIDTH];
    NODE *s = graph.nodes[startX+startY*WIDTH];
    LIST_ELEMENT *route = malloc(sizeof(LIST_ELEMENT));
    LIST_ELEMENT *tmp = route;
    tmp->self = d;
    while(((NODE*) d->parent)->no != startX+startY*WIDTH){
        tmp->nextElement = malloc(sizeof(LIST_ELEMENT));
        tmp = ((LIST_ELEMENT*)tmp)->nextElement;
        tmp->self = ((NODE*) d->parent);
        tmp->nextElement = NULL;
        d = d->parent; 
    }
    return route;
}

int inRoute(NODE *node, LIST_ELEMENT *route){
    
    while(route->self != node){
        route = ((LIST_ELEMENT*)route)->nextElement;
        if(route==NULL)
            return 0;
    }
    return 1;
}

void initEdge(EDGE* edge, int x, int y, int add) {
    edge->src = x + y*WIDTH;
    edge->dst = edge->src + add;
    edge->weight = 1;
}

void initializeGrid(void) {

    graph.nodes = malloc(sizeof (NODE*) * WIDTH * HEIGHT);
    // is less in a grid
    graph.edges = malloc(sizeof (EDGE*) * WIDTH * HEIGHT * 4);
    int i, j;
    for (i = 0; i < WIDTH; i++) {
        for (j = 0; j < HEIGHT; j++) {

            graph.nodes[i + j * WIDTH] = malloc(sizeof (NODE));
            graph.nodes[i + j * WIDTH]->dist = INT_MAX;
            graph.nodes[i + j * WIDTH]->parent = NULL;
            graph.nodes[i + j * WIDTH]->no = i + j*WIDTH;
            if (i != 0) {
                graph.edges[edgC] = malloc(sizeof (EDGE));
                initEdge(graph.edges[edgC], i, j, -1);
                edgC++;
            }
            if (i != (WIDTH - 1)) {
                graph.edges[edgC] = malloc(sizeof (EDGE));
                initEdge(graph.edges[edgC], i, j, 1);
                edgC++;
            }
            if (j != 0) {
                graph.edges[edgC] = malloc(sizeof (EDGE));
                initEdge(graph.edges[edgC], i, j, -WIDTH);
                edgC++;
            }
            if (j != (HEIGHT - 1)) {
                graph.edges[edgC] = malloc(sizeof (EDGE));
                initEdge(graph.edges[edgC], i, j, WIDTH);
                edgC++;
            }
        }
    }

    graph.N = WIDTH*HEIGHT;
    graph.E = edgC;
    //printEdges();

}

void bellman_ford(unsigned int startX, unsigned int startY) {
    int V = graph.N;
    int E = graph.E;
    // distance to our beginning point is of course 0
    graph.nodes[startX + WIDTH * startY]->dist = 0;

    int i, j;
    for (i = 1; i <= V - 1; i++) {
        for (j = 0; j < E; j++) {
            int u = graph.edges[j]->src;
            int v = graph.edges[j]->dst;
            unsigned int weight = graph.edges[j]->weight;
            if (graph.nodes[u]->dist + weight < graph.nodes[v]->dist) {
                graph.nodes[v]->dist = graph.nodes[u]->dist + weight;
                graph.nodes[v]->parent = graph.nodes[u];
            }
        }
    }


}

void printRoute(int strtX, int strtY, int dstX, int dstY) {
    NODE *n = graph.nodes[dstX + dstY * WIDTH];
    NODE *s = graph.nodes[strtX + strtY * WIDTH];
    LIST_ELEMENT *rt = traceRoute(strtX,strtY,dstX,dstY);
    int i, j;
    for (j = 0; j < HEIGHT; j++) {
        for (i = 0; i < WIDTH; i++) {
            if(inRoute(graph.nodes[i + j * WIDTH],rt)){
                printf("*");
            }
            else
                printf(" ");
            printf("%.2d  ", graph.nodes[i + j * WIDTH]->dist);
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {
    initializeGrid();
    bellman_ford(5, 4);
    printRoute(5, 4, 3, 9);
    return (EXIT_SUCCESS);
}

