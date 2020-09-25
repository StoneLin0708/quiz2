#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

const uint32_t D = 3;
#define M ((uint64_t)(UINT64_C(0xFFFFFFFFFFFFFFFF) / (D) + 1))

bool divisible(uint32_t n)
{
    return n * M <= (M - 1);
}


int main(int argc, char const *argv[])
{
    for (int i = 0; i < 100; ++i) {
        if (divisible(i) != (i % D == 0))
            printf("divisible fail : %d", i);
    }
    printf("done\n");
    return 0;
}
