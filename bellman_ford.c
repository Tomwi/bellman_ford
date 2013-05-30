#include "bellman_ford.h"


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

// checks wether the given NODE is in the generated route list
static int inRoute(NODE *node, LIST_ELEMENT *route) {
    // as long as the current node isn't equal to the node we're seeking
    while (route->self != node) {
        route = ((LIST_ELEMENT*) route)->nextElement;
        if (route == NULL)
            return 0;
    }
    return 1;
}

// free all the allocated resources used by traceRoute
void freeRoute(LIST_ELEMENT* route) {
    LIST_ELEMENT* tmp = route;
    while (route->nextElement) {
        tmp = route;
        route = route->nextElement;
        free(tmp);
    }
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
            /* Check for turning: if previous dir != dir, we're turning and as 
             * turning takes longer than going in a straigh line, add a penalty
             */
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
            if ((inRoute(graph.nodes[i + j * WIDTH], rt)) || (i == strtX && j == strtY)) {
                printf("*");
            }
            else
                printf(" ");
            printf("%.2d  ", GRID_CELL(i, j)); 

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
