/*
 * Fichier: sizeof_types.c
 * Objectif: Afficher la taille (en octets) des principaux types de données en C
 *           - char, signed char, unsigned char
 *           - short, unsigned short
 *           - int, unsigned int
 *           - long int, unsigned long int, long long int
 *           - float, double, long double
 * Date: 06/11/2025
 * Auteur: Arnaud
*/
#include <stdio.h>

int main(){

    // valeurs char, signed char, unsigned char
    printf("valeur de char %lu\n", sizeof(char));
    printf("valeur de signed char %lu\n", sizeof(signed char));
    printf("valeur de unsigned char %lu\n", sizeof(unsigned char));

    // valeurs short, unsigned short
    printf("valeur de short %lu\n", sizeof(short));
    printf("valeur de unsigned short %lu\n", sizeof(unsigned short));

    //valeurs int, unsigned int
    printf("valeur de int %lu\n", sizeof(int));
    printf("valeur de unsigned int %lu\n", sizeof(unsigned int));

    //valeurs long int, unsigned long int
    printf("valeur de long int %lu\n", sizeof(long int));
    printf("valeur de unsigned long int %lu\n", sizeof(unsigned long int));

    //valeur de long
    printf("valeur de long long int %lu\n", sizeof(long long int));

    //valeur de float
    printf("valeur de float %lu\n", sizeof(float));

    //valeur de double
    printf("valeur de double %lu\n", sizeof(double));

    //valeur de long double
    printf("valeur de long double %lu\n", sizeof(long double));

    return 0;
}