#include "algorithms.h"
#include <string.h>
#include <stdlib.h>


static i32 color_set(graph_t g, i32* colors, i32* is_visited,
                     i32* set1, i32* set2,   i32  set1_size,  i32 c) {

    i32 set2_size = 0;
    while(set1_size > 0) {

        i32 v = set1[--set1_size];
        colors[v] = c;

        i32 degree_of_v = degree(g, v);
        for(i32 i = 0; i < degree_of_v; i++) {
            i32 w = neighbor(g, v, i);
            if(colors[w] == c) return -1;
            if(is_visited[w])  continue;

            is_visited[w] = 1;
            set2[set2_size++] = w;
        }
    }

    return set2_size;
}

i32 bipartite(graph_t g, i32* colors) {

    i32 V = number_of_vertices(g);
    if(V == 0) return 0;

    memset(colors, 0x00, V * sizeof(i32));
    i32* is_visited = calloc(V, sizeof(i32));
    i32* set1 = malloc(V * sizeof(i32));
    i32* set2 = malloc(V * sizeof(i32));
    i32 set1_size = 0;
    i32 set2_size = 0;

    for(i32 v = 0; v < V; v++) {
        if(is_visited[v]) continue;

        set1[set1_size++] = v;
        is_visited[v] = 1;

        while(set1_size > 0 || set2_size > 0) {
            set2_size = color_set(g, colors, is_visited,
                                  set1, set2, set1_size, 1);
            if(set2_size == -1) break;

            set1_size = color_set(g, colors, is_visited,
                                  set2, set1, set2_size, 2);
            if(set1_size == -1) break;
        }

        if(set1_size == -1 || set2_size == -1) break;
    }

    free(set2);
    free(set1);
    free(is_visited);

    if(set1_size == -1 || set2_size == -1) return -1;
    return 0;
}
