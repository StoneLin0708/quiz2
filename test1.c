#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

bool is_ascii(const char str[], size_t size)
{
    if (size == 0)
        return false;
    for (int i = 0; i < size; i++)
        if (str[i] & 0x80) /* i.e. (unsigned) str[i] >= 128 */
            return false;
    return true;
}

bool is_ascii64(const char str[], size_t size)
{
    if (size == 0)
        return false;
    int i = 0;
    while ((i + 8) <= size) {
        uint64_t payload;
        memcpy(&payload, str + i, 8);
        if (payload & 0x8080808080808080)
            return false;
        i += 8;
    }
    while (i < size) {
        if (str[i] & 0x80)
            return false;
        i++;
    }
    return true;
}


#define PACKED_BYTE(b) (((uint64_t)(b) & (0xff)) * 0x0101010101010101u)

bool is_alphabet(const char str[], size_t size)
{
    if (size == 0)
        return false;
    int i = 0;
    while ((i + 8) <= size) {
        uint64_t payload;
        memcpy(&payload, str + i, 8);
        payload |= PACKED_BYTE(0x20);
        uint64_t a_check = payload + PACKED_BYTE(0x80 - 'a');
        uint64_t z_check = payload + PACKED_BYTE(0x80 - 'z' - 1);
        if ((a_check ^ z_check) & PACKED_BYTE(0x80) ^ PACKED_BYTE(0x80))
            return false;
        i += 8;
    }
    while (i < size) {
        const char c = str[i] | 0x20;
        if (c < 'a' || c > 'z')
            return false;
        i++;
    }
    return true;
}

int main(int argc, char const *argv[])
{
    {
        char s0[] = {'A', 'B', 'C', 0};
        char s1[] = {0xFF, 'A', 'B', 0};
        printf("%s : %d\n", s0, is_ascii64(s0, sizeof(s0) - 1));
        printf("%s : %d\n", s1, is_ascii64(s1, sizeof(s1) - 1));
    }
    {
        char s0[] = {'a', 'B', 'C', 'D', 'A', 'B', 'C', 'D', 'A', 0};
        char s1[] = {0x40, 'A', 'B', 'C', 0};
        char s2[] = {0x40, 'A', 'B', 'C', 'A', 'B', 'C', 'D', 'A', 0};
        printf("%s : %d\n", s0, is_alphabet(s0, sizeof(s0) - 1));
        printf("%s : %d\n", s1, is_alphabet(s1, sizeof(s1) - 1));
        printf("%s : %d\n", s2, is_alphabet(s2, sizeof(s2) - 1));
    }
    return 0;
}
