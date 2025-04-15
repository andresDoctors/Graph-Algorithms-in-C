#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <omp.h>

#include "graph.h"


#define bit(n) ((u64) 1 << (n))


static u64* bitarray_new(i32 nbits) {
    assert(nbits > 0);

    i32 nwords = (nbits + 63) / 64;
    u64* bits = malloc(nwords*sizeof(u64));

    return bits;
}

static void bitarray_clear(u64* bits, i32 nbits) {
    assert(bits);
    assert(nbits > 0);

    i32 nwords = (nbits + 63) / 64;
    memset(bits, 0x00, nwords*sizeof(u64));
}

static void bitarray_set(u64* bits, i32 i) {
    assert(bits);
    assert(i >= 0);

    bits[i / 64] |= bit(i % 64);
}

/* Finds the smallest non-negative integer `i` such that:
 * - `bitarray_set(bits, i)` has not been called (i.e., the bit at position `i` is not set). */
static i32 bits_find_first_zero(const u64* BITS) {
    assert(BITS);

    i32 i, j;
    for(i = 0; BITS[i] == u64_MAX; i++);
    j = __builtin_ctzll(~BITS[i]);

    return 64*i + j;
}

static i32 maximum_i32(const i32* ARR, i32 n) {
    assert(ARR);
    assert(n > 0);

    i32 max = ARR[0];
    for(i32 i = 1; i < n; i++) {
        if(ARR[i] > max) {
            max = ARR[i];
        }
    }

    return max;
}

i32 greedy(graph_t g, const i32* ORDER, i32* colors) {
    for (i32 i = 0; i < g->nvertices; i++)
        assert(0 <= ORDER[i] && ORDER[i] < g->nvertices);

    memset(colors, 0x00, g->nvertices*sizeof(i32));
    u64* neighbor_colors_bitmap = bitarray_new(g->Delta + 3);

    for(i32 i = 0; i < g->nvertices; i++) {
        i32 v = ORDER[i];
        bitarray_clear(neighbor_colors_bitmap, degree(g, v) + 3);

        // #pragma omp parallel for
        for(i32 j = 0; j < degree(g, v); j++) {
            i32 w = neighbor(g, v, j);
            bitarray_set(neighbor_colors_bitmap, colors[w]);
            // printf("Thread %d: i = %d\n", omp_get_thread_num(), i);
        }

        bitarray_set(neighbor_colors_bitmap, 0);
        colors[v] = bits_find_first_zero(neighbor_colors_bitmap);
    }

    for (i32 v = 0; v < g->nvertices; v++)
        assert(1 <= colors[v] && colors[v] <= g->Delta + 1);

    free(neighbor_colors_bitmap);
    return maximum_i32(colors, g->nvertices);
}
