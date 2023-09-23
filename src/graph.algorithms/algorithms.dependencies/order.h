#ifndef ORDER_H
#define ORDER_H


#include "../../../src/graph.h"


void order_natural(i32 V, i32* order);
void order_random(i32 V, u64 seed, i32* order);
void order_descending_degrees(graph_t g, i32* order);


#endif
