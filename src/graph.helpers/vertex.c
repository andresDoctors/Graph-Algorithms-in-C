#include "vertex.h"


void vertices_add(i32 idx1, name_t name1, i32 idx2, name_t name2,
                  Vertex* vertices) {

    vertices[idx1].degree++;
    push(&(vertices[idx1].neighbors), idx2);
    if(name_is_empty(vertices[idx1].name))
        vertices[idx1].name = name_copy(name1);

    vertices[idx2].degree++;
    push(&(vertices[idx2].neighbors), idx1);
    if(name_is_empty(vertices[idx2].name))
        vertices[idx2].name = name_copy(name2);
}
