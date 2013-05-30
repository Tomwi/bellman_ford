#include "grid.h"
GRAPH graph;
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

// return the index of the edge found in graph.edges 
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
    // all nodes not on the edge of the grid have four edges
    graph.edges = malloc(sizeof(EDGE*)*EDGES_IN_GRID(WIDTH, HEIGHT));
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

// Free allocated resources used for initializing the grid
void deinitializeGrid(void) {
    int i;
    for (i = 0; i < graph.N; i++) {
        free(graph.nodes[i]);
    }
    for (i = 0; i < graph.E; i++) {

        free(graph.edges[i]);
    }
    free(graph.nodes);
    free(graph.edges);
}

// find the given node in the graph
int findNode(void* node) {
    int i;
    if (node) {
        for (i = 0; i < graph.N; i++) {
            if (graph.nodes[i] == ((NODE*) node))
                return graph.nodes[i]->no;
        }
    }
    // not found
    return -1;
}