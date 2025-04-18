#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../test/utils.h"


void edges_to_file(i32* edges, i32 nvertices, i32 nedges, FILE* STREAM) {
    assert(edges);
    assert(nvertices > 0);
    assert(nedges > 0);
    assert(STREAM);

    const char TEMPLATE1[] = "p edge " i32_SCN " " i32_SCN "\n";
    fprintf(STREAM, TEMPLATE1, nvertices, nedges);
    for (i32 i = 0; i < nedges; i++) {
        const char TEMPLATE2[] = "e " i32_PRI " " i32_PRI "\n";
        fprintf(STREAM, TEMPLATE2, edges[2*i], edges[2*i + 1]);
    }

    fflush(STREAM);
    fseek(STREAM, 0, SEEK_SET);
}

i32 file_to_lines(char** lines, FILE* file) {
    assert(lines);
    assert(file);

    i32 nlines = 0;
    size_t bytes_read;

    do {
        char* line = NULL;
        size_t line_size = 0;
        bytes_read = getline(&line, &line_size, file);
        if(bytes_read > 0) lines[nlines++] = line;
    } while(bytes_read > 0);

    return nlines;
}

void normalize_edge_lines(char** lines, i32 nlines) {
    assert(lines);
    assert(nlines > 1);
    
    for(i32 i = 0; i < nlines; i++) {
        i32 v, w;
        char TEMPLATE[] = "e " i32_SCN " " i32_SCN "\n";
        i32 nassignments = sscanf(lines[i], TEMPLATE, &v, &w);
        if(nassignments == 2 && v > w)
            sprintf(lines[i], TEMPLATE, w, v);
    }
}

i32 deduplicate_sorted_lines(char** lines, i32 nlines) {
    assert(lines);
    assert(nlines > 1);
    for(i32 i = 1; i < nlines; i++)
        assert(strcmp(lines[i - 1], lines[i]) <= 0);

    i32 uniques_index = 0;
    for(i32 i = 1; i < nlines; i++) {
        i32 cmp = strcmp(lines[uniques_index], lines[i]);

        if(cmp <  0) lines[++uniques_index] = lines[i];
        if(cmp == 0) lines[--nlines]        = lines[i];
    }

    for(i32 i = 1; i < uniques_index + 1; i++)
        assert(strcmp(lines[i-1], lines[i]) < 0);

    return uniques_index + 1;
}

i32 _strcmp_(const void* _line1_, const void* _line2_) {
    char* line1 = * (char**) _line1_;
    char* line2 = * (char**) _line2_;

    return strcmp(line1, line2);
}

/* 62,500 lines of 'e 4294967295 4294967295\n' total 150MB.
   Since our largest file is ~100MB, this is more than enough to load it into memory. */
#define MAX_LINES 65536
i32 file_cmp(FILE* file1, FILE* file2) {
    assert(file1);
    assert(file2);

    char* lines1[MAX_LINES];
    char* lines2[MAX_LINES];

    i32 nlines1 = file_to_lines(lines1, file1);
    i32 nlines2 = file_to_lines(lines2, file2);

    qsort(lines1, nlines1, sizeof(char*), _strcmp_);
    qsort(lines2, nlines2, sizeof(char*), _strcmp_);

    i32 i;
    for(i = 0; i < nlines1 && i < nlines2; i++)
        if(strcmp(lines1[i], lines2[i]) != 0) break;

    return strcmp(lines1[i], lines2[i]);
}