#include <stdio.h>
#include <stdlib.h>

#include "src/graph.algorithms/algorithms.h"
#include "src/graph.h"

int main(void) {
    graph_t g = graph_new(stdin);
    i32* colors = malloc(g->nvertices*sizeof(i32));
    i32* order = malloc(g->nvertices*sizeof(i32));
    for(i32 i = 0; i < g->nvertices; i++)
        order[i] = i;

    i32 chi = greedy(g, order, colors);
    printf("chi:%d\n", chi);
}
