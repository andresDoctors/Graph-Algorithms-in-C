#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "random.h"

static u64 state[4];

/* Splitmix64 */
void srand2(u64 __seed) {

    u64 seed = __seed;

    for(i32 i = 0; i < 4; i++) {
        seed += 0x9e3779b97f4a7c15;

        u64 z = seed;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        state[i] = z ^ (z >> 31);
    }
}

static inline u64 rotl(const u64 x, i32 k) {
    return (x << k) | (x >> (64 - k));
}

/* xoshiro256** */
u64 rand2(void) {

    const u64 result = rotl(state[1] * 5, 7) * 9;
    const u64 t      = state[1] << 17;

    state[2] ^= state[0];
    state[3] ^= state[1];
    state[1] ^= state[2];
    state[0] ^= state[3];

    state[2] ^= t;

    state[3] = rotl(state[3], 45);

    return result;
}

/** in range [a, b) */
u64 uniform(u64 a, u64 b) {
    return a + (rand2() % (b - a));
}

#define populate_random_array(TYPE, MASK)             \
    do {                                              \
        TYPE* _arr_ = (TYPE*)arr;                     \
        for (i32 i = 0; i < n; i++) {                 \
            TYPE r = (TYPE) (uniform(a, b) & (MASK)); \
            _arr_[i] = r;                             \
        }                                             \
    } while (0)

void random_array(void* arr, i32 n, i32 size, u64 a, u64 b) {
    assert(arr);
    assert(n > 0);
    assert(size == 1 || size == 2 || size == 4 || size == 8);

    switch (size) {
        case 1: populate_random_array(u08, u08_MAX); break;
        case 2: populate_random_array(u16, u16_MAX); break;
        case 4: populate_random_array(u32, u32_MAX); break;
        case 8: populate_random_array(u64, u64_MAX); break;
    }
}

void random_edges(i32* edges, i32 nvertices, i32 nedges) {
    assert(edges);
    assert(nvertices > 0);
    assert(nedges > 0);

    random_array(edges, 2*nedges, sizeof(i32), 0, nvertices);

    i32* names = malloc(nvertices*sizeof(i32));
    random_array(names, nvertices, sizeof(i32), 0, i32_MAX);

    for (i32 i = 0; i < 2*nedges; i++)
        edges[i] = names[edges[i]];

    free(names);
}

