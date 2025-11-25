/*
 * Fichier : phrases.c
 * Objectif : Rechercher une phrase donnée par l'utilisateur dans un fichier texte
 * spécifié, ligne par ligne. Le programme compte et affiche le nombre
 * d'occurrences de la phrase par ligne, ainsi que le total général.
 * Auteur : [Votre Nom/Pseudo]
 * Date : Novembre 2025
 */

#include <stdio.h>  // Pour les fonctions d'entrée/sortie (printf, fopen, fgets, fclose)
#include <string.h> // Pour la manipulation de chaînes (strstr)

int main() {
    // Déclaration des tableaux de caractères pour les saisies et la lecture du fichier.
    char nom_fichier[100];
    char phrase_recherche[200];
    char ligne[500];
    // Variables de comptage.
    int numero_ligne = 0;       // Compteur de lignes lues.
    int total_occurrences = 0;  // Compteur total d'occurrences trouvées.
    
    // --- Saisie du nom du fichier et de la phrase à rechercher ---
    printf("Nom du fichier : ");
    // Lecture de la ligne complète (incluant les espaces) pour le nom du fichier.
    scanf(" %[^\n]", nom_fichier); 
    
    printf("Phrase a rechercher : ");
    // Lecture de la ligne complète pour la phrase à rechercher.
    scanf(" %[^\n]", phrase_recherche);

    // --- Ouverture du fichier en mode lecture ("r") ---
    FILE *fichier = fopen(nom_fichier, "r"); // Ligne importante : Ouverture du flux de fichier.
    
    // Vérification d'erreur : Si fopen retourne NULL, l'ouverture a échoué.
    if (fichier == NULL) {
        printf("ERROR: impossible ouvrir fichier '%s'\n", nom_fichier);
        return 1; // Retourne un code d'erreur non nul.
    }

    // Affichage des informations de la recherche.
    printf("Recherche de : \"%s\"\n", phrase_recherche);
    printf("Dans le fichier : %s\n\n", nom_fichier);
    
    // --- Boucle de lecture du fichier ligne par ligne ---
    // fgets lit au maximum sizeof(ligne) - 1 caractères ou jusqu'à un '\n'.
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) { // Ligne importante : Lecture ligne par ligne.
        numero_ligne++;
        int occurrences_ligne = 0;
        
        // Pointeur pour parcourir la ligne après chaque occurrence trouvée.
        char *position = ligne;
        
        // --- Boucle de recherche d'occurrences dans la ligne actuelle ---
        // strstr() cherche la première occurrence de 'phrase_recherche' dans 'position'.
        // Tant qu'une occurrence est trouvée (position est non-NULL)...
        while ((position = strstr(position, phrase_recherche)) != NULL) { // Ligne importante : Fonction de recherche (strstr).
            occurrences_ligne++;
            total_occurrences++;
            // Avancer le pointeur d'un caractère pour trouver des occurrences qui se chevauchent.
            // Si on avançait de strlen(phrase_recherche), on ignorerait les chevauchements.
            position++; 
        }
        
        // Affichage des résultats pour la ligne si au moins une occurrence a été trouvée.
        if (occurrences_ligne > 0) {
            printf("\nLigne %d : %d occurrence(s)\n", numero_ligne, occurrences_ligne);
            printf(" -> %s", ligne); // Afficher la ligne elle-même.
        }
    }

    // --- Affichage des résultats finaux ---
    printf("\nConclusion:\n");
    printf("Total d'occurrences : %d\n", total_occurrences);
    printf("Nombre de lignes analysees : %d\n", numero_ligne);

    // Fermeture du fichier
    fclose(fichier); // Ligne importante : Fermeture du flux de fichier.
    
    return 0;
}