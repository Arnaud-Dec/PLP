/**
 * Nom du fichier : arithmetic.c
 * Objectif       : Moteur de calcul et parsing. Gère :
 * - L'algorithme Shunting-yard (gestion priorités opératoires).
 * - L'évaluation des expressions postfixées.
 * - La substitution textuelle pour les expressions Lambda.
 * Auteurs        : 1. Théo DEMARIA
 * 2. Arnaud DECOURT
 */

#include "arithmetic.h"
#include "lexer.h"
#include "variable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STACK 200

// Priorité des opérateurs
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Gestion des Lambdas : (lambda x.expr) arg
int resolve_lambda(const char* input, char* output) {
    // 1. Vérification de la syntaxe de base
    const char* lambda_pos = strstr(input, "(lambda");
    if (!lambda_pos) return 0;

    const char* dot = strchr(lambda_pos, '.');
    const char* rparen = strrchr(lambda_pos, ')');
    if (!dot || !rparen || rparen < dot) return 0;

    // 2. Extraire le corps de la fonction (ce qu'il y a après le point)
    char body[256];
    int len_body = rparen - (dot + 1);
    strncpy(body, dot + 1, len_body);
    body[len_body] = '\0';

    // 3. Extraire l'argument (ce qu'il y a après la parenthèse fermante)
    const char* arg_ptr = rparen + 1;
    while (*arg_ptr == ' ') arg_ptr++; // Ignorer les espaces
    
    char arg_val[256];
    // Si c'est un nombre, on le copie tel quel
    if (isdigit(*arg_ptr) || (*arg_ptr == '-' && isdigit(*(arg_ptr+1)))) {
        int k = 0;
        while(arg_ptr[k] && !isspace(arg_ptr[k])) {
            arg_val[k] = arg_ptr[k];
            k++;
        }
        arg_val[k] = '\0';
    } else {
        // Si c'est une variable, on va chercher sa valeur dans la table des symboles
        char var_name[50];
        int k = 0;
        while(arg_ptr[k] && !isspace(arg_ptr[k])) {
            var_name[k] = arg_ptr[k];
            k++;
        }
        var_name[k] = '\0';

        const char* val = var_get_value(var_name); // <--- Appel au module variable
        if (!val) {
            printf("`Erreur : la variable '%s' n'est pas définie\n", var_name);
            return 0;
        }
        strcpy(arg_val, val);
    }

    // 4. Substitution : Remplacer toutes les occurrences de 'x' par la valeur de l'argument
    int j = 0;
    for (int i = 0; body[i] != '\0'; i++) {
        if (body[i] == 'x') { // Simplification TP: la variable locale est toujours 'x'
            strcpy(&output[j], arg_val);
            j += strlen(arg_val);
        } else {
            output[j++] = body[i];
        }
    }
    output[j] = '\0';
    return 1;
}

// Change void en int
int infixToPostfix(const char *infix, char *postfix) {
    Lexer lexer;
    lexer_init(&lexer, infix);
    Token token;
    char stack[MAX_STACK];
    int top = -1, j = 0;
    int error = 0; // Pour détecter les erreurs

    while ((token = lexer_next_token(&lexer)).type != TOKEN_END) {
        if (token.type == TOKEN_NUMBER) {
            j += sprintf(&postfix[j], "%g ", token.value);
        }
        else if (token.type == TOKEN_IDENTIFIER) {
            const char* val = var_get_value(token.identifier);
            if (val) {
                j += sprintf(&postfix[j], "%s ", val);
            } else {
                // ERREUR DETECTÉE
                printf("Erreur : la variable '%s' n'est pas définie\n", token.identifier);
                return 0; // On arrête tout de suite, on renvoie ECHEC
            }
        }
        else if (token.type == TOKEN_LPAREN) stack[++top] = '(';
        else if (token.type == TOKEN_RPAREN) {
            while (top >= 0 && stack[top] != '(') {
                postfix[j++] = stack[top--]; postfix[j++] = ' ';
            }
            if (top >= 0) top--;
        }
        else if (token.type == TOKEN_OPERATOR) {
            while (top >= 0 && stack[top] != '(' && precedence(stack[top]) >= precedence(token.operator)) {
                postfix[j++] = stack[top--]; postfix[j++] = ' ';
            }
            stack[++top] = token.operator;
        }
        else if (token.type == TOKEN_ERROR) {
             printf("Erreur de syntaxe : caractère inconnu\n");
             return 0;
        }
    }
    while (top >= 0) { postfix[j++] = stack[top--]; postfix[j++] = ' '; }
    postfix[j] = '\0';
    return 1; // SUCCÈS
}

int calculate(const char* expr, double* result) {
    double stack[MAX_STACK];
    int top = -1;
    
    // Pour lire la chaîne postfix, on ne peut pas utiliser le lexer tel quel
    // car le format "3 4 +" est différent. On fait une lecture simple.
    
    // Copie locale pour utiliser strtok (qui modifie la chaîne)
    char buffer[1024];
    strncpy(buffer, expr, 1024);
    
    char* token = strtok(buffer, " ");
    
    while (token != NULL) {
        // Si c'est un nombre (ou un nombre négatif)
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            stack[++top] = atof(token);
        }
        // Sinon c'est un opérateur
        else {
            if (top < 1) return 0; // Erreur structure
            double b = stack[top--];
            double a = stack[top--];
            double val = 0;
            
            switch (token[0]) {
                case '+': val = a + b; break;
                case '-': val = a - b; break;
                case '*': val = a * b; break;
                case '/': 
                    if (b == 0) { printf("Erreur: Div / 0\n"); return 0; }
                    val = a / b; 
                    break;
            }
            stack[++top] = val;
        }
        token = strtok(NULL, " ");
    }
    
    if (top == 0) {
        *result = stack[top];
        return 1;
    }
    return 0;
}