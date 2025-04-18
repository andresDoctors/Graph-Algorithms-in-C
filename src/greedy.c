#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <omp.h>

#include "graph.h"


#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))


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

    bits[i / 64] |= ((u64) 1 << (i % 64));
}

/* Finds the smallest non-negative integer `i` such that:
 * - `bitarray_set(bits, i)` has not been called (i.e., the bit at position `i` is not set). */
static i32 bitarray_find_first_zero(const u64* BITS) {
    assert(BITS);

    i32 i, j;
    for(i = 0; BITS[i] == u64_MAX; i++);
    j = __builtin_ctzll(~BITS[i]);

    assert(0 <= j && j < 64);
    return 64*i + j;
}

i32 greedy(graph_t g, const i32* ORDER, i32* colors) {
    for (i32 i = 0; i < nvertices(g); i++)
        assert(0 <= ORDER[i] && ORDER[i] < nvertices(g));

    i32 chi = 0;
    memset(colors, 0x00, nvertices(g)*sizeof(i32));
    u64* neighbor_colors_bitmap = bitarray_new(delta(g) + 2);

    for(i32 i = 0; i < nvertices(g); i++) {
        i32 v = ORDER[i];
        i32 v_color_upper_bound = min(degree(g, v) + 1, chi + 1);
        bitarray_clear(neighbor_colors_bitmap, v_color_upper_bound + 1);

        #pragma omp parallel for
        for(i32 j = 0; j < degree(g, v); j++) {
            i32 w = neighbor(g, v, j);
            bitarray_set(neighbor_colors_bitmap, colors[w]);
        }

        bitarray_set(neighbor_colors_bitmap, 0);
        colors[v] = bitarray_find_first_zero(neighbor_colors_bitmap);
        chi = max(chi, colors[v]);
    }

    for (i32 v = 0; v < nvertices(g); v++)
        assert(1 <= colors[v] && colors[v] <= chi && chi <= delta(g) + 1);

    free(neighbor_colors_bitmap);
    return chi;
}
