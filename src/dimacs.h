#ifndef GRAPH_IO_H
#define GRAPH_IO_H


#include <stdio.h>
#include "primitives.h"


u32* dimacs_scan(FILE* STREAM, i32* ptr_nvertices, i32* ptr_nedges);


#endif
