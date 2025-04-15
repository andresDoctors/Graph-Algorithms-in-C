#include "random.h"

static u64 state[4];

/* Splitmix64 */
void srand2(u64 __seed) {

    u64 seed = __seed;

    for(i32 i = 0; i < 4; i++) {
        seed += 0x9e3779b97f4a7c15;

        u64 z = seed;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        state[i] = z ^ (z >> 31);
    }
}

static inline u64 rotl(const u64 x, i32 k) {
    return (x << k) | (x >> (64 - k));
}

/* xoshiro256** */
u64 rand2(void) {

    const u64 result = rotl(state[1] * 5, 7) * 9;
    const u64 t      = state[1] << 17;

    state[2] ^= state[0];
    state[3] ^= state[1];
    state[1] ^= state[2];
    state[0] ^= state[3];

    state[2] ^= t;

    state[3] = rotl(state[3], 45);

    return result;
}
