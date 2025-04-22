#include <stdio.h>
#include "../src/primitives.h"


void edges_to_file(u32* edges, i32 nvertices, i32 nedges, FILE* STREAM);
void normalize_file(FILE* in, FILE* out);
i32 file_to_lines(char** lines, FILE* file);
