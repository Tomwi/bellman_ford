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

GRAPH graph;

int edgC;

void printEdges(void) {
    int i;
    for (i = 0; i < graph.E; i++) {
        printf("%d, %d -> %d = %d\n", i, graph.edges[i]->src, graph.edges[i]->dst, graph.edges[i]->weight);
    }
}

void printGrid(void) {
    int i, j;
    for (j = 0; j < HEIGHT; j++) {
        for (i = 0; i < WIDTH; i++) {
            printf("%d ", graph.nodes[i + j * WIDTH]->dist);
        }
        printf("\n");
    }
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

    int i, j;
    for (j = 0; j < HEIGHT; j++) {
        for (i = 0; i < WIDTH; i++) {
            if (((NODE*) n->parent)->no == i + j * WIDTH) {
                printf("_%.2d_ ", graph.nodes[i + j * WIDTH]->dist);
                n = n->parent;
            } else
                printf(" %.2d  ", graph.nodes[i + j * WIDTH]->dist);

        }
        printf("\n");
    }
}

int main(int argc, char** argv) {
    initializeGrid();
    bellman_ford(9, 9);
    printRoute(9, 9, 0, 0);
    return (EXIT_SUCCESS);
}

