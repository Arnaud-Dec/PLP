/*
 * Fichier: variables.c
 * Objectif: Afficher les valeurs minimales et maximales des principaux types de données en C
 *           - Types entiers : char, short, int, long int, long long int (signés et non signés)
 *           - Types flottants : float, double, long double
 * Date: 06/11/2025
 * Auteur: Théo
*/
#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void) {
    // Types char
    char c = CHAR_MIN;                 // minimum char
    signed char sc = SCHAR_MIN;        // minimum signed char
    unsigned char uc = UCHAR_MAX;      // maximum unsigned char
    printf("c: %d, sc: %d, uc: %u\n", c, sc, uc);

    // Types short
    short s = SHRT_MIN;                // minimum short
    signed short ss = SHRT_MIN;        // minimum signed short
    unsigned short us = USHRT_MAX;     // maximum unsigned short
    printf("s: %d, ss: %d, us: %u\n", s, ss, us);

    // Types int
    int i = INT_MIN;                    // minimum int
    signed int si = INT_MIN;            // minimum signed int
    unsigned int ui = UINT_MAX;         // maximum unsigned int
    printf("i: %d, si: %d, ui: %u\n", i, si, ui);

    // Types long int
    long int li = LONG_MIN;             // minimum long
    signed long int sli = LONG_MIN;     // minimum signed long
    unsigned long int uli = ULONG_MAX;  // maximum unsigned long
    printf("li: %ld, sli: %ld, uli: %lu\n", li, sli, uli);

    // Types long long int
    long long int lli = LLONG_MIN;              // minimum long long
    signed long long int slli = LLONG_MIN;      // minimum signed long long
    unsigned long long int ulli = ULLONG_MAX;   // maximum unsigned long long
    printf("lli: %lld, slli: %lld, ulli: %llu\n", lli, slli, ulli);

    // Types flottants
    float f = -FLT_MAX;               // minimum float (négatif)
    printf("f: %e\n", f);

    double d = -DBL_MAX;              // minimum double (négatif)
    printf("d: %e\n", d);

    long double ld = -LDBL_MAX;       // minimum long double (négatif)
    printf("ld: %Le\n", ld);

    return 0; // Fin du programme
}
