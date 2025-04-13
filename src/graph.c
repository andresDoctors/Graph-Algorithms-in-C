#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "graph.helpers/graph_io.h"


static graph_t graph_malloc(i32 nvertices) {
    assert(nvertices > 0);

    graph_t new_graph    = malloc(sizeof(GraphSt));
    new_graph->degrees   = malloc(nvertices * sizeof(i32));
    new_graph->neighbors = malloc(nvertices * sizeof(i32*));
    new_graph->names     = malloc(nvertices * sizeof(name_t));

    return new_graph;
}

int cmp_i32(const void* _a_, const void* _b_) {
    i32 a = * (i32*) _a_;
    i32 b = * (i32*) _b_;
    return (a > b) - (a < b);
}

static i32 uniques_from_sorted(i32* dst, const i32* SRC, i32 n) {
    assert(dst);
    assert(SRC);
    assert(n > 0);
    for(i32 i = 0; i < n - 1; i++)
        assert(SRC[i] <= SRC[i+1]);

    i32 dst_size = 0;
    dst[dst_size++] = SRC[0];
    for(i32 i = 1; i < n; i++) {
        if(SRC[i] != SRC[i-1]) {
            dst[dst_size++] = SRC[i];
        }
    }

    return dst_size;
}

static void graph_populate_names(graph_t g, i32* edges) {
    assert(g);
    assert(g->names);
    assert(g->nedges > 0);
    assert(g->nvertices > 0);
    assert(edges);

    i32* non_unique_names = malloc(2*g->nedges*sizeof(i32));
    memcpy(non_unique_names, edges, 2*g->nedges*sizeof(i32));
    qsort(non_unique_names, 2*g->nedges, sizeof(i32), cmp_i32);
    i32 nnames = uniques_from_sorted(g->names, non_unique_names, 2*g->nedges);

    free(non_unique_names);
    assert(nnames == g->nvertices);    
}

static i32 vertex(graph_t g, i32 name) {
    assert(g);
    assert(g->names);
    assert(g->nvertices > 0);

    i32* ptr = bsearch(&name, g->names, g->nvertices, sizeof(i32), cmp_i32);
    return (ptr == NULL) ? -1 : *ptr;
}

static void graph_populate_degrees(graph_t g, i32* edges) {
    assert(g);
    assert(g->degrees);
    assert(g->nedges > 0);
    assert(g->nvertices > 0);
    assert(edges);

    memset(g->degrees, 0x00, g->nvertices*sizeof(i32));
    for(i32 i = 0; i < 2*g->nedges; i++) {
        i32 name = edges[i];
        i32 v = vertex(g, name);
        g->degrees[v]++;
    }
}

static i32 maximum_i32(i32* arr, i32 n) {
    assert(arr);
    assert(n > 0);

    i32 max = arr[0];
    for(i32 i = 1; i < n; i++) {
        if(arr[i] > max) {
            max = arr[i];
        }
    }

    return max;
}

static void graph_populate_neighbors(graph_t g, i32* edges) {
    assert(g);
    assert(g->degrees);
    assert(g->neighbors);
    assert(g->nvertices > 0);
    assert(g->nedges > 0);
    assert(edges);

    for(i32 v = 0; v < g->nvertices; v++)
        g->neighbors[v] = malloc(g->degrees[v]*sizeof(i32));

    i32* nneighbors = malloc(g->nvertices*sizeof(i32));
    memset(nneighbors, 0x00, g->nvertices*sizeof(i32));

    for(i32 i = 0; i < g->nedges; i++) {
        i32 name1 = edges[2*i];
        i32 name2 = edges[2*i + 1];

        i32 v1 = vertex(g, name1);
        i32 v2 = vertex(g, name2);

        neighbor(g, v1, nneighbors[v1]++) = v2;
        neighbor(g, v2, nneighbors[v2]++) = v1;
    }

    for (i32 i = 0; i < g->nvertices; i++)
        assert(nneighbors[i] == g->degrees[i]);
    free(nneighbors);
}

graph_t graph_new(FILE* STREAM) {
    i32 nvertices, nedges;
    i32* edges = scan_graph(STREAM, &nvertices, &nedges);

    graph_t g = graph_malloc(nvertices);
    g->nvertices = nvertices;
    g->nedges = nedges;
    graph_populate_names(g, edges);
    graph_populate_degrees(g, edges);
    graph_populate_neighbors(g, edges);
    g->Delta = maximum_i32(g->degrees, nvertices);

    free(edges);
    return g;
}

void graph_destroy(graph_t g) {
    for(i32 v = 0; v < g->nvertices; v++)
        free(g->neighbors[v]);
    free(g->neighbors);
    free(g->degrees);
    free(g->names);
    free(g);
}
