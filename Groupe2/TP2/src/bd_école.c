#include <stdio.h>
#include <string.h>
#include "etudiant.h"

int main(){
    struct Etudiant etudiants[5];

    strcpy(etudiants[0].nom, "Thomas");
    strcpy(etudiants[0].prenom, "Alexis");
    strcpy(etudiants[0].adresse, "12 rue de l'example");
    
    etudiants[0].notes[0] = 15.5;
    etudiants[0].notes[1] = 16.0;
    etudiants[0].notes[2] = 14.5;

    for(int i = 1; i < 5; i++){
        printf("\n Etudiant %d \n", i + 1);
        
        printf("Nom: ");
        scanf("%s", etudiants[i].nom);
        
        printf("Prenom: ");
        scanf("%s", etudiants[i].prenom);
        
        printf("Adresse: ");
        scanf(" %[^\n]", etudiants[i].adresse);

        printf("Saisir 3 notes:\n");
        for(int j = 0; j < 3; j++){
            printf("  Note %d : ", j + 1);
            scanf("%f", &etudiants[i].notes[j]);
        }
    }

    for(int i = 0; i < 5; i++){
        printf("\n Etudiant %d \n", i + 1);
        printf("Nom     : %s\n", etudiants[i].nom);
        printf("Prenom  : %s\n", etudiants[i].prenom);
        printf("Adresse : %s\n", etudiants[i].adresse);
        printf("Notes   : ");
        
        for (int j = 0; j < 3; j++) {
            printf("%.2f ", etudiants[i].notes[j]);
        }
        printf("\n");
    }

    return 0;
}