#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../tests_run.h"
#include "../tests.helpers/graph_metadata.h"

#include "../../src/graph.h"
#include "../../src/graph.algorithms/algorithms.h"
#include "../../src/graph.algorithms/algorithms.dependencies/order.h"


void test_welsh_powell(FILE* file_in, FILE* file_out, char* graph_name) {
    fprintf(file_out, graph_name);
    fprintf(file_out, ":\n");

    graph_t g = graph_new(file_in);
    i32 V = number_of_vertices(g);
    i32* colors = malloc(V * sizeof(i32));
    i32* order  = malloc(V * sizeof(i32));

    order_descending_degrees(g, order);

    i32 b = 1;
    for(i32 i = 0; i < V - 1; i++) {
        i32 v = order[i];
        i32 w = order[i+1];

        b = b && (degree(g, v) >= degree(g, w));
    }

    time_t start_wall_time = time(NULL);
    i32 Chi = greedy(g, order, colors);
    double seconds = difftime(time(NULL), start_wall_time);

    fprintf(file_out, TAB "order_is_ok:%d\n", b);
    fprintf(file_out, TAB "wlsh_powell:%d\n", Chi);
    fprintf(file_out, TAB "seconds:%lf\n", seconds);
    fflush(file_out);

    free(order);
    free(colors);
    graph_destroy(g);
}
