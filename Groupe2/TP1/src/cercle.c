/*
 * Fichier: cercle.c
 * Objectif: Calculer et afficher l'aire et le périmètre d'un cercle à partir de son rayon
 * Date: 06/11/2025
 * Auteur: Théo
*/
#include <stdio.h>

int main() {
    const float PI = 3.141592;      // π
    float rayon;

    scanf("%f", &rayon);            // lecture du rayon

    const float aire = PI * rayon * rayon;       // aire du cercle
    const float perimetre = 2 * PI * rayon;     // périmètre du cercle

    printf("aire: %f, perimetre: %f\n", aire, perimetre);

    return 0;
}
