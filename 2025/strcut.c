#include <stdio.h>
#include "eleve.h"

void demande_user(){
    struct eleve nouveau;

    printf("prenom : \n");
    scanf("%s", nouveau.prenom);

    printf("nom : \n");
    scanf("%s", nouveau.nom);

    printf("ville : \n");
    scanf("%s", nouveau.ville);

    printf("Eleve : %s %s %s \n", nouveau.nom, nouveau.prenom, nouveau.ville);
}


int main() {
    struct eleve kevin = { "Dupont" , "Kevin" , "Villeurbanne"};

    printf("Eleve : %s %s %s\n" , kevin.nom , kevin.prenom , kevin.ville);

    demande_user();
    return 0; 
}
