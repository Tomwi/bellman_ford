#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "bellman_ford.h"

GRAPH graph;
LIST_ELEMENT *route;

/**
 * @brief Traces back the shortest path 
 * @param startX starting X tile
 * @param startY starting Y tile
 * @param dstX final X tile
 * @param dstY final Y tile 
 */
LIST_ELEMENT* traceRoute(int startX, int startY, int dstX, int dstY) {
    NODE *d = graph.nodes[dstX + dstY * WIDTH];
    LIST_ELEMENT *route = malloc(sizeof (LIST_ELEMENT));
    LIST_ELEMENT *tmp = route;
    tmp->self = d;
    // as long as we haven't reached our beginning position
    while (((NODE*) d->parent)->no != startX + startY * WIDTH) {
        // allocate a new element to be added to route
        tmp->nextElement = malloc(sizeof (LIST_ELEMENT));
        tmp = ((LIST_ELEMENT*) tmp)->nextElement;
        tmp->self = ((NODE*) d->parent);
        tmp->nextElement = NULL;
        d = d->parent;
    }
    return route;
}

static int inRoute(NODE *node, LIST_ELEMENT *route) {
    // as long as the current node isn't equal to the node we're seeking
    while (route->self != node) {
        route = ((LIST_ELEMENT*) route)->nextElement;
        if (route == NULL)
            return 0;
    }
    return 1;
}

void freeRoute(LIST_ELEMENT* route) {
    LIST_ELEMENT* tmp = route;
    while (route->nextElement) {
        tmp = route;
        route = route->nextElement;
        free(tmp);
    }
}

/**
 * @brief initialize an edge between two cells
 * @param edge structure to initialize
 * @param x x tile of the cell
 * @param y y tile of the cell
 * @param add distance between the two cells
 */
static void initEdge(EDGE* edge, int x, int y, int add) {
    edge->src = x + y*WIDTH;
    edge->dst = edge->src + add;
    edge->weight = 10;
}

int findEdge(int sx, int sy, int dx, int dy) {
    int i;
    for (i = 0; i < graph.E; i++) {
        if (graph.edges[i]->src == GRID_CELL(sx, sy) && graph.edges[i]->dst == GRID_CELL(dx, dy)) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief remove an edge between two cells
 */
void removeEdge(int sx, int sy, int dx, int dy) {
    int i, tmp = 0;
    for (i = 0; i < graph.E; i++) {
        if ((tmp = findEdge(sx, sy, dx, dy)) >= 0) {
            free(graph.edges[tmp]);
            if (tmp < (graph.E - 1))
                memmove(&graph.edges[tmp], &graph.edges[tmp + 1], ((graph.E - 1) - tmp) * sizeof (EDGE*));
            graph.E--;
            return;
        }
    }
}

void initializeGrid(void) {

    graph.nodes = malloc(sizeof (NODE*) * WIDTH * HEIGHT);
    // is less in a grid
    graph.edges = malloc(sizeof (EDGE*) * WIDTH * HEIGHT * 4);
    int i, j;
    for (i = 0; i < WIDTH; i++) {
        for (j = 0; j < HEIGHT; j++) {
            // allocate a node for each cell in the gred
            graph.nodes[i + j * WIDTH] = malloc(sizeof (NODE));
            graph.nodes[i + j * WIDTH]->dist = INT_MAX;
            graph.nodes[i + j * WIDTH]->parent = NULL;
            graph.nodes[i + j * WIDTH]->no = i + j*WIDTH;
            // no left edge when x = 0
            if (i != 0) {
                graph.edges[graph.E] = malloc(sizeof (EDGE));
                initEdge(graph.edges[graph.E], i, j, -1);
                graph.E++;
            }
            // no right edge when x = WIDTH-1
            if (i != (WIDTH - 1)) {
                graph.edges[graph.E] = malloc(sizeof (EDGE));
                initEdge(graph.edges[graph.E], i, j, 1);
                graph.E++;
            }
            // no upper edge when y = 0
            if (j != 0) {
                graph.edges[graph.E] = malloc(sizeof (EDGE));
                initEdge(graph.edges[graph.E], i, j, -WIDTH);
                graph.E++;
            }
            // no lower edge when y = HEIGHT-1
            if (j != (HEIGHT - 1)) {

                graph.edges[graph.E] = malloc(sizeof (EDGE));
                initEdge(graph.edges[graph.E], i, j, WIDTH);
                graph.E++;
            }
        }
    }
    graph.N = WIDTH*HEIGHT;
}

void deinitializeGrid(void) {
    int i;
    for (i = 0; i < graph.N; i++) {
        free(graph.nodes[i]);
    }
    for (i = 0; i < graph.E; i++) {

        free(graph.edges[i]);
    }
}

int findNode(void* node) {
    int i;
    if (node) {
        for (i = 0; i < graph.N; i++) {
            if (graph.nodes[i] == ((NODE*) node))
                return graph.nodes[i]->no;
        }
    }
    return -1;
}

/**
 * @brief finds the shortest path between to cells in a grid
 * @param startX starting X tile
 * @param startY starting Y tile
 */
void bellman_ford(unsigned int startX, unsigned int startY) {
    int V = graph.N;
    int E = graph.E;
    // distance to our beginning point is of course 0
    graph.nodes[startX + WIDTH * startY]->dist = 0;

    int i, j;
    // update the distances for each node
    for (i = 1; i <= V - 1; i++) {
        for (j = 0; j < E; j++) {
            int penalty = 0;

            int u = graph.edges[j]->src;
            int v = graph.edges[j]->dst;

            int parent = -1;

            parent = findNode(graph.nodes[u]->parent);

            int dir = 0;
            if (parent >= 0) {
                dir = u - parent;
            }

            if ((v - u) != dir && dir != 0) {

                penalty = 5;
            }

            unsigned int weight = graph.edges[j]->weight + penalty;
            // if we can reach this cell faster, update the parent and distance
            if ((graph.nodes[u]->dist + weight) < graph.nodes[v]->dist) {
                graph.nodes[v]->dist = graph.nodes[u]->dist + weight;
                graph.nodes[v]->parent = graph.nodes[u];
            }
        }
    }
}

/**
 * @brief prints a grid with a shortest route marked by *'s
 * @param strtX starting X cell
 * @param strtY starting Y cell
 * @param dstX ending X cell
 * @param dstY ending Y cell
 */
void printRoute(int strtX, int strtY, int dstX, int dstY) {
    LIST_ELEMENT *rt = traceRoute(strtX, strtY, dstX, dstY);
    int i, j;
    // loop through every cell of the grid
    for (j = 0; j < HEIGHT; j++) {
        for (i = 0; i < WIDTH; i++) {
            // if this cell is on the shortes path, mark it
            if (inRoute(graph.nodes[i + j * WIDTH], rt)) {
                printf("*");
            } else
                printf(" ");
            printf("%.2d  ", GRID_CELL(i, j)); //graph.nodes[GRID_CELL(i, j)]->dist);

            if (findEdge(i, j, i + 1, j) >= 0)
                printf("- ");
            else
                printf("  ");
        }
        // print a newline to seperate the rows of the grid
        printf("\n");
        for (i = 0; i < WIDTH; i++) {
            if (findEdge(i, j, i, j + 1) >= 0)
                printf("  |    ");
            else
                printf("       ");
        }
        printf("\n");
    }
    freeRoute(rt);
}
