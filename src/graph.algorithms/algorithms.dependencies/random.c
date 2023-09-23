#include "random.h"


#ifdef UINT64_MAX


static uint64_t state[4];

/* Splitmix64 */
void srand2(u64 __seed) {

    uint64_t seed = __seed;

    for(i32 i = 0; i < 4; i++) {
        seed += 0x9e3779b97f4a7c15;

        uint64_t z = seed;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        state[i] = z ^ (z >> 31);
    }
}

static inline uint64_t rotl(const uint64_t x, i32 k) {
    return (x << k) | (x >> (64 - k));
}

/* xoshiro256** */
u64 rand2(void) {

    const uint64_t result = rotl(state[1] * 5, 7) * 9;
    const uint64_t t      = state[1] << 17;

    state[2] ^= state[0];
    state[3] ^= state[1];
    state[1] ^= state[2];
    state[0] ^= state[3];

    state[2] ^= t;

    state[3] = rotl(state[3], 45);

    return result;
}


#else


u64 state[4];
#define __BITMASK64 0xFFFFFFFFFFFFFFFF

/* Splitmix64 */
void srand2(u64 seed) {

    seed &= __BITMASK64;
    for(i32 i = 0; i < 4; i++) {
        seed += 0x9e3779b97f4a7c15;
        seed &= __BITMASK64;

        u64 z = seed;

        z  = z ^ (z >> 30)
        z &= __BITMASK64
        z *= 0xbf58476d1ce4e5b9;
        z &= __BITMASK64;

        z  = z ^ (z >> 27)
        z &= __BITMASK64
        z *= 0x94d049bb133111eb;
        z &= __BITMASK64;

        z  = z ^ (z >> 31);
        z &= __BITMASK64;

        state[i] = z;
    }
}

static inline u64 rotl(u64 x, i32 k) {
    x &= __BITMASK64;
    return (__BITMASK64 & (x << k)) | (x >> (64 - k));
}

/* xoshiro256** */
u64 rand2(void) {
    const u64 result = (rotl(state[1] * 5, 7) * 9) & __BITMASK64;
    const u64 t      = (state[1] << 17) & __BITMASK64;

    state[2] ^= state[0];
    state[2] &= __BITMASK64;
    state[3] ^= state[1];
    state[3] &= __BITMASK64;
    state[1] ^= state[2];
    state[1] &= __BITMASK64;
    state[0] ^= state[3];
    state[0] &= __BITMASK64;

    state[2] ^= t;
    state[2] &= __BITMASK64;

    state[3] = rotl(state[3], 45);

    return result;
}


#endif
