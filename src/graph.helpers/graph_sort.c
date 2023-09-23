#include "../graph.h"
#include <stdlib.h>

graph_t g_compared_graph;

int vertex_cmp(const void* p_v1, const void* p_v2) {
    i32 v1 = * (i32*) p_v1;
    i32 v2 = * (i32*) p_v2;

    return name_cmp(name(g_compared_graph, v1), name(g_compared_graph, v2));
}

void graph_sort_by_name(graph_t g) {

    i32 V = number_of_vertices(g);
    i32* vertices = malloc(V * sizeof(i32));
    for(i32 i = 0; i < V; i++) vertices[i] = i;
    g_compared_graph = g;
    qsort(vertices, V, sizeof(i32), vertex_cmp);

    for(i32 v = 0; v < V; v++) {

        name_t tmp = name(g, v);
        name(g, v) = name(g, vertices[v]);
        name(g, vertices[v]) = tmp;

        i32 degree_of_v = degree(g, v);
        for(i32 i = 0; i < degree_of_v; i++)
            neighbor(g, v, i) = vertices[neighbor(g, v, i)];
    }

    free(vertices);
}
