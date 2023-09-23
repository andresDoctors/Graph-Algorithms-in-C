#ifndef GRAPH_METADATA_H
#define GRAPH_METADATA_H


#include "../../types/integers.h"


typedef struct GraphMetadata {
    i32 V;
    i32 E;
    i32 Delta;
    i32 is_bipartite;
    i32 chromatic_number;
    i32 expected_order_natural;
    i32 expected_order_walshpowell;
    char filename[32];
} GraphMetadata;


#define UNKNOWN -1
#define NUMBER_OF_GRAPHS 31


extern GraphMetadata ALL_GRAPHS[NUMBER_OF_GRAPHS];


#endif
