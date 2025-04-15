#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../../src/primitives.h"
#include "../../src/graph.algorithms/algorithms.dependencies/random.h"

// #include "../tests_run.h"
// #include "../tests.helpers/tests.algorithms/kahan_sum.h"

// #include "../../src/graph.algorithms/algorithms.h"
// #include "../../src/graph.algorithms/algorithms.dependencies/random.h"


#define MAX_VERTICES 2000000
#define NGREEDYS 3000


typedef void (*srand_t) (u64);
typedef u64 (*rand_t) (void);


f128 sample_uniform_distribution(i64* sample, i64 max, i64 n, srand_t srand, rand_t rand) {
    const i32 ARBITRARY_32BITS = 0xAC688B99;
    srand(ARBITRARY_32BITS);

    time_t start_time = time(NULL);
    for(i64 i = 0; i < n; i++)
        sample[rand() % max]++;

    f128 seconds = difftime(time(NULL), start_time);
    return seconds;
}

f128 kahan_sum(f128* TERMS, i32 n) {
    f128 sum = 0.0;
    f128 c = 0.0;

    for (i32 i = 0; i < n; i++) {
        f128 y = TERMS[i] - c;
        f128 t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }

    return sum;
}

f128 chi_square(const i64* SAMPLE, i64 n, f128 population_mean) {
    f128* square_differences = malloc(n * sizeof(f128));
    for(i64 i = 0; i < n; i++) {
        f128 diff = SAMPLE[i] - population_mean;
        square_differences[i] = diff * diff;
    }

    f128 chi = kahan_sum(square_differences, n) / population_mean;

    free(square_differences);
    return chi;
}

/* used for comparing with our self-implemented rand2 function */
void c_rand_statistical_test(srand_t srand, rand_t rand) {
    /* We want to meassure an upper bound on how much time takes the rand()
    calls when performing the greedy algotithm in 3000 random orders */
    i64 MAX = MAX_VERTICES;
    i64 SAMPLE_SIZE = NGREEDYS * MAX;

    i64 POPULATION_MEAN = SAMPLE_SIZE / MAX;
    i64 DEGREES_OF_FREEDOM = MAX - 1;

    i64* sample = calloc(MAX, sizeof(i64));
    f128 seconds = sample_uniform_distribution(sample, MAX, SAMPLE_SIZE, srand, rand);
    f128 chi2 = chi_square(sample, MAX, POPULATION_MEAN);

    // fprintf(file_out, "sample size:%llu", SAMPLE_SIZE);
    // fprintf(file_out, "degrees of freedom:%lld\n", DEGREES_OF_FREEDOM);
    // fprintf(file_out, "seconds:%Lf\n", seconds);
    // fprintf(file_out, "chi-square:%Lf\n", chi2);

    printf("sample size:" i64_PRI "\n", SAMPLE_SIZE);
    printf("degrees of freedom:" i64_PRI "\n", DEGREES_OF_FREEDOM);
    printf("seconds:" f128_PRI "\n", seconds);
    printf("chi-square:" f128_PRI "\n", chi2);
}

void gcc_srand(u64 seed) {
    srand((u32) seed);
}

u64 gcc_rand(void) {
    return (u64) rand();
}

int main(void) {
    c_rand_statistical_test(gcc_srand, gcc_rand);
    printf("-------------\n");
    c_rand_statistical_test(srand2, rand2);
    return 0;
}