#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../test/utils.h"


void edges_to_file(u32* edges, i32 nvertices, i32 nedges, FILE* STREAM) {
    assert(edges);
    assert(nvertices > 0);
    assert(nedges > 0);
    assert(STREAM);

    const char TEMPLATE1[] = "p edge " i32_SCN " " i32_SCN "\n";
    fprintf(STREAM, TEMPLATE1, nvertices, nedges);
    for (i32 i = 0; i < nedges; i++) {
        const char TEMPLATE2[] = "e " u32_PRI " " u32_PRI "\n";
        fprintf(STREAM, TEMPLATE2, edges[2*i], edges[2*i + 1]);
    }

    fflush(STREAM);
    fseek(STREAM, 0, SEEK_SET);
}

i32 file_to_lines(char** lines, FILE* file) {
    assert(lines);
    assert(file);

    i32 nlines = 0;
    ssize_t bytes_read;

    do {
        char* line = NULL;
        size_t line_size = 0;
        bytes_read = getline(&line, &line_size, file);
        if(bytes_read > 0) lines[nlines++] = line;
    } while(bytes_read > 0);

    return nlines;
}
