#include <stdlib.h>
#include <time.h>

#include "../tests_run.h"
#include "../tests.helpers/tests.algorithms/kahan_sum.h"

#include "../../src/graph.algorithms/algorithms.h"
#include "../../src/graph.algorithms/algorithms.dependencies/random.h"


#define MAX_VERTICES 2000000


double sample_uniform_distribution(i64* sample, i64 max, i64 n) {
    const i32 ARBITRARY_32BITS = 0xAC688B99;
    srand(ARBITRARY_32BITS);

    time_t start_time = time(NULL);
    for(i64 i = 0; i < n; i++)
        sample[rand() % max]++;

    double seconds = difftime(time(NULL), start_time);
    return seconds;
}

double chi_square(i64* sample, i64 n, long double population_mean) {
    long double* square_differences = malloc(n * sizeof(long double));
    for(i64 i = 0; i < n; i++) {
        long double diff = sample[i] - population_mean;
        square_differences[i] = diff * diff;
    }

    return kahan_sum(square_differences, n) / population_mean;
}

/* used for comparing with our self-implemented rand2 function */
void c_rand_statistical_test(FILE* file_out) {
    /* We want to meassure an upper bound on how much time takes the rand()
    calls when performing the greedy algotithm in 3000 random orders */
    i64 MAX = MAX_VERTICES;
    i64 SAMPLE_SIZE = 3000 * MAX;

    i64 POPULATION_MEAN = SAMPLE_SIZE / MAX;
    i64 DEGREES_OF_FREEDOM = MAX - 1;

    i64* sample = calloc(MAX, sizeof(i64));
    long double seconds = sample_uniform_distribution(sample, MAX, SAMPLE_SIZE);
    long double chi2 = chi_square(sample, MAX, POPULATION_MEAN);

    fprintf(file_out, "sample size:%llu", SAMPLE_SIZE);
    fprintf(file_out, "degrees of freedom:%lld\n", DEGREES_OF_FREEDOM);
    fprintf(file_out, "seconds:%lf\n", seconds);
    fprintf(file_out, "chi-square:%Lf\n", chi2);
}
