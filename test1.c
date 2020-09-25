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

bool is_eng(const char str[], size_t size)
{
    if (size == 0)
        return false;
    int i = 0;
    while (i < size) {
        if ((str[i] < 'A') || (str[i] > 'z') || (str[i] > 'Z' && str[i] < 'a'))
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
        printf("%s : %d\n", s0, is_eng(s0, sizeof(s0) - 1));
        printf("%s : %d\n", s1, is_eng(s1, sizeof(s1) - 1));
    }
    return 0;
}
