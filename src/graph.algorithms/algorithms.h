#ifndef ALGORITHMS_H
#define ALGORITHMS_H


#include "../graph.h"


i32 greedy(graph_t g, i32* order, i32* colors);
void order_natural(i32 V, i32* order);
void order_random(i32 V, u64 seed, i32* order);
void order_descending_degrees(graph_t g, i32* order);

i32 bipartite(graph_t g, i32* colors);


#endif
