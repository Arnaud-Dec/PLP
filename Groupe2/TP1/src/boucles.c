#include <stdio.h>

// Affichage du motif avec des boucles for
void typeFor(int taille) {
    for (int i = 1; i <= taille; i++) {          // Parcourt chaque ligne
        for (int j = 1; j <= i; j++) {           // Parcourt chaque colonne de la ligne

            if (i == taille) {                   // Dernière ligne entièrement en *
                printf("* ");
            }
            else if (i <= 2) {                   // Les deux premières lignes en *
                printf("* ");
            }
            else {                               // Lignes intermédiaires
                if (j == 1 || j == i)            // Bords en *
                    printf("* ");
                else                              // Intérieur en #
                    printf("# ");
            }
        }
        printf("\n");                             // Nouvelle ligne
    }
}

// Même motif avec des boucles while
void typeWhile(const int taille) {
    int i = 1;
    while (i <= taille) {
        int j = 1;
        while (j <= i) {

            if (i == taille) {                    // Dernière ligne
                printf("* ");
            }
            else if (i <= 2) {                    // Deux premières lignes
                printf("* ");
            }
            else {                                // Lignes intermédiaires
                if (j == 1 || j == i)             // Bords
                    printf("* ");
                else
                    printf("# ");
            }
            j++;
        }
        printf("\n");
        i++;
    }
}

int main() {
    int taille;
    const int max = 100;

    // Saisie sécurisée de la taille
    do {
        printf("Entrez une taille (<%d) : ", max);
        scanf("%d", &taille);
    } while (taille >= max || taille <= 0);

    // Affichage avec les deux méthodes
    typeFor(taille);
    
    printf("\n");

    typeWhile(taille);

    return 0;
}
