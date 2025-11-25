/*
 * Fichier : chaine.c
 * Objectif : Manipulation de chaînes de caractères en C sans utiliser les fonctions
 * standard de la librairie <string.h> (strlen, strcpy, strcat).
 * Le programme calcule la longueur, copie et concatène deux chaînes
 * saisies par l'utilisateur.
 * Auteur : Arnaud
 * Date : Novembre 2025
 */

#include <stdio.h> // Inclusion de la librairie standard pour les fonctions d'entrée/sortie (printf, scanf)

int main(){
    
    // Déclaration des tableaux de caractères (chaînes) avec une taille maximale de 50.
    char chaine1[50];
    char chaine2[50];
    char chaine3[50];

    // Demande et lecture de la première chaîne.
    // NOTE : scanf("%s", ...) lit jusqu'au premier espace ou saut de ligne.
    printf("Chaine 1 < 25 char:"); 
    scanf("%s", chaine1);

    // Demande et lecture de la seconde chaîne.
    printf("\nChaine 2 < 25 char:");
    scanf("%s", chaine2);

    // --- Calcul de la longueur de la chaîne 1 (similaire à strlen) ---
    int i = 0; // i est le compteur de caractères
    // Parcours de la chaîne jusqu'au caractère de fin de chaîne ('\0').
    while(chaine1[i] != '\0' ){
        i++;
    }

    // Affichage du résultat de la longueur. i contiendra la longueur.
    printf("\nLongeur de la chaine 1 = %d\n" , i);

    // --- Copie de la chaîne 1 dans la chaîne 3 (similaire à strcpy) ---
    int j = 0; // j est l'indice pour le parcours et la copie.
    while(chaine1[j] != '\0'){
        // Copie du caractère de chaine1 dans chaine3.
        chaine3[j] = chaine1[j];
        j++;
    }
    // Ajout du caractère de fin de chaîne ('\0') pour garantir que chaine3 est une chaîne valide.
    chaine3[j] = '\0'; // Ligne importante : Termine la nouvelle chaîne.
    printf("affichage de la chaine 3 (copie de la chaine 1) : %s\n", chaine3);

    // --- Concaténation de la chaîne 2 à la suite de la chaîne 1 (similaire à strcat) ---
    // i est déjà positionné sur l'indice du '\0' de chaine1 (grâce au premier calcul de longueur).
    int w = 0; // w est l'indice pour parcourir la chaîne 2.
    while(chaine2[w] != '\0'){
        // Ajout du caractère de chaine2 à la fin de chaine1.
        chaine1[i] = chaine2[w];
        i++; // Avance l'indice de fin de chaine1.
        w++; // Avance l'indice de chaine2.
    }
    // Ajout du caractère de fin de chaîne ('\0') à la fin de la nouvelle chaîne 1 concaténée.
    chaine1[i] = '\0'; // Ligne importante : Termine la chaîne concaténée.
    printf("Concaténation de chaine 1 et chaine 2 : %s\n" , chaine1);

    return 0; // Fin du programme sans erreur
}