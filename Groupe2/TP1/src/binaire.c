#include <stdio.h>

// Affiche la représentation binaire d'un entier non signé
void afficher_binaire(unsigned int n) {
    if (n > 1) {                  // Traite d'abord les bits de poids fort (récursif)
        afficher_binaire(n / 2);
    }
    printf("%d", n % 2);          // Affiche le bit courant
}

int main() {
    unsigned int valeurs[] = {0, 4096, 65536, 65535, 1024};
    int nb_valeurs = sizeof(valeurs) / sizeof(unsigned int); // Nombre d'éléments
        
    for (int i = 0; i < nb_valeurs; i++) {
        printf("Décimal: %8u ->  Binaire : ", valeurs[i]);
        afficher_binaire(valeurs[i]); // Affichage en binaire
        printf("\n");
    }
    
    return 0;
}
