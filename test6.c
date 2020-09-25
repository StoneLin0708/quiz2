#include <stdio.h>

int singleNumber(int *nums, int numsSize)
{
    int lower = 0, higher = 0;
    for (int i = 0; i < numsSize; i++) {
        lower ^= nums[i];
        lower &= ~higher;
        higher ^= nums[i];
        higher &= ~lower;
    }
    return lower;
}

int main(int argc, char const *argv[])
{
    int x[] = {1, 2, 1, 3, 2, 2, 1};
    printf("%d\n", singleNumber(x, sizeof(x) / sizeof(int)));
    return 0;
}
