#include "kahan_sum.h"


long double kahan_sum(long double* arr, i32 n) {
    long double sum = 0.0;
    long double c = 0.0;

    for(i32 i = 0; i < n; i++) {
        long double y = arr[i] - c;
        long double t = sum + y;
        c = (t - sum) - y;

        sum = t;
    }

    return sum;
}
