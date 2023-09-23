#ifndef TESTS_H
#define TESTS_H


#include <stdio.h>

#include "../types/integers.h"


#define TAB    "    "
#define TABTAB "    " "    "


typedef void (*single_test_t)(FILE*);
typedef void (*multiple_test_t)(FILE*, FILE*, char*);


// single tests
void test_gcc_rand(FILE* file_out);
void test_rand2   (FILE* file_out);

// multiple tests single output
void test_greedy      (FILE* file_in, FILE* file_out, char* graph_name);
void test_welsh_powell(FILE* file_in, FILE* file_out, char* graph_name);

// multiple tests multilple output
void test_bipartite   (FILE* file_in, FILE* file_out, char* graph_name);


#endif
