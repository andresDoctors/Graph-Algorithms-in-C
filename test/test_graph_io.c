#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../unity/unity.h"
#include "../src/graph_io.h"
#include "../src/primitives.h"
#include "../test/random.h"
#include "../test/utils.h"

FILE* stream;
i32 nvertices1, nedges1, seed;

void setUp() {
    stream = fopen("test/test_graph_io.txt", "w+");
    assert(stream);
}

void tearDown() {
    int fclose_error = fclose(stream);
    assert(!fclose_error);
    int remove_error = remove("test/test_graph_io.txt");
    assert(!remove_error);
}

/** @param nvertices1
 *  @param nedges1
 *  @param stream
 *  @param seed
 */
void test_random_input(void) {
    srand2(seed);

    i32* edges1 = malloc(2*nedges1*sizeof(i32));
    random_edges(edges1, nvertices1, nedges1);
    edges_to_file(edges1, nvertices1, nedges1, stream);

    i32 nvertices2, nedges2;
    i32* edges2 = scan_graph(stream, &nvertices2, &nedges2);

    TEST_ASSERT_EQUAL_INT32(nvertices1, nvertices2);
    TEST_ASSERT_EQUAL_INT32(nedges1, nedges2);
    for (i32 i = 0; i < 2*nedges1; i++) {
        TEST_ASSERT_EQUAL_INT32(edges1[i], edges2[i]);
    }

    free(edges1);
    free(edges2);
}


int main(void) {
    UNITY_BEGIN();
        srand2(81);
        for(i32 i = 0; i < 100; i++) {
            seed = uniform(0, u64_MAX);
            nvertices1 = uniform(1, 2000000);
            nedges1 = uniform(1, 10000000);
            RUN_TEST(test_random_input);
        }
    UNITY_END();

    return 0;
}
