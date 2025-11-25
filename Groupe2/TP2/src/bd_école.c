/*
 * Fichier : bd_école.c
 * Objectif : Gérer et manipuler les données de 5 étudiant.e.s en utilisant
 * une structure C (struct) pour organiser le nom, l'adresse et les notes.
 * Le programme initialise le premier étudiant et demande la saisie des 4 autres.
 * Auteur : [Votre Nom/Pseudo]
 * Date : Novembre 2025
 */

#include <stdio.h>    // Pour les fonctions d'entrée/sortie (printf, scanf)
#include <string.h>   // Pour les fonctions de manipulation de chaînes (strcpy)
#include "etudiant.h" // Fichier d'en-tête contenant la définition de 'struct Etudiant'

int main(){
    // Déclaration d'un tableau de 5 structures 'Etudiant'.
    struct Etudiant etudiants[5];

    // --- Initialisation manuelle du premier étudiant (Ligne importante) ---
    // Utilisation de strcpy car les chaînes sont des tableaux de caractères.
    strcpy(etudiants[0].nom, "Thomas");
    strcpy(etudiants[0].prenom, "Alexis");
    strcpy(etudiants[0].adresse, "12 rue de l'exemple");
    
    // Initialisation des notes du premier étudiant.
    etudiants[0].notes[0] = 15.5;
    etudiants[0].notes[1] = 16.0;
    etudiants[0].notes[2] = 14.5;

    // --- Boucle de saisie pour les 4 autres étudiant.e.s (de l'indice 1 à 4) ---
    for(int i = 1; i < 5; i++){
        printf("\n Étudiant %d \n", i + 1);
        
        // Saisie du nom et prénom : scanf("%s", ...) s'arrête au premier espace.
        printf("Nom: ");
        scanf("%s", etudiants[i].nom);
        
        printf("Prénom: ");
        scanf("%s", etudiants[i].prenom);
        
        // Saisie de l'adresse : utilisation de " %[^\n]" pour lire la ligne entière (incluant les espaces)
        // et éviter le problème du caractère '\n' laissé par le scanf précédent.
        printf("Adresse: ");
        scanf(" %[^\n]", etudiants[i].adresse); // Ligne importante pour la lecture de chaînes avec espaces

        // Saisie des 3 notes (flottants)
        printf("Saisir 3 notes:\n");
        for(int j = 0; j < 3; j++){
            printf("   Note %d : ", j + 1);
            // '&' est nécessaire pour lire un flottant (float) dans la variable.
            scanf("%f", &etudiants[i].notes[j]); 
        }
    }

    // --- Affichage des informations de tous les étudiant.e.s ---
    for(int i = 0; i < 5; i++){
        printf("\n Étudiant %d \n", i + 1);
        printf("Nom     : %s\n", etudiants[i].nom);
        printf("Prénom  : %s\n", etudiants[i].prenom);
        printf("Adresse : %s\n", etudiants[i].adresse);
        printf("Notes   : ");
        
        // Affichage des notes avec deux chiffres après la virgule (%.2f).
        for (int j = 0; j < 3; j++) {
            printf("%.2f ", etudiants[i].notes[j]);
        }
        printf("\n");
    }

    return 0; // Fin du programme
}