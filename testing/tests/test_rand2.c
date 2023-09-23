#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "../tests_run.h"
#include "../tests.helpers/tests.algorithms/kahan_sum.h"

#include "../../src/graph.h"
#include "../../src/graph.algorithms/algorithms.dependencies/random.h"


void test_rand2(FILE* file_out) {

    srand2(0b1011110000110110110000011111000101010101111010011101100100010011);
    i32 V = 2000000;
    u64* count = calloc(V, sizeof(u64));

    u64 N = 0;
    time_t start_time = time(NULL);
    while(N < 3000ull * 2000000ull) {
        count[rand2() % V]++;
        count[rand2() % V]++;
        count[rand2() % V]++;
        count[rand2() % V]++;
        count[rand2() % V]++;
        count[rand2() % V]++;
        count[rand2() % V]++;
        count[rand2() % V]++;
        count[rand2() % V]++;
        count[rand2() % V]++;

        N += 10;
    }
    double seconds = difftime(time(NULL), start_time);

    long double expected_frequency = N / V;
    long double* summands = malloc(V * sizeof(long double));
    for(i32 k = 0; k < V; k++) {
        long double diff = count[k] - expected_frequency;
        summands[k] = diff * diff;
    }

    long double sum = kahan_sum(summands, V);
    long double test_statistic = sum / expected_frequency;
    i32 df = V - 1;

    fprintf(file_out, "chi-square:%Lf\n", test_statistic);
    fprintf(file_out, "df:%d\n", df);
    fprintf(file_out, "seconds:%lf\n", seconds);
    fprintf(file_out, "N:%llu\n", N);

}
