#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "primitives.h"


static void ignore_comment_lines(FILE* STREAM) {
    assert(STREAM);
    char line[1024];

    do {
        char* error1 = fgets(line, sizeof(line), STREAM);
        assert(!error1);
    } while(line[0] == 'c');
    
    i32 error2 = fseek(STREAM, -strlen(line), SEEK_CUR);

    assert(!error2);
    assert(line[0] == 'p');
}

static void scan_order_and_size(FILE* STREAM, i32* ptr_nvertices, i32* ptr_nedges) {
    assert(STREAM);
    assert(ptr_nvertices);
    assert(ptr_nedges);

    const char TEMPLATE[] = "p " i32_SCN " " i32_SCN;
    i32 nassignments = fscanf(STREAM, TEMPLATE, ptr_nvertices, ptr_nedges);

    assert(nassignments == 2);
}

static void scan_edges(FILE* STREAM, i32* edges, i32 nedges) {
    assert(STREAM);
    assert(edges);
    assert(nedges > 0);

    for(i32 i = 0; i < nedges; i++) {
        i32 name1, name2, nassignments;
        const char TEMPLATE[] = "e " i32_SCN " " i32_SCN;

        nassignments = fscanf(STREAM, TEMPLATE, &name1, &name2);
        assert(nassignments == 2);

        edges[2*i]     = name1;
        edges[2*i + 1] = name2;
    }
}

static void sort_edges(i32* edges, i32 nedges) {
    assert(edges);
    assert(nedges > 0);

    int edge_cmp(const void* _EDGE1_, const void * _EDGE2_) {
        i32* EDGE1 = (i32*) _EDGE1_;
        i32* EDGE2 = (i32*) _EDGE2_;

        i32 v1 = EDGE1[0], v2 = EDGE2[0];
        if(v1 == v2) {
            v1 = EDGE1[1], v2 = EDGE2[1];
        }
    
        return (v1 > v2) - (v1 < v2);
    }

    qsort(edges, nedges, 2*sizeof(i32), edge_cmp);
}

i32* scan_graph(FILE* STREAM, i32* ptr_nvertices, i32* ptr_nedges) {
    assert(STREAM);
    assert(ptr_nvertices);
    assert(ptr_nedges);

    ignore_comment_lines(STREAM);
    
    i32 nvertices, nedges;
    scan_order_and_size(STREAM, &nvertices, &nedges);

    i32* edges = malloc(2*nedges*sizeof(i32));
    assert(edges);

    scan_edges(STREAM, edges, nedges);
    sort_edges(edges, nedges);

    *ptr_nvertices = nvertices;
    *ptr_nedges = nedges;
    return edges;
}
