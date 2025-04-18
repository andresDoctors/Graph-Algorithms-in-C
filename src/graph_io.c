#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "primitives.h"


static void ignore_comment_lines(FILE* STREAM) {
    assert(STREAM);
    char line[1024];

    do {
        char* error1 = fgets(line, sizeof(line), STREAM);
        assert(error1);
    } while(line[0] == 'c');
    
    i32 error2 = fseek(STREAM, -strlen(line), SEEK_CUR);

    assert(!error2);
    assert(line[0] == 'p');
}

static void scan_order_and_size(FILE* STREAM, i32* ptr_nvertices, i32* ptr_nedges) {
    assert(STREAM);
    assert(ptr_nvertices);
    assert(ptr_nedges);

    const char TEMPLATE[] = "p edge " i32_SCN " " i32_SCN;
    i32 nassignments = fscanf(STREAM, TEMPLATE, ptr_nvertices, ptr_nedges);

    assert(nassignments == 2);
}

static i32 cmp_edges(const void* _edge1_, const void* _edge2_) {
    i32* edge1 = (i32*) _edge1_;
    i32* edge2 = (i32*) _edge2_;

    i32 v1 = edge1[0];
    i32 v2 = edge2[0];
    if(v1 == v2) {
        v1 = edge1[1];
        v2 = edge2[1];
    }

    return (v1 > v2) - (v1 < v2);
}

static void scan_edges(FILE* STREAM, i32* edges, i32 nedges) {
    assert(STREAM);
    assert(edges);
    assert(nedges > 0);

    for(i32 i = 0; i < nedges; i++) {
        i32 name1, name2, nassignments;
        const char TEMPLATE[] = "\ne " i32_SCN " " i32_SCN;

        nassignments = fscanf(STREAM, TEMPLATE, &name1, &name2);
        assert(nassignments == 2);

        edges[2*i]     = name1;
        edges[2*i + 1] = name2;
    }

    qsort(edges, nedges, 2*sizeof(i32), cmp_edges);
    for(i32 i = 0; i < nedges - 1; i++) {
        assert(
            edges[2*i]     != edges[2*i + 2] ||
            edges[2*i + 1] != edges[2*i + 3]
        );
    }
}

i32* scan_graph(FILE* STREAM, i32* ptr_nvertices, i32* ptr_nedges) {
    assert(STREAM);
    assert(ptr_nvertices);
    assert(ptr_nedges);

    i32 nvertices, nedges;
    ignore_comment_lines(STREAM);
    scan_order_and_size(STREAM, &nvertices, &nedges);

    i32* edges = malloc(2*nedges*sizeof(i32));
    scan_edges(STREAM, edges, nedges);

    *ptr_nvertices = nvertices;
    *ptr_nedges = nedges;

    assert(edges);
    assert(nvertices > 0);
    assert(nedges > 0);
    return edges;
}
