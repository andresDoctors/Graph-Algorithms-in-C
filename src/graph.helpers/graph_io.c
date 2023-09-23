#include <stdio.h>
#include <stdlib.h>

#include "graph_io.h"
#include "data_structures/dict.h"


static void xfscanf(FILE* file, char* format,
                    name_address_t p_name1, name_address_t p_name2) {

    i32 k = fscanf(file, format, p_name1, p_name2);
    if(k != 2 || *p_name1 < 0 || *p_name2 < 0)
        exit(-1);
}

static Vertex* scan_vertices(FILE* file, i32 V, i32 E) {

    Vertex* vertices = calloc(V, sizeof(Vertex));
    dict_t dict = dict_new(2*V);

    for(i32 i = 0; i < E; i++) {

        name_declare_tmp(name1);
        name_declare_tmp(name2);

        xfscanf(file, "\ne %" SCNNAME " %" SCNNAME,
            name_address(name1), name_address(name2));

        i32 idx1 = dict_get_idx(dict, name1);
        i32 idx2 = dict_get_idx(dict, name2);

        vertices_add(idx1, name1, idx2, name2, vertices);
    }

    dict_destroy(dict);

    return vertices;
}

Vertex* scan_graph(FILE* file_in, i32* p_V, i32* p_E) {

    char line[1024];
    do { (void) fgets(line, 1024, file_in); }
        while(line[0] != 'p');
    sscanf(line, "p edge %" SCNi32 " %" SCNi32, p_V, p_E);

    return scan_vertices(file_in, *p_V, *p_E);
}
