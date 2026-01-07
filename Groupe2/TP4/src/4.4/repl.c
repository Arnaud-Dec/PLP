/**
 * Nom du fichier : repl.c
 * Objectif       : Boucle principale de l'interpréteur (TP4).
 * Gère la commande 'calc' pour évaluer des expressions mathématiques
 * complexes (parenthèses, priorités) via le module arithmetic.
 * Auteurs        : 1. Théo DEMARIA
 * 2. Arnaud DECOURT
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "function.h"
#include "arithmetic.h"
#include "lexer.h"

/**
 * Programme qui simule un interpréteur de commandes simple.
 * Il lit les commandes utilisateur et les traite en fonction de leur contenu.
 */

const char* version = "1.0.1";
int continuer = 1; // Variable pour contrôler la boucle principale


void afficher_version(char* commande, int fr) {
    printf("%s\n", version);
}

void afficher_aide(char* commande, int fr) {
    if (fr == 0) {
        printf("===== Help - Commandes disponibles =====\n");
        printf("help        : Affiche cette aide\n");
        printf("version     : Affiche la version du programme\n");
        printf("date        : Affiche la date et l'heure actuelles\n");
        printf("echo <txt>  : Affiche le texte suivant la commande\n");
        printf("calc <expr> : Calcule une expression (ex: calc 2 + 3)\n");
        printf("quit        : Quitte le programme\n");
        printf("========================================\n");
    }
    else {
        printf("===== Aide - Commandes disponibles =====\n");
        printf("aide        : Affiche cette aide\n");
        printf("version     : Affiche la version du programme\n");
        printf("date        : Affiche la date et l'heure actuelles\n");
        printf("echo <txt>  : Affiche le texte suivant la commande\n");
        printf("calc <expr> : Calcule une expression (ex: calc 2 + 3)\n");
        printf("quitter     : Quitte le programme\n");
        printf("========================================\n");
    }
}

void traiter_date(char* commande, int fr) {
    time_t t = time(NULL);
    printf("%s", ctime(&t));
}

void traiter_echo(char* commande, int fr) {
    if (fr == 0) {
        // Traite la commande "echo" pour afficher du texte
        printf("Echo: ");
        // Imprime la chaîne
        for (int i = 5; commande[i] != '\0'; i++) {
            printf("%c", commande[i]);
        }
        printf("\n");
    }
    else {
        printf("Affiché: ");
        // Imprime la chaîne
        for (int i = 9; commande[i] != '\0'; i++) {
            printf("%c", commande[i]);
        }
        printf("\n");
    }
}

void traiter_quit(char* commande, int fr) {
    if (fr == 0) {
        printf("Stop...\n");
    }
    else {
        printf("Arrêt...\n");
    }
    continuer = 0;
}

// NOUVELLE FONCTION : Traiter les calculs mathématiques
void traiter_calcul(char* commande, int fr) {
    // Extraire l'expression après "calc " ou "calculer "
    char* expression;
    
    if (fr == 0) {
        // Commande "calc"
        if (strlen(commande) <= 5) {
            printf("Erreur : Veuillez fournir une expression (ex: calc 2 + 3)\n");
            return;
        }
        expression = commande + 5; // Sauter "calc "
    }
    else {
        // Commande "calculer"
        if (strlen(commande) <= 9) {
            printf("Erreur : Veuillez fournir une expression (ex: calculer 2 + 3)\n");
            return;
        }
        expression = commande + 9; // Sauter "calculer "
    }
    
    char postfix[1024];
    double resultat;

    // 1. Conversion Infixe -> Postfixe
    infixToPostfix(expression, postfix);

    // 2. Évaluation
    if (calculate(postfix, &resultat)) {
        printf("%g\n", resultat);
    } else {
        printf("Erreur lors du calcul (Syntaxe ou Div/0)\n");
    }
}

void normaliser_cmd(char* dest, const char* src) {
    int j = 0;
    int debut = 1;

    for (int i = 0; src[i] != '\0' || src[i] == 32; i++) {
        unsigned char c = src[i];

        if (c < 128) {
            if (debut && c == ' ') continue;
            debut = 0;
            if (c >= 'A' && c <= 'Z')
                dest[j++] = c + 32;
            else
                dest[j++] = c;
        }
        else {
            dest[j++] = c;
        }
    }
    dest[j] = '\0';
}

int main()
{
    struct function table_f[] = {
        {"echo", "affiché", traiter_echo},
        {"quit", "quitter", traiter_quit},
        {"version", "version", afficher_version},
        {"help", "aide", afficher_aide},
        {"date", "date", traiter_date},
        {"calc", "calculer", traiter_calcul}
    };
    
    printf("=== Interpréteur de commandes ===\n");
    printf("Tapez 'help' ou 'aide' pour voir les commandes disponibles\n\n");
    
    // Boucle principale qui lit et traite les commandes utilisateur
    while (continuer)
    {
        printf("> "); // Affiche le prompt de commande

        // Buffer pour stocker la commande utilisateur
        char commande[1024];
        // Lit la commande utilisateur et la stocke dans le buffer
        fgets(commande, sizeof(commande), stdin);

        // Enlève le caractère de fin de ligne ajouté par fgets
        commande[strcspn(commande, "\n")] = 0;

        int nb_cmd = sizeof(table_f) / sizeof(table_f[0]);
        int find_f = 0;
        int fr;

        char cmd[1024];
        normaliser_cmd(cmd, commande);

        for (int i = 0; i < nb_cmd; i++) {
            fr = 0;
            int len_en = strlen(table_f[i].name);
            int len_fr = strlen(table_f[i].name_fr);
            // Vérification stricte ANGLAIS 
            if (strncmp(cmd, table_f[i].name, len_en) == 0 && 
               (cmd[len_en] == ' ' || cmd[len_en] == '\0')) {
                
                table_f[i].func(commande, fr);
                find_f = 1;
                break;
            }
            // Vérification stricte FRANÇAIS
            else if (strncmp(cmd, table_f[i].name_fr, len_fr) == 0 && 
                    (cmd[len_fr] == ' ' || cmd[len_fr] == '\0')) {
                fr = 1;
                table_f[i].func(commande, fr);
                find_f = 1;
                break;
            }
        }

        if (!find_f) {
            printf("Commande non reconnue. Essayer help ou aide pour connaître toutes les commandes disponibles.\n");
        }

        printf("\n"); // Saut de ligne après la sortie
    }

    return 0;
}
