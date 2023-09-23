#include <stdlib.h>
#include <string.h>

#include "algorithms.h"


i32 greedy(graph_t g, i32* order, i32* colors) {

    i32 Chi_plus_one = 1;
    i32 V = number_of_vertices(g);
    i32* marked_colors = calloc(Delta(g) + 2, sizeof(i32));
    memset(colors, 0x00, V * sizeof(i32));

    for(i32 i = 0; i < V; i++) {
        i32 v = order[i];
        i32 degree_of_v = degree(g, v);

        for(i32 j = 0; j < degree_of_v; j++) {
            i32 w = neighbor(g, v, j);
            marked_colors[colors[w]] = i + 1;
        }

        i32 color_of_v;
        for(color_of_v = 1; marked_colors[color_of_v] == i + 1; color_of_v++);

        colors[v] = color_of_v;
        Chi_plus_one += (color_of_v == Chi_plus_one);
    }

    free(marked_colors);
    return Chi_plus_one - 1;
}
