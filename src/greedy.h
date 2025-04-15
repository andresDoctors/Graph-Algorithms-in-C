#include "graph.h"
#include "primitives.h"


/**
 * For each vertex `v` being processed, a bitmap is used to track the colors
 * already assigned to its neighbors. Specifically, the bit at position `i` 
 * is set if and only if vertex `v` has at least one neighbor with color `i`.
 * 
 * @param g The graph to be colored.
 * 
 * @param ORDER An array of length `g->nvertices`, containing a permutation of
 *        vertex indices (from 0 to `g->nvertices - 1`) that specifies the order 
 *        in which the vertices are processed.
 * 
 * @param colors An array of length `g->nvertices`, allocated by the caller,
 *        which will store the assigned colors (ranging from 1 to `g->Delta + 1`).
 * 
 * @return The maximum color used in the coloring process.
 */
i32 greedy(graph_t g, const i32* ORDER, i32* colors);
