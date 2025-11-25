/*
 * Fichier : couleurs.c
 * Objectif : Générer un tableau de 100 structures 'Couleur' (RGBA) aléatoires.
 * Le programme identifie ensuite les couleurs distinctes dans le tableau
 * et compte le nombre d'occurrences de chacune d'elles, affichant les résultats.
 * Auteur : [Votre Nom/Pseudo]
 * Date : Novembre 2025
 */

#include <stdio.h>  // Pour les fonctions d'entrée/sortie (printf)
#include <stdlib.h> // Pour les fonctions de génération de nombres aléatoires (rand, srand)
#include <time.h>   // Pour initialiser la graine aléatoire (time)

// Définition de la constante pour la taille du tableau de couleurs.
const int count = 100;

// --- Définition de la structure Couleur (Ligne importante : définition de la structure) ---
// La structure stocke les composantes Rouge (r), Vert (g), Bleu (b) et Alpha (a) d'une couleur.
typedef struct {
    int r, g, b, a;
} Couleur;

// Fonction utilitaire pour comparer si deux couleurs sont strictement identiques.
// Retourne 1 (vrai) si elles sont égales, 0 (faux) sinon.
int sont_egales(Couleur c1, Couleur c2) {
    return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a);
}

int main() {
    // Initialisation de la graine du générateur de nombres aléatoires basé sur l'heure actuelle.
    srand(time(NULL)); // Ligne importante : Initialisation de l'aléatoire.

    // Déclaration du tableau de 100 couleurs et d'un tableau de marquage.
    Couleur palette[count];
    // Ce tableau booléen (0 ou 1) sert à marquer les couleurs déjà comptées (pour éviter la redondance).
    int deja_traite[count];

    // --- Phase d'initialisation : Génération des couleurs aléatoires et initialisation du marquage ---
    for (int i = 0; i < count; i++) {
        // rand() % 256 génère un nombre entre 0 et 255 (valeurs typiques pour les composantes couleur).
        palette[i].r = rand() % 256;
        palette[i].g = rand() % 256;
        palette[i].b = rand() % 256;
        palette[i].a = rand() % 256;
        deja_traite[i] = 0; // Initialisation du drapeau à 0 (non traité).
    }

    // Affichage de l'en-tête du tableau des résultats.
    printf("--- Compte des couleurs distinctes ---\n");
    printf("| R\t| G\t| B\t| A\t| Occurrences |\n");
    printf("----------------------------------------\n");

    // --- Phase de comptage des occurrences ---
    for (int i = 0; i < count; i++) {

        // Si la couleur à l'indice 'i' a déjà été comptée (marquée à 1), on passe à la suivante.
        if (deja_traite[i] == 1)
            continue; // Passe à l'itération suivante de la boucle 'i'.

        // Initialisation du compteur à 1 (la couleur elle-même est la première occurrence).
        int compteur = 1;

        // Boucle interne : recherche des occurrences de la couleur 'palette[i]' dans le reste du tableau (j > i).
        for (int j = i + 1; j < count; j++) {
            // Utilisation de la fonction pour la comparaison.
            if (sont_egales(palette[i], palette[j])) { // Ligne importante : Vérification d'égalité.
                compteur++;
                // Marquer l'occurrence trouvée à l'indice 'j' comme traitée.
                deja_traite[j] = 1; // Ligne importante : Marquage de l'occurrence.
            }
        }

        // Affichage de la couleur distincte et de son nombre total d'occurrences.
        printf("| %d\t| %d\t| %d\t| %d\t| %d |\n",
            palette[i].r, palette[i].g, palette[i].b, palette[i].a, compteur);
    }
    printf("----------------------------------------\n");

    return 0;
}