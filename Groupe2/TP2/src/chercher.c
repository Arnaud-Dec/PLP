/*
 * Fichier : chercher.c
 * Objectif : Rechercher si une phrase donnée est présente dans un tableau
 * prédéfini de 10 phrases. L'objectif principal est de réaliser la comparaison
 * de chaînes (fonction sont_identiques) sans utiliser les fonctions
 * standards comme strcmp, comme l'exige l'exercice.
 * Auteur : [Votre Nom/Pseudo]
 * Date : Novembre 2025
 */

#include <stdio.h> // Pour les fonctions d'entrée/sortie (printf)

// --- Fonction de comparaison de chaînes personnalisée (Ligne importante) ---
// Similaire à strcmp, mais retourne 1 si les chaînes sont identiques, 0 sinon.
// Utilise des pointeurs constants pour indiquer que les chaînes ne seront pas modifiées.
int sont_identiques(const char *chaine1, const char *chaine2) {
    int i = 0;

    // Boucle de comparaison caractère par caractère tant qu'on n'atteint pas le '\0'
    // sur L'UNE OU L'AUTRE des deux chaînes.
    while (chaine1[i] != '\0' && chaine2[i] != '\0') {
        // Si les caractères sont différents, les chaînes ne sont pas identiques.
        if (chaine1[i] != chaine2[i]) {
            return 0; // Retourne 0 immédiatement (non identique).
        }
        i++;
    }

    // Après la boucle, pour que les chaînes soient IDENTIQUES, il faut que
    // les deux aient atteint leur caractère de fin de chaîne ('\0') en même temps.
    if (chaine1[i] == '\0' && chaine2[i] == '\0') {
        return 1; // Retourne 1 (identique).
    }

    // Si seulement une des deux chaînes s'est terminée (ex: "mot" vs "mot.")
    // ou si on est sorti pour une autre raison, elles ne sont pas identiques.
    return 0;
}

int main() {
    // Tableau de 10 pointeurs vers des chaînes de caractères (phrases).
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

    // La phrase à rechercher dans le tableau.
    const char *recherche = "La programmation en C est amusante.";

    int trouve = 0; // Drapeau booléen (0 = faux, 1 = vrai) pour indiquer si la phrase est trouvée.

    // --- Boucle de recherche dans le tableau ---
    for (int i = 0; i < 10; i++) {
        // Appel de la fonction de comparaison personnalisée.
        if (sont_identiques(phrases[i], recherche)) {
            trouve = 1; // La phrase a été trouvée.
            break;      // Sortir de la boucle dès qu'une correspondance est trouvée.
        }
    }

    // Affichage du résultat final.
    if (trouve) {
        printf("Phrase trouvée.\n");
    } else {
        printf("Phrase non trouvée.\n");
    }

    return 0; // Fin du programme.
}