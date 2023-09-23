#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

#include "../types/names.h"
#include "../types/integers.h"


typedef struct GraphSt {
    i32 V;
    i32 E;
    i32 Delta;
    i32* degrees;
    i32** neighbors;
    name_t* names;
} GraphSt;

typedef GraphSt* graph_t;


graph_t graph_new(FILE* file_in);
void graph_destroy(graph_t g);
void graph_sort_by_name(graph_t g);


#define number_of_vertices(g) (g)->V 
#define number_of_edges(g)    (g)->E
#define Delta(g)              (g)->Delta
#define name(g, v)            (g)->names[v]
#define degree(g, v)          (g)->degrees[v]
#define neighbor(g, v, i)     (g)->neighbors[v][i]


#endif
