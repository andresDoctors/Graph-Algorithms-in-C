#ifndef VERTEX_H
#define VERTEX_H


#include "../../types/names.h"
#include "data_structures/stack.h"


typedef struct Vertex {
    name_t name;
    i32 degree;
    stack_t neighbors;
} Vertex;


void
vertices_add(i32 idx1, name_t name1, i32 idx2, name_t name2, Vertex* vertices);


#endif
