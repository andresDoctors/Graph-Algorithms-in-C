#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../unity/unity.h"
#include "../src/dimacs.h"
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

void setUp(void) {}
void tearDown(void) {}

#define DEFINE_GRAPH_TEST(name, filename)                            \
    void test_##name(void) {                                         \
        char filepath[] = "graphs/" filename;                        \
        i32 nvertices, nedges;                                       \
                                                                     \
        FILE* STREAM = fopen(filepath, "r");                         \
        u32* edges = dimacs_scan(STREAM, &nvertices, &nedges);       \
                                                                     \
        i32 cmp = memcmp(edges, name##_edges, nedges * sizeof(u32)); \
        TEST_ASSERT_EQUAL_INT32(0, cmp);                             \
                                                                     \
        fclose(STREAM);                                              \
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
