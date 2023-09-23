#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../tests_run.h"
#include "../tests.helpers/graph_metadata.h"

#include "../../src/graph.h"
#include "../../src/graph.algorithms/algorithms.h"


void test_bipartite(FILE* file_in, FILE* file_out, char* graphname) {
    fprintf(file_out, graphname);
    fprintf(file_out, ":\n");

    graph_t g = graph_new(file_in);

    i32* colors = malloc(number_of_vertices(g) * sizeof(i32));

    time_t start_wall_time = time(NULL);
    i32 status = bipartite(g, colors);
    double seconds = difftime(time(NULL), start_wall_time);

    char status_str[8];
    if(status == 0) strcpy(status_str, "true");
    else            strcpy(status_str, "false");

    fprintf(file_out, TAB "is bipartite:%s\n", status_str);
    fprintf(file_out, TAB "seconds:%lf\n", seconds);
    fprintf(file_out, TAB "colors: {\n");
    for(i32 i = 0; i < number_of_vertices(g); i += 10) {
        fprintf(file_out, TABTAB);
        for(i32 j = 0; j < 10 && i + j < number_of_vertices(g); j++) {
            fprintf(file_out, "%d ", colors[i + j]);
        }
        fprintf(file_out, "\n");
    }
    fprintf(file_out, TAB "}\n\n");
    fflush(file_out);

    free(colors);
    graph_destroy(g);
}
