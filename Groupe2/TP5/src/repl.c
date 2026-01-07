/**
 * Nom du fichier : repl.c
 * Objectif       : Point d'entrée principal du Shell. Implémente la boucle REPL
 * (Read-Eval-Print Loop), gère les commandes système (echo, help, quit)
 * et orchestre l'appel aux modules de calcul et de variables.
 * Auteurs        : 1. Théo DEMARIA
 * 2. Arnaud DECOURT
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

#include "function.h"
#include "arithmetic.h"
#include "lexer.h"
#include "variable.h" 

const char* version = "1.0.1";
int continuer = 1;

// --- Fonctions Commandes Existantes ---

void afficher_version(char* commande, int fr) {
    printf("%s\n", version);
}

void afficher_aide(char* commande, int fr) {
    if (fr == 0) {
        printf("===== Help - Commandes disponibles =====\n");
        printf("x = 12             : Assign variable\n");
        printf("x                  : Display variable value\n");
        printf("calc x + 2         : Calculate expression\n");
        printf("(lambda x.x+1) 5   : Lambda function\n");
        printf("echo <txt>         : Print text\n");
        printf("version            : Show version\n");
        printf("quit               : Exit\n");
        printf("================\n");
    } else {
        printf("===== Aide - Commandes disponibles =====\n");
        printf("x = 12             : Assigner une variable\n");
        printf("x                  : Afficher la valeur d'une variable\n");
        printf("calculer x + 2     : Calculer une expression\n");
        printf("(lambda x.x+1) 5   : Fonction Lambda\n");
        printf("affiché <txt>      : Afficher un texte\n");
        printf("version            : Afficher la version\n");
        printf("quitter            : Quitter\n");
        printf("================\n");
    }
}

void traiter_date(char* commande, int fr) {
    time_t t = time(NULL);
    printf("%s", ctime(&t));
}

void traiter_echo(char* commande, int fr) {
    if (fr == 0) {
        printf("Echo: ");
        int debut = 5;
        if (strlen(commande) > debut) printf("%s\n", commande + debut);
        else printf("\n");
    }
    else {
        printf("Affiché: ");
        int debut = 9;
        if (strlen(commande) > debut) printf("%s\n", commande + debut);
        else printf("\n");
    }
}

void traiter_quit(char* commande, int fr) {
    printf(fr == 0 ? "Bye...\n" : "Arrêt...\n");
    continuer = 0;
}

// Fonction de calcul explicite (via commande "calc")
void traiter_calcul(char* commande, int fr) {
    char* expression;
    int decalage = (fr == 0) ? 5 : 9;
    if (strlen(commande) <= decalage) return;
    expression = commande + decalage;

    char postfix[1024];
    double resultat;
    
    // On vérifie si la conversion réussit avant de calculer
    if (infixToPostfix(expression, postfix)) {
        if (calculate(postfix, &resultat)) printf("%g\n", resultat);
        else printf("Erreur calcul\n");
    }
}

void normaliser_cmd(char* dest, const char* src) {
    int j = 0;
    int debut = 1;
    for (int i = 0; src[i] != '\0'; i++) {
        dest[j++] = src[i]; 
    }
    dest[j] = '\0';
}

// --- MAIN ---

int main() {
    var_init(); // Initialisation variables

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
    
    while (continuer) {
        printf("> ");
        char commande[1024];
        if (!fgets(commande, sizeof(commande), stdin)) break;
        commande[strcspn(commande, "\n")] = 0;
        if (strlen(commande) == 0) continue;

        int nb_cmd = sizeof(table_f) / sizeof(table_f[0]);
        int trouve = 0;
        
        char premier_mot[50];
        sscanf(commande, "%49s", premier_mot);

        for (int i = 0; i < nb_cmd; i++) {
            if (strcmp(premier_mot, table_f[i].name) == 0) {
                table_f[i].func(commande, 0);
                trouve = 1; break;
            }
            if (strcmp(premier_mot, table_f[i].name_fr) == 0) {
                table_f[i].func(commande, 1);
                trouve = 1; break;
            }
        }

        // --- LOGIQUE TP5 (Si commande inconnue) ---
        if (!trouve) {
            
            // 1. Affectation (x = 12)
            if (strchr(commande, '=') != NULL) {
                var_process_assignment(commande);
            }
            // 2. Lambda ((lambda x.x+1) 5)
            else if (strstr(commande, "(lambda")) {
                char expression_resolue[1024];
                if (resolve_lambda(commande, expression_resolue)) {
                    char postfix[1024];
                    double resultat;
                    if (infixToPostfix(expression_resolue, postfix)) {
                        if (calculate(postfix, &resultat)) printf("%g\n", resultat);
                    }
                }
            }
            // 3. Calcul Implicite ou Variable (x + 2, ou juste x)
            else {
                // PRIORITÉ 1: Est-ce juste le nom d'une variable ? (ex: "z")
                const char* val_simple = var_get_value(commande);
                if (val_simple) {
                    var_print(commande); // Affiche la variable proprement
                }
                // PRIORITÉ 2: Sinon, on essaie de calculer (ex: "x + 2")
                else {
                    char postfix[1024];
                    double resultat;
                    
                    if (infixToPostfix(commande, postfix)) {
                        if (calculate(postfix, &resultat)) {
                            printf("%g\n", resultat);
                        } else {
                            printf("Erreur de calcul (Opération invalide).\n");
                        }
                    }
                    // Si infixToPostfix échoue, l'erreur a déjà été affichée par arithmetic.c
                }
            }
        }
        printf("\n"); // Saut de ligne
    }

    var_free();
    return 0;
}