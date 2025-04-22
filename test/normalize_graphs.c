#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <dirent.h>
#include <string.h>

#include "../src/primitives.h"
#include "../test/utils.h"


void normalize_edge_lines(char** lines, i32 nlines) {
    assert(lines);
    assert(nlines > 1);

    for(i32 i = 0; i < nlines; i++) {
        i32 v, w;
        char TEMPLATE[] = "e " u32_SCN " " u32_SCN "\n";
        i32 nassignments = sscanf(lines[i], TEMPLATE, &v, &w);
        if(nassignments == 2 && v > w) {
            char TEMPLATE2[] = "e " u32_PRI " " u32_PRI "\n";
            sprintf(lines[i], TEMPLATE2, w, v);
        }
    }
}

i32 deduplicate_sorted_lines(char** lines, i32 nlines) {
    assert(lines);
    assert(nlines > 0);

    i32 uniques_index = 0;
    for(i32 i = 1; i < nlines; i++) {
        i32 cmp = strcmp(lines[uniques_index], lines[i]);

        if(cmp != 0) lines[++uniques_index] = lines[i];
        if(cmp == 0) lines[--nlines]        = lines[i];
    }

    for(i32 i = 1; i < uniques_index + 1; i++)
        assert(strcmp(lines[i-1], lines[i]) != 0);

    return uniques_index + 1;
}

void count_line_categories(
        char** lines, i32 nlines,
        i32* ptr_ncomments, i32* ptr_nproblems, i32* ptr_nedges) {

    assert(lines);
    for(i32 i = 0; i < nlines; i++)
        assert(lines[i]);

    assert(ptr_ncomments);
    assert(ptr_nproblems);
    assert(ptr_nedges);

    i32 ncomments = 0;
    i32 nproblems = 0;
    i32 nedges    = 0;

    for(i32 i = 0; i < nlines; i++) {
        char EDGE_FORMAT[]    = "e "      u32_SCN " " u32_SCN "\n";
        char PROBLEM_FORMAT[] = "p edge " u32_SCN " " u32_SCN "\n";

        i32 foo1, foo2;
        char* line = lines[i];

        i32 is_comment = (line[0] == 'c');
        i32 is_problem = (sscanf(line, PROBLEM_FORMAT, &foo1, &foo2) == 2);
        i32 is_edge    = (sscanf(line, EDGE_FORMAT,    &foo1, &foo2) == 2);

        if(is_comment) ncomments++;
        if(is_problem) nproblems++;
        if(is_edge)    nedges++;
    }

    *ptr_ncomments = ncomments;
    *ptr_nproblems = nproblems;
    *ptr_nedges    = nedges;
}

void assert_lines_order(
        char** lines, i32 nlines,
        i32 ncomments, i32 nproblems, i32 nedges) {

    i32 foo1, foo2;
    char PROBLEM_FORMAT[] = "p edge " u32_SCN " " u32_SCN "\n";
    char EDGE_FORMAT[]    = "e "      u32_SCN " " u32_SCN "\n";

    for(i32 i = 0; i < ncomments; i++)
        assert(lines[i][0] == 'c');
    for(i32 i = ncomments; i < ncomments + nproblems; i++)
        assert(sscanf(lines[i], PROBLEM_FORMAT, &foo1, &foo2) == 2);
    for(i32 i = ncomments + nproblems; i < nlines; i++)
        assert(sscanf(lines[i], EDGE_FORMAT,    &foo1, &foo2) == 2);
}

i32 cmp_edge_lines(const void* _line1_, const void* _line2_) {
    char* line1 = * (char**) _line1_;
    char* line2 = * (char**) _line2_;

    i32 nassignments;
    char EDGE_FORMAT[] = "e " u32_SCN " " u32_SCN "\n";

    u32 v1, w1;
    nassignments = sscanf(line1, EDGE_FORMAT, &v1, &w1);
    assert(nassignments == 2);

    u32 v2, w2;
    nassignments = sscanf(line2, EDGE_FORMAT, &v2, &w2);
    assert(nassignments == 2);

    i32 cmp;
    if(v1 != v2) cmp = (v1 > v2) - (v1 < v2);
    if(v1 == v2) cmp = (w1 > w2) - (w1 < w2);

    return cmp;
}

/* 6,553,600 lines of 'e 4294967295 4294967295\n' total 150MB.
   Since our largest file is ~100MB, this is more than enough to load it into memory. */
#define MAX_LINES 6553600
void normalize_file(FILE* in, FILE* out) {
    assert(in);
    assert(out);

    char** lines = calloc(MAX_LINES, sizeof(char*));
    i32 nlines = file_to_lines(lines, in);

    i32 ncomments, nproblems, nedges;
    count_line_categories(lines, nlines, &ncomments, &nproblems, &nedges);
    assert(ncomments + nproblems + nedges == nlines);
    assert(ncomments >= 0 && nproblems == 1 && nedges > 0);
    assert_lines_order(lines, nlines, ncomments, nproblems, nedges);

    char** edge_lines = lines + ncomments + nproblems;
    normalize_edge_lines(edge_lines, nedges);
    qsort(edge_lines, nedges, sizeof(char*), cmp_edge_lines);
    nedges = deduplicate_sorted_lines(edge_lines, nedges);

    fprintf(out, "%s", lines[ncomments]);
    for(i32 i = 0; i < nedges; i++)
        fprintf(out, "%s", edge_lines[i]);
    fflush(out);

    for(i32 i = 0; i < nlines; i++)
        free(lines[i]);
    free(lines);
}

i32 main() {
    DIR* dir = opendir("./graphs");
    struct dirent* entry;
    for(entry = readdir(dir); entry != NULL; entry = readdir(dir)) {
        if(entry->d_type != DT_REG) continue;
        char filepath[1024];

        sprintf(filepath, "./graphs/%s", entry->d_name);
        FILE* in = fopen(filepath, "r");

        sprintf(filepath, "./test/normalized_graphs/%s", entry->d_name);
        FILE* out = fopen(filepath, "w");

        normalize_file(in, out);

        fclose(in);
        fclose(out);
    }
}