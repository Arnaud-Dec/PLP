/*
 * Fichier: operateurs.c
 * Objectif: Illustrer l'utilisation des opérateurs arithmétiques et de comparaison en C
 *           - Opérateurs arithmétiques : +, -, *, /, %
 *           - Opérateurs de comparaison : ==, >
 * Date: 06/11/2025
 * Auteur: Arnaud
*/
#include <stdio.h>

int main(){

    int a = 16;
    int b = 3;

    //Calculs :
    printf("resultat a+b: %d\n", a+b);
    printf("resultat a-b: %d\n", a-b);

    printf("resultat a*b: %d\n", a*b);
    printf("resultat a/b: %d\n", a/b);

    printf("resultat a modulo b: %d\n", a%b);

    //Comparaisons :
    printf("es que a = b: %d\n", a==b);
    printf("es que a > b: %d\n", a>b);

    return 0;
}

