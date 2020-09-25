#include <stdint.h>
#include <stdio.h>

uint8_t hexchar2val(uint8_t in)
{
    const uint8_t letter = in & 0x40;
    const uint8_t shift = (letter >> 3) | (letter >> 5);
    return (in + shift) & 0xf;
}

int main(int argc, char const *argv[])
{
    const char *hex = "aB09";
    for (int i = 0; i < 4; ++i)
        printf("%c, %d\n", hex[i], hexchar2val(hex[i]));
    return 0;
}
