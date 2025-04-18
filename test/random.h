#ifndef RANDOM_H
#define RANDOM_H


#include "../src/primitives.h"


void srand2(u64 seed);
u64 rand2(void);
u64 uniform(u64 a, u64 b);
void random_graph_file(i32 nvertices, i32 nedges, FILE* STREAM);
void random_edges(i32* edges, i32 nvertices, i32 nedges);


#endif
