#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../unity/unity.h"
#include "../src/graph.h"
#include "../src/primitives.h"

#include "../test/edges/A1H75_18.txt.c"
#include "../test/edges/C1599_1777.txt.c"
#include "../test/edges/CBQsc100_200_11_1517.c"
#include "../test/edges/CBQsv10_22_61.txt.c"
#include "../test/edges/Cne140_4.txt.c"
#include "../test/edges/DG100.txt.c"
#include "../test/edges/GRD22154753987.c"
#include "../test/edges/KC.txt.c"
#include "../test/edges/KD.txt.c"
#include "../test/edges/KM.txt.c"
#include "../test/edges/PG64.txt.c"
#include "../test/edges/R22_99_15.txt.c"
#include "../test/edges/bxb15_22_10.txt.c"
#include "../test/edges/lux1.txt.c"
#include "../test/edges/lux2.txt.c"
#include "../test/edges/lux3.txt.c"
#include "../test/edges/q10.corr.c"
#include "../test/edges/q13.corr.c"
#include "../test/edges/school1.col.c"

i32 edges_cmp(const void* _edge1_, const void* _edge2_) {
    u32* edge1 = (u32*) _edge1_;
    u32* edge2 = (u32*) _edge2_;

    u32 v = edge1[0], w = edge2[0];
    if(v == w)
        v = edge1[1], w = edge2[1];

    return (v > w) - (v < w);
}

i32 edges_deduplicated(u32* dst, u32* SRC, i32 n) {
    assert(dst);
    assert(SRC);
    assert(n > 0);
    for(i32 i = 0; i < n - 1; i++) {
        i32 cmp = edges_cmp(&SRC[2*i], &SRC[2*i + 2]);
        assert(cmp <= 0);
    }

    dst[2*0]     = SRC[2*0];
    dst[2*0 + 1] = SRC[2*0 + 1];
    i32 dst_size = 1;

    for(i32 i = 1; i < n; i++) {
        i32 cmp = edges_cmp(&SRC[2*i - 2], &SRC[2*i]);
        if(cmp != 0) {
            dst[2*dst_size]     = SRC[2*i];
            dst[2*dst_size + 1] = SRC[2*i + 1];
            dst_size++;
        }
    }

    for(i32 i = 0; i < dst_size - 1; i++) {
        i32 cmp = edges_cmp(&dst[2*i], &dst[2*i + 2]);
        assert(cmp < 0);
    }

    return dst_size;
}

#define max(a, b) ((a) >= (b) ? (a) : (b))
#define min(a, b) ((a) <= (b) ? (a) : (b))

void edges_sorted_endpoints(u32* dst, u32* SRC, i32 n) {
    assert(dst);
    assert(SRC);
    assert(n > 0);

    for(i32 i = 0; i < n; i++) {
        u32 min = min(SRC[2*i], SRC[2*i + 1]);
        u32 max = max(SRC[2*i], SRC[2*i + 1]);

        dst[2*i]     = min;
        dst[2*i + 1] = max;
    }

    for(i32 i = 0; i < n; i++)
        assert(dst[2*i] <= dst[2*i + 1]);
}

void setUp(void) {}
void tearDown(void) {}

#define DEFINE_GRAPH_TEST(name, filename)                                              \
    void test_##name(void) {                                                           \
        graph_t g = graph_new(name##_edges, name##_nvertices, name##_nedges);          \
        u32* edges = malloc(2 * name##_nedges * sizeof(u32));                          \
        i32 nedges = graph_to_edges(edges, g);                                         \
                                                                                       \
        edges_sorted_endpoints(name##_edges, name##_edges, name##_nedges);             \
        qsort(name##_edges, name##_nedges, 2*sizeof(u32), edges_cmp);                  \
        name##_nedges = edges_deduplicated(name##_edges, name##_edges, name##_nedges); \
                                                                                       \
        TEST_ASSERT_EQUAL_INT32(name##_nvertices, nvertices(g));                       \
        TEST_ASSERT_EQUAL_INT32(name##_nedges, nedges(g));                             \
        TEST_ASSERT_EQUAL_INT32(name##_nedges, nedges);                                \
                                                                                       \
        i32 cmp = memcmp(edges, name##_edges, 2*name##_nedges*sizeof(u32));            \
        TEST_ASSERT_EQUAL_INT32(0, cmp);                                               \
                                                                                       \
        free(edges);                                                                   \
        graph_destroy(g);                                                              \
    }

DEFINE_GRAPH_TEST(A1H75_18, "A1H75_18.txt")
DEFINE_GRAPH_TEST(C1599_1777, "C1599_1777.txt")
DEFINE_GRAPH_TEST(CBQsc100_200_11_1517, "CBQsc100_200_11_1517")
DEFINE_GRAPH_TEST(CBQsv10_22_61, "CBQsv10_22_61.txt")
DEFINE_GRAPH_TEST(Cne140_4, "Cne140_4.txt")
DEFINE_GRAPH_TEST(DG100, "DG100.txt")
DEFINE_GRAPH_TEST(GRD22154753987, "GRD22154753987")
DEFINE_GRAPH_TEST(KC, "KC.txt")
DEFINE_GRAPH_TEST(KD, "KD.txt")
DEFINE_GRAPH_TEST(KM, "KM.txt")
DEFINE_GRAPH_TEST(PG64, "PG64.txt")
DEFINE_GRAPH_TEST(R22_99_15, "R22_99_15.txt")
DEFINE_GRAPH_TEST(bxb15_22_10, "bxb15_22_10.txt")
DEFINE_GRAPH_TEST(lux1, "lux1.txt")
DEFINE_GRAPH_TEST(lux2, "lux2.txt")
DEFINE_GRAPH_TEST(lux3, "lux3.txt")
DEFINE_GRAPH_TEST(q10, "q10.corr")
DEFINE_GRAPH_TEST(q13, "q13.corr")
DEFINE_GRAPH_TEST(school1, "school1.col")

int main(void) {
    UNITY_BEGIN();
        RUN_TEST(test_A1H75_18);
        RUN_TEST(test_C1599_1777);
        RUN_TEST(test_CBQsc100_200_11_1517);
        RUN_TEST(test_CBQsv10_22_61);
        RUN_TEST(test_Cne140_4);
        RUN_TEST(test_DG100);
        RUN_TEST(test_GRD22154753987);
        RUN_TEST(test_KC);
        RUN_TEST(test_KD);
        RUN_TEST(test_KM);
        RUN_TEST(test_PG64);
        RUN_TEST(test_R22_99_15);
        RUN_TEST(test_bxb15_22_10);
        RUN_TEST(test_lux1);
        RUN_TEST(test_lux2);
        RUN_TEST(test_lux3);
        RUN_TEST(test_q10);
        RUN_TEST(test_q13);
        RUN_TEST(test_school1);
    UNITY_END();

    return 0;
}
