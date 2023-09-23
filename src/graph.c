#include <stdlib.h>

#include "graph.h"
#include "graph.helpers/vertex.h"
#include "graph.helpers/graph_io.h"


static graph_t graph_malloc(i32 V) {

    graph_t new_graph    = malloc(sizeof(GraphSt));
    new_graph->degrees   = malloc(V * sizeof(i32));
    new_graph->neighbors = malloc(V * sizeof(i32*));
    new_graph->names     = malloc(V * sizeof(name_t));

    return new_graph;
}

static graph_t graph_from_vertices(Vertex* vertices, i32 V, i32 E) {
    if(V == 0) return NULL;

    i32 Delta = -1;
    graph_t new_graph = graph_malloc(V);
    i32* all_neighbors = malloc((2*E) * sizeof(i32));

    for(i32 v = 0; v < V; v++) {
        Vertex vertex = vertices[v];

        if(vertex.degree > Delta)
            Delta = vertex.degree;

        name(new_graph, v)   = vertex.name;
        degree(new_graph, v) = vertex.degree;

        new_graph->neighbors[v] = all_neighbors;
        for(i32 i = 0; i < vertex.degree; i++)
            *all_neighbors++ = pop(&(vertex.neighbors));
    }

    new_graph->V = V;
    new_graph->E = E;
    new_graph->Delta = Delta;

    return new_graph;
}

graph_t graph_new(FILE* file_in) {
    int V, E;
    Vertex* vertices = scan_graph(file_in, &V, &E);
    return graph_from_vertices(vertices, V, E);
}

void graph_destroy(graph_t g) {
    i32 V = g->V;

    free(g->neighbors[0]);
    for(i32 v = 0; v < V; v++) { 
        //free(g->neighbors[v]);
        name_destroy(g->names[v]);
    }

    free(g->names);
    free(g->degrees);
    free(g->neighbors);
    free(g);
}
