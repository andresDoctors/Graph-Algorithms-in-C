#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "./tests_run.h"
#include "./tests.helpers/graph_metadata.h"



char DIR_IN[16]  = "./graphs/";
char DIR_OUT[32] = "./tests/tests.results/";


void get_time_as_string(char* str_time) {
    time_t current_time = time(NULL);
    struct tm* time_info = localtime(&current_time);
    strftime(str_time, 32, "%Y-%m-%d.%H-%M-%S", time_info);
}

void run_single_tests() {

    char path[256];
    char str_time[32];

    single_test_t tests[2] = { test_gcc_rand, test_rand2, };
    char test_names[2][32] = { "gcc_rand/", "rand2/", };

    for(i32 i = 0; i < 2; i++) {

        single_test_t test = tests[i];
        get_time_as_string(str_time);

        strcpy(path, DIR_OUT);
        strcat(path, test_names[i]);
        strcat(path, str_time);

        FILE* file_out = fopen(path, "w");
        test(file_out);
        fclose(file_out);
    }
}

void run_multiple_tests_single_output() {

    char path[256];
    char str_time[32];

    multiple_test_t tests[3] = {test_greedy, test_welsh_powell, test_bipartite};
    char test_names[3][32] = {"greedy/", "welsh_powell/", "bipartite/"};

    for(i32 i = 0; i < 3; i++) {

        multiple_test_t test = tests[i];
        get_time_as_string(str_time);

        strcpy(path, DIR_OUT);
        strcat(path, test_names[i]);
        strcat(path, str_time);

        FILE* file_out = fopen(path, "w");
        for(i32 j = 0; j < NUMBER_OF_GRAPHS; j++) {
            strcpy(path, DIR_IN);
            strcat(path, ALL_GRAPHS[j].filename);

            FILE* file_in = fopen(path, "r");
            test(file_in, file_out, ALL_GRAPHS[j].filename);
            fclose(file_in);
        }

        fclose(file_out);
    }
}


void run_multiple_tests_multiple_outputs() {
}

int main(void) {
    run_single_tests();
    run_multiple_tests_single_output();
    run_multiple_tests_multiple_outputs();
    return 0;
}
