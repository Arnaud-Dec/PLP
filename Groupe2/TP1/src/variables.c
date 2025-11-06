#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void) {
    char c = CHAR_MIN;
    signed char sc = SCHAR_MIN;
    unsigned char uc = UCHAR_MAX;
    printf("c: %d, sc: %d, uc: %u\n", c, sc, uc);

    short s = SHRT_MIN;
    signed short ss = SHRT_MIN;
    unsigned short us = USHRT_MAX;
    printf("s: %d, ss: %d, us: %u\n", s, ss, us);

    int i = INT_MIN;
    signed int si = INT_MIN;
    unsigned int ui = UINT_MAX;
    printf("i: %d, si: %d, ui: %u\n", i, si, ui);

    long int li = LONG_MIN;
    signed long int sli = LONG_MIN;
    unsigned long int uli = ULONG_MAX;
    printf("li: %ld, sli: %ld, uli: %lu\n", li, sli, uli);

    long long int lli = LLONG_MIN;
    signed long long int slli = LLONG_MIN;
    unsigned long long int ulli = ULLONG_MAX;
    printf("lli: %lld, slli: %lld, ulli: %llu\n", lli, slli, ulli);

    float f = -FLT_MAX;
    printf("f: %e\n", f);

    double d = -DBL_MAX;
    printf("d: %e\n", d);

    long double ld = -LDBL_MAX;
    printf("ld: %Le\n", ld);

    return 0;
}
