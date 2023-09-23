#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../tests_run.h"
#include "../tests.helpers/graph_metadata.h"

#include "../../src/graph.h"
#include "../../src/graph.algorithms/algorithms.h"
#include "../../src/graph.algorithms/algorithms.dependencies/order.h"


void analyse_Chis(i32* Chis, i32 n, FILE* file_out) {

    i32* count = calloc(2500, sizeof(i32));
    for(i32 i = 0; i < n; i++)
        count[Chis[i]]++;

    for(i32 i = 0; i < 2500; i++) if(count[i] != 0)
        fprintf(file_out, TAB "Chi == %d : %d times\n", i, count[i]);
    fprintf(file_out, "\n");
    fflush(file_out);

    i32 minimum = I32_MAX;
    for(i32 i = 0; i < 2500; i++) if(Chis[i] < minimum) {
        minimum = Chis[i];
        fprintf(file_out, TAB "local minimum: %d at try %d\n", minimum, i + 1);
    }
    fprintf(file_out, "\n");
    fflush(file_out);

    free(count);
}

void test_natural_order(graph_t g, i32* order, i32* colors, FILE* file_out) {

    order_natural(number_of_vertices(g), order);
    i32 Chi = greedy(g, order, colors);

    fprintf(file_out, TAB "natural_order:%d\n\n", Chi);
    fflush(file_out);
}

void test_random_order(graph_t g, i32* order, i32* colors, FILE* file_out) {

    i32 V = number_of_vertices(g);
    i32* Chis = malloc(3000 * sizeof(i32));

    time_t start_wall_time = time(NULL);
    clock_t start_cpu_time = clock();

    for(i32 i = 0; i < 3000; i++) {

        order_random(V, i, order);
        i32 Chi = greedy(g, order, colors);

        Chis[i] = Chi;
    }

    double wall_seconds = difftime(time(NULL), start_wall_time);
    double cpu_seconds = (double)(clock() - start_cpu_time) / CLOCKS_PER_SEC;
    fprintf(
        file_out, 
        TAB "executed 3000 random order tests in\n"
        TAB "wall-time seconds: %lf\n"
        TAB "cpu-time  seconds: %lf\n\n", wall_seconds, cpu_seconds);
    fflush(file_out);

    analyse_Chis(Chis, 3000, file_out);

    free(Chis);
}

void test_greedy(FILE* file_in, FILE* file_out, char* graph_name) {
    fprintf(file_out, graph_name);
    fprintf(file_out, ":\n");
    fflush(file_out);

    graph_t g = graph_new(file_in);

    i32* colors = malloc(number_of_vertices(g) * sizeof(i32));
    i32* order  = malloc(number_of_vertices(g) * sizeof(i32));

    test_natural_order(g, order, colors, file_out);
    test_random_order(g, order, colors, file_out);

    fprintf(file_out, "Done!\n\n");
    fflush(file_out);

    free(order);
    free(colors);
    graph_destroy(g);
}
