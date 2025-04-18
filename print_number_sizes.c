#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main(void) {
    printf("char:%lu\n", sizeof(char));
    printf("short:%lu\n", sizeof(short));
    printf("long:%lu\n", sizeof(long));
    printf("long-long:%lu\n", sizeof(long long));

    printf("unsigned-char:%lu\n", sizeof(unsigned char));
    printf("unsigned-short:%lu\n", sizeof(unsigned short));
    printf("unsigned-long:%lu\n", sizeof(unsigned long));
    printf("unsigned-long-long:%lu\n", sizeof(unsigned long long));

    printf("float:%lu\n", sizeof(float));
    printf("double:%lu\n", sizeof(double));
    printf("long-double:%lu\n", sizeof(long double));

    printf("int8_t:%lu\n", sizeof(int8_t));
    printf("int16_t:%lu\n", sizeof(int16_t));
    printf("int32_t:%lu\n", sizeof(int32_t));
    printf("int64_t:%lu\n", sizeof(int64_t));

    printf("uint8_t:%lu\n", sizeof(uint8_t));
    printf("uint16_t:%lu\n", sizeof(uint16_t));
    printf("uint32_t:%lu\n", sizeof(uint32_t));
    printf("uint64_t:%lu\n", sizeof(uint64_t));

    printf("PRId8:'%s'\n", PRId8);
    printf("PRId16:'%s'\n", PRId16);
    printf("PRId32:'%s'\n", PRId32);
    printf("PRId64:'%s'\n", PRId64);

    printf("PRIu8:'%s'\n", PRIu8);
    printf("PRIu16:'%s'\n", PRIu16);
    printf("PRIu32:'%s'\n", PRIu32);
    printf("PRIu64:'%s'\n", PRIu64);

    printf("SCNd8:'%s'\n", SCNd8);
    printf("SCNd16:'%s'\n", SCNd16);
    printf("SCNd32:'%s'\n", SCNd32);
    printf("SCNd64:'%s'\n", SCNd64);

    printf("SCNu8:'%s'\n", SCNu8);
    printf("SCNu16:'%s'\n", SCNu16);
    printf("SCNu32:'%s'\n", SCNu32);
    printf("SCNu64:'%s'\n", SCNu64);

    return 0;
}
