#include <stdio.h>
#include <stdint.h>
#include <setjmp.h>


#include "guess.h"

#if _WIN32
#  define C_RED(s)     s
#  define C_GREEN(s)   s
#else
#  define C_RED(s)     "\033[31;1m" s "\033[0m"
#  define C_GREEN(s)   "\033[32;1m" s "\033[0m"
#endif

#define TEST(s, x)                              \
    do {                                        \
        if (x) {                                \
            printf(C_GREEN("PASS") " %s\n", s); \
            count_pass++;                       \
        } else {                                \
            printf(C_RED("FAIL") " %s\n", s);   \
            count_fail++;                       \
        }                                       \
    } while (0)


int main(int argc, char **argv) {
    volatile int count_pass = 0;
    volatile int count_fail = 0;

    TEST("Arabic 1 to roman I", !strcmp(to_roman(1), "I"));
    TEST("Arabic 42 to roman XLII", !strcmp(to_roman(42), "XLII"));
    TEST("Roman I to arabic 1", to_arabic("I") == 1);
    TEST("Roman XCIX to arabic 99", to_arabic("XCIX") == 99);

    printf("%d fail, %d pass\n", count_fail, count_pass);
    return count_fail != 0;
}