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

int singleNumber2(int* nums, int numsSize){
    int bits = sizeof(int) * 8;
    const int n = 3;
    unsigned res = 0;
    for(int b=0; b < bits; ++b){
        int c=0;
        for(int i=0; i<numsSize; ++i){
            c += (nums[i]>>b) & 0x1;
        }
        res |= (unsigned)(c % 3) << b;
    }
    return res;
}

int main(int argc, char const *argv[])
{
    int x[] = {1, 2, 1, 3, 2, 2, 1};
    printf("%d\n", singleNumber(x, sizeof(x) / sizeof(int)));
    printf("%d\n", singleNumber2(x, sizeof(x) / sizeof(int)));
    return 0;
}
