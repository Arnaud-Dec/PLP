#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int count = 100;

typedef struct {
    int r, g, b, a;
} Couleur;

int sont_egales(Couleur c1, Couleur c2) {
    return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a);
}

int main() {
    srand(time(NULL));

    Couleur palette[count];
    int deja_traite[count];

    // Initialisation : couleurs aléatoires et marquage à 0
    for (int i = 0; i < count; i++) {
        palette[i].r = rand() % 256;
        palette[i].g = rand() % 256;
        palette[i].b = rand() % 256;
        palette[i].a = rand() % 256;
        deja_traite[i] = 0;
    }

    printf("| R\t| G\t| B\t| A\t| Occurrences |\n");

    for (int i = 0; i < count; i++) {

        if (deja_traite[i] == 1)
            continue;

        int compteur = 1;

        for (int j = i + 1; j < count; j++) {
            if (sont_egales(palette[i], palette[j])) {
                compteur++;
                deja_traite[j] = 1;
            }
        }

        // afficher TOUTES les couleurs distinctes
        printf("| %d\t| %d\t| %d\t| %d\t| %d |\n",
            palette[i].r, palette[i].g, palette[i].b, palette[i].a, compteur);
    }

    return 0;
}
