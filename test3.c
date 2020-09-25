#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

const uint32_t D = 3;
#define M ((uint64_t)(UINT64_C(0xFFFFFFFFFFFFFFFF) / (D) + 1))

/* compute (n mod d) given precomputed M */
uint32_t quickmod(uint32_t n)
{
    uint64_t quotient = ((__uint128_t) M * n) >> 64;
    return n - quotient * D;
}

int main(int argc, char const *argv[])
{
    for (int i = 0; i < 100; ++i) {
        if (quickmod(i) != i % D)
            printf("Quick mod fail : %d", i);
    }
    printf("done\n");
    return 0;
}
