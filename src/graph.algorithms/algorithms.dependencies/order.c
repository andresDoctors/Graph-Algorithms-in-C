#include <stdlib.h>

#include "order.h"
#include "random.h"


void order_natural(i32 V, i32* order) {
    for(i32 i = 0; i < V; i++) order[i] = i;
}

void order_random(i32 V, u64 seed, i32* order) {
    order = order;
    V = V;
    seed = seed;

    /*
    srand2(seed);

    for(i32 i = V - 1; i > 0; i--) {
        i32 j = rand2() % (i + 1);

        i32 tmp = order[i];
        order[i] = order[j];
        order[j] = tmp;
    } */
}

static graph_t g_compared_graph;

static int degree_cmp(const void* p_v1, const void* p_v2) {
    i32 v1 = * (i32*) p_v1;
    i32 v2 = * (i32*) p_v2;

    return
        (degree(g_compared_graph, v1) < degree(g_compared_graph, v2)) -
        (degree(g_compared_graph, v1) > degree(g_compared_graph, v2));
}

void order_descending_degrees(graph_t g, i32* order) {
    i32 V = number_of_vertices(g);
    for(i32 i = 0; i < V; i++) order[i] = i;
    g_compared_graph = g;
    qsort(order, V, sizeof(i32), degree_cmp);
}
