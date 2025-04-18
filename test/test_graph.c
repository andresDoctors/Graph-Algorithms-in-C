#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../unity/unity.h"
#include "../src/graph.h"
#include "../src/primitives.h"
#include "../test/random.h"
#include "../test/utils.h"


i32* tringle(i32* nvertices, i32* nedges) {
    *nvertices = 3;
    *nedges = 3;

    i32* edges = malloc(2*(*nedges)*sizeof(i32));
    edges[0] = 1; edges[1] = 2;
    edges[2] = 2; edges[3] = 3;
    edges[4] = 3; edges[5] = 1;
    return edges;
}

i32 are_neighbors(graph_t g, i32 v, i32 w) {
    i32 b1 = 0;
    for(i32 i = 0; i < degree(g, v); i++)
        b1 = b1 || (neighbor(g, v, i) == v);

    i32 b2 = 0;
    for(i32 i = 0; i < degree(g, w); i++)
        b2 = b2 || (neighbor(g, w, i) == w);

    return b1 && b2;
}

/** for a graph to be considered valid it must be connected and have more than
  * one vertex */
i32 graph_is_invalid(graph_t g) {
    if(g == NULL) return -1;

    if(nvertices(g) <= 0)    return -2;
    if(nedges(g)    <= 0)    return -3;
    if(delta(g)     <= 0)    return -4;

    for(i32 v = 0; v < nvertices(g); v++)
        if(degree(g, v) < 0) return -5;

    for(i32 v = 0; v < nvertices(g); v++) {
        for(i32 i = 0; i < degree(g, v); i++) {
            i32 w = neighbor(g, v, i);
            if(w < 0) return -6;
        }
    }

    i32 max_degree = i32_MIN;
    for(i32 v = 0; v < nvertices(g); v++)
        max_degree = (max_degree > degree(g, v)) ? max_degree : degree(g, v);
    if(delta(g) != max_degree) return -7;

    for(i32 v = 0; v < nvertices(g); v++) {
        for(i32 i = 0; i < degree(g, v); i++) {
            i32 w = neighbor(g, v, i);

            i32 b = 0;
            for(i32 j = 0; j < degree(g, w); j++)
                b = b || (neighbor(g, w, j) == v);

            if(!b) return -8;
        }
    }

    for(i32 v = 0; v < nvertices(g); v++) {
        for(i32 i = 0; i < degree(g, v); i++) {
            i32 w = neighbor(g, v, i);
            if(w == v) return -9;
        }
    }

    return 0;
}

void setUp(void) {}

void tearDown(void) {}

void test_triangle(void) {
    i32 nvertices, nedges;
    i32* edges = tringle(&nvertices, &nedges);
    graph_t g = graph_new(edges, nvertices, nedges);

    TEST_ASSERT_EQUAL_INT(0, graph_is_invalid(g));

    TEST_ASSERT_EQUAL_INT(3, g->nvertices);
    TEST_ASSERT_EQUAL_INT(3, g->nedges);
    TEST_ASSERT_EQUAL_INT(2, g->Delta);

    for(i32 i = 0; i < g->nvertices; i++)
        TEST_ASSERT_EQUAL_INT(2, g->degrees[i]);

    TEST_ASSERT_TRUE(are_neighbors(g, 0, 1));
    TEST_ASSERT_TRUE(are_neighbors(g, 1, 2));
    TEST_ASSERT_TRUE(are_neighbors(g, 2, 0));

    graph_destroy(g);
}

int main(void) {
    UNITY_BEGIN();
        RUN_TEST(test_triangle);
    UNITY_END();

    return 0;
}
