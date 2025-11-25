#include <stdio.h>
#include <string.h>

int main() {
    char nom_fichier[100];
    char phrase_recherche[200];
    char ligne[500];
    int numero_ligne = 0;
    int total_occurrences = 0;
    
    printf("Nom du fichier : ");
    scanf(" %[^\n]", nom_fichier);
    
    printf("Phrase a rechercher : ");
    scanf(" %[^\n]", phrase_recherche);

    FILE *fichier = fopen(nom_fichier, "r");
    
    if (fichier == NULL) {
        printf("ERROR: impossible ouvrir fichier '%s'\n", nom_fichier);
        return 1;
    }


    printf("Recherche de : \"%s\"\n", phrase_recherche);
    printf("Dans le fichier : %s\n\n", nom_fichier);
    
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        numero_ligne++;
        int occurrences_ligne = 0;
        
        char *position = ligne;
        while ((position = strstr(position, phrase_recherche)) != NULL) {
            occurrences_ligne++;
            total_occurrences++;
            position++; 
        }
        
        if (occurrences_ligne > 0) {
            printf("\nLigne %d : %d occurrence(s)\n", numero_ligne, occurrences_ligne);
            printf(" -> %s", ligne);
        }
    }

    printf("\nConclusion:\n");
    printf("Total d'occurrences : %d\n", total_occurrences);
    printf("Nombre de lignes analysees : %d\n", numero_ligne);

    fclose(fichier);
    
    return 0;
}