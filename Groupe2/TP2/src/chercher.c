#include <stdio.h>

int sont_identiques(const char *chaine1, const char *chaine2) {
    int i = 0;

    while (chaine1[i] != '\0' && chaine2[i] != '\0') {
        if (chaine1[i] != chaine2[i]) {
            return 0;
        }
        i++;
    }

    if (chaine1[i] == '\0' && chaine2[i] == '\0') {
        return 1;
    }

    return 0;
}

int main() {
    const char *phrases[10] = {
        "Bonjour, comment ça va ?",
        "Le temps est magnifique aujourd'hui.",
        "C'est une belle journée.",
        "La programmation en C est amusante.",
        "Les tableaux en C sont puissants.",
        "Les pointeurs en C peuvent être déroutants.",
        "Il fait beau dehors.",
        "La recherche dans un tableau est intéressante.",
        "Les structures de données sont importantes.",
        "Programmer en C, c'est génial."
    };

    const char *recherche = "La programmation en C est amusante.";

    int trouve = 0;

    for (int i = 0; i < 10; i++) {
        if (sont_identiques(phrases[i], recherche)) {
            trouve = 1;
            break;
        }
    }

    if (trouve) {
        printf("Phrase trouvée.\n");
    } else {
        printf("Phrase non trouvée.\n");
    }

    return 0;
}