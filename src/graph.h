#ifndef GRAPH_H
#define GRAPH_H


#include <stdio.h>
#include "primitives.h"


typedef struct GraphSt {
    i32 nvertices;
    i32 nedges;
    i32 Delta;
    i32* degrees;
    i32** neighbors;
    i32* names;
} GraphSt;

typedef GraphSt* graph_t;


graph_t graph_new(FILE* STREAM);
void graph_destroy(graph_t g);


#define name(g, v)        (g)->names[v]
#define degree(g, v)      (g)->degrees[v]
#define neighbor(g, v, i) (g)->neighbors[v][i]


#endif
