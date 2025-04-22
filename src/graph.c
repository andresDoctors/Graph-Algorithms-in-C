#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "graph.h"


typedef enum graph_status_t {
    GRAPH_IS_OK = 0,

    GRAPH_IS_NULL,
    NEGATIVE_VERTEX_COUNT,
    NEGATIVE_EDGE_COUNT,
    NEGATIVE_MAX_DEGREE,
    NEGATIVE_VERTEX_DEGREE,
    NEIGHBOR_OUT_OF_BOUNDS,
    MAX_DEGREE_MISMATCH,
    MISSING_RECIPROCAL_EDGE,
    SELF_LOOP,
} graph_status_t;


static i32 i32_maximum(i32* arr, i32 n) {
    assert(arr);
    assert(n > 0);

    i32 max = arr[0];
    for(i32 i = 1; i < n; i++)
        if(arr[i] > max) max = arr[i];

    return max;
}

static i32 u32_cmp(const void* _a_, const void* _b_) {
    u32 a = * (u32*) _a_;
    u32 b = * (u32*) _b_;
    return (a > b) - (a < b);
}

static i32 u32_deduplicated(u32* dst, const u32* SRC, i32 n) {
    assert(dst);
    assert(SRC);
    assert(n > 0);
    for(i32 i = 0; i < n - 1; i++)
        assert(SRC[i] <= SRC[i+1]);

    dst[0] = SRC[0];
    i32 dst_size = 1;

    for(i32 i = 1; i < n; i++) {
        if(SRC[i-1] != SRC[i]) {
            dst[dst_size++] = SRC[i];
        }
    }

    return dst_size;
}

static i32 edges_cmp(const void* _edge1_, const void* _edge2_) {
    u32* edge1 = (u32*) _edge1_;
    u32* edge2 = (u32*) _edge2_;

    u32 v1 = edge1[0];
    u32 v2 = edge2[0];
    if(v1 == v2) {
        v1 = edge1[1];
        v2 = edge2[1];
    }

    return (v1 > v2) - (v1 < v2);
}

static i32 edges_filtered_reflexives(u32* dst, u32* SRC, i32 n) {
    assert(dst);
    assert(SRC);
    assert(n > 0);

    i32 dst_size = 0;
    for(i32 i = 0; i < n; i++) { 
        if(SRC[2*i] != SRC[2*i + 1]) {
            dst[2*dst_size]     = SRC[2*i];
            dst[2*dst_size + 1] = SRC[2*i + 1];
            dst_size++;
        }
    }

    for(i32 i = 0; i < n; i++)
        assert(dst[2*i] != dst[2*i + 1]);

    return dst_size;
}


static i32 edges_deduplicated(u32* dst, u32* SRC, i32 n) {
    assert(dst);
    assert(SRC);
    assert(n > 0);
    for(i32 i = 0; i < n - 1; i++) {
        i32 cmp = edges_cmp(&SRC[2*i], &SRC[2*i + 2]);
        assert(cmp <= 0);
    }

    dst[2*0]     = SRC[2*0];
    dst[2*0 + 1] = SRC[2*0 + 1];
    i32 dst_size = 1;

    for(i32 i = 1; i < n; i++) {
        i32 cmp = edges_cmp(&SRC[2*i - 2], &SRC[2*i]);
        if(cmp != 0) {
            dst[2*dst_size]     = SRC[2*i];
            dst[2*dst_size + 1] = SRC[2*i + 1];
            dst_size++;
        }
    }

    return dst_size;
}

static i32 edges_normalized(u32* dst, u32* SRC, i32 n) {
    assert(dst);
    assert(SRC);
    assert(n > 0);

    i32 dst_size;
    dst_size = edges_filtered_reflexives(dst, SRC, n);
    qsort(dst, dst_size, 2*sizeof(u32), edges_cmp);
    dst_size = edges_deduplicated(dst, dst, dst_size);

    return dst_size;
}

static graph_t graph_malloc(i32 nvertices) {
    assert(nvertices > 0);

    graph_t new_graph    = malloc(sizeof(GraphSt));
    new_graph->degrees   = malloc(nvertices*sizeof(i32));
    new_graph->neighbors = malloc(nvertices*sizeof(i32*));
    new_graph->names     = malloc(nvertices*sizeof(u32));

    return new_graph;
}

static void graph_populate_names(graph_t g, u32* edges) {
    assert(g);
    assert(g->names);
    assert(g->nedges > 0);
    assert(g->nvertices > 0);
    assert(edges);

    u32* non_unique_names = malloc(2*g->nedges*sizeof(u32));
    memcpy(non_unique_names, edges, 2*g->nedges*sizeof(u32));
    qsort(non_unique_names, 2*g->nedges, sizeof(u32), u32_cmp);
    i32 nnames = u32_deduplicated(g->names, non_unique_names, 2*g->nedges);

    free(non_unique_names);
    assert(nnames == g->nvertices);
}

static i32 vertex(graph_t g, u32 name) {
    assert(g);
    assert(g->names);
    assert(g->nvertices > 0);

    u32* ptr = bsearch(&name, g->names, g->nvertices, sizeof(u32), u32_cmp);
    assert(ptr != NULL);

    i32 v = (i32) (ptr - g->names);
    assert(0 <= v && v < g->nvertices);

    return v;
}

static void graph_populate_degrees(graph_t g, u32* edges) {
    assert(g);
    assert(g->degrees);
    assert(g->nedges > 0);
    assert(g->nvertices > 0);
    assert(edges);

    memset(g->degrees, 0x00, g->nvertices*sizeof(i32));
    for(i32 i = 0; i < 2*g->nedges; i++) {
        u32 name = edges[i];
        i32 v = vertex(g, name);
        g->degrees[v]++;
    }
}

static void graph_populate_neighbors(graph_t g, u32* edges) {
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
        u32 name1 = edges[2*i];
        u32 name2 = edges[2*i + 1];

        i32 v1 = vertex(g, name1);
        i32 v2 = vertex(g, name2);

        neighbor(g, v1, nneighbors[v1]++) = v2;
        neighbor(g, v2, nneighbors[v2]++) = v1;
    }

    for (i32 i = 0; i < g->nvertices; i++)
        assert(nneighbors[i] == g->degrees[i]);
    free(nneighbors);
}

static graph_status_t graph_consistency_check(graph_t g) {
    if(g == NULL) return GRAPH_IS_NULL;

    if(nvertices(g) < 0) return NEGATIVE_VERTEX_COUNT;
    if(nedges(g)    < 0) return NEGATIVE_EDGE_COUNT;
    if(delta(g)     < 0) return NEGATIVE_MAX_DEGREE;

    for(i32 v = 0; v < nvertices(g); v++)
        if(degree(g, v) < 0) return NEGATIVE_VERTEX_DEGREE;

    for(i32 v = 0; v < nvertices(g); v++) {
        for(i32 i = 0; i < degree(g, v); i++) {
            i32 w = neighbor(g, v, i);
            if(w < 0 || w >= nvertices(g)) return NEIGHBOR_OUT_OF_BOUNDS;
        }
    }

    i32 max_degree = i32_maximum(g->degrees, nvertices(g));
    if(delta(g) != max_degree) return MAX_DEGREE_MISMATCH;

    for(i32 v = 0; v < nvertices(g); v++) {
        for(i32 i = 0; i < degree(g, v); i++) {
            i32 w = neighbor(g, v, i);

            i32 b = 0;
            for(i32 j = 0; j < degree(g, w); j++)
                b = b || (neighbor(g, w, j) == v);

            if(!b) return MISSING_RECIPROCAL_EDGE;
        }
    }

    for(i32 v = 0; v < nvertices(g); v++) {
        for(i32 i = 0; i < degree(g, v); i++) {
            i32 w = neighbor(g, v, i);
            if(v == w) return SELF_LOOP;
        }
    }

    return GRAPH_IS_OK;
}

graph_t graph_new(u32* edges, i32 nvertices, i32 nedges) {
    nedges = edges_normalized(edges, edges, nedges);

    graph_t g = graph_malloc(nvertices);
    g->nvertices = nvertices;
    g->nedges = nedges;
    graph_populate_names(g, edges);
    graph_populate_degrees(g, edges);
    graph_populate_neighbors(g, edges);
    g->Delta = i32_maximum(g->degrees, nvertices);

    assert(graph_consistency_check(g) == GRAPH_IS_OK);
    return g;
}

void graph_destroy(graph_t g) {
    assert(graph_consistency_check(g) == GRAPH_IS_OK);

    for(i32 v = 0; v < g->nvertices; v++)
        free(g->neighbors[v]);
    free(g->neighbors);
    free(g->degrees);
    free(g->names);
    free(g);
}

i32 graph_to_edges(u32* dst, graph_t g) {
    assert(dst);
    assert(graph_consistency_check(g) == GRAPH_IS_OK);

    for(i32 v = 0; v < g->nvertices - 1; v++)
        assert(g->names[v] < g->names[v + 1]);

    i32 dst_size = 0;
    for(i32 v = 0; v < g->nvertices; v++) {
        u32 name1 = g->names[v];

        for (i32 i = 0; i < g->degrees[v]; i++) {
            i32 w = g->neighbors[v][i];
            u32 name2 = g->names[w];

            if (name1 < name2) {
                dst[2*dst_size]     = name1;
                dst[2*dst_size + 1] = name2;
                dst_size++;
            }
        }
    }

    qsort(dst, dst_size, 2*sizeof(u32), edges_cmp);

    for(i32 i = 0; i < dst_size - 1; i++) {
        i32 cmp = edges_cmp(&dst[2*i], &dst[2*i + 2]);
        assert(cmp < 0);
    }

    return dst_size;
}