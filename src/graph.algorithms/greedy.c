#include <stdlib.h>
#include <string.h>

#include "algorithms.h"


static u64* bits_new(i32 nbits) {
    assert(nbits > 0);

    i32 nwords = (nbits + 63) / 64;
    u64* bits = malloc(nwords*sizeof(u64));

    return bits;
}

static void bits_clear(u64* bits, i32 nbits) {
    assert(bits);
    assert(nbits > 0);

    i32 nwords = (nbits + 63) / 64;
    memset(bits, 0x00, nwords*sizeof(u64));
}

static void bits_set(u64* bits, i32 i) {
    assert(bits);
    assert(i >= 0);

    bits[i / 64] |= (1ULL << (i % 64));
}

/* should be compiled using no loops, but bsr assembly instruction */
static i32 least_significant_set_bit(u64 word) {
    assert(word != 0);

    i32 i = 0;
    while(word >>= 1) i++;

    assert(0 <= i && i < 64);
    return i;
}

/* Finds the smallest non-negative integer `i` such that:
 * - `bits_set(bits, i)` has not been called (i.e., the bit at position `i` is not set). */
static i32 bits_first_not_set(u64* bits) {
    assert(bits);

    i32 i = 0;
    while(bits[i] == u64_MAX) i++;
    i32 j = least_significant_set_bit(~bits[i]);

    return 64*i + j;
}

static i32 maximum_i32(i32* arr, i32 n) {
    assert(arr);
    assert(n > 0);

    i32 max = arr[0];
    for(i32 i = 1; i < n; i++) {
        if(arr[i] > max) {
            max = arr[i];
        }
    }

    return max;
}

i32 greedy(graph_t g, i32* order, i32* colors) {
    for (i32 i = 0; i < g->nvertices; i++)
        assert(0 <= order[i] && order[i] < g->nvertices);

    u64* marked_colors = bits_new(g->Delta + 2);
    memset(colors, 0x00, g->nvertices*sizeof(i32));

    for(i32 i = 0; i < g->nvertices; i++) {
        i32 v = order[i];
        bits_clear(marked_colors, degree(g, v) + 2);

        for(i32 j = 0; j < degree(g, v); j++) {
            i32 w = neighbor(g, v, j);
            bits_set(marked_colors, colors[w]);
        }

        colors[v] = bits_first_not_set(marked_colors);
    }

    for (i32 v = 0; v < g->nvertices; v++)
        assert(1 <= colors[v] && colors[v] <= g->Delta + 1);

    free(marked_colors);
    return maximum_i32(colors, g->nvertices);
}
