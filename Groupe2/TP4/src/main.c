/**
 * Nom du fichier : main.c (Version TP4 - Calculatrice)
 * Objectif       : Programme autonome testant la logique mathématique du TP4.
 * Regroupe dans un seul fichier :
 * - La conversion d'expressions Infixe vers Postfixe (Shunting-yard).
 * - L'évaluation des expressions Postfixées (RPN).
 * - Le main pour lire et traiter une expression utilisateur.
 * Auteurs        : 1. Théo DEMARIA
 * 2. Arnaud DECOURT
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Fonction pour donner la priorité des opérateurs
int precedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
    }
    return 0;
}

// Fonction de conversion infix -> postfix
void infixToPostfix(const char *infix, char *postfix) {
    char stack[MAX];
    int top = -1;          // sommet de la pile
    int j = 0;             // index dans la sortie

    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];

        // Ignorer les espaces
        if (c == ' ') continue;

        // Si c'est un chiffre → on l'ajoute à la sortie
        if (isdigit(c)) {
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i];
                i++;
            }
            postfix[j++] = ' '; // séparateur
            i--;
        }

        else if (c == '(') {
            stack[++top] = c;
        }

        else if (c == ')') {
            while (stack[top] != '(') {
                postfix[j++] = stack[top--];
                postfix[j++] = ' ';
            }
            top--;
        }

        // Si c'est un opérateur
        else if (c == '+' || c == '-' || c == '*' || c == '/') {

            // Dépiler tant que la pile n'est pas vide
            // et que l'opérateur au sommet a une priorité >=
            while (top >= 0 && precedence(stack[top]) >= precedence(c)) {
                postfix[j++] = stack[top--];
                postfix[j++] = ' ';
            }

            // Empiler l'opérateur courant
            stack[++top] = c;
        }
    }

    // Dépiler les opérateurs restants
    while (top >= 0) {
        postfix[j++] = stack[top--];
        postfix[j++] = ' ';
    }

    postfix[j] = '\0';
}

void calculate(const char* expr, int* result) {
    int stack[MAX];
    int top = -1;

    int i = 0;

    while (expr[i] != '\0') {
        if (expr[i] == ' ') {
            i++;
            continue;
        }

        if (isdigit(expr[i])) {
            int num = 0;

            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }

            stack[++top] = num;
            continue;
        }

        char op = expr[i];
        int b = stack[top--];
        int a = stack[top--];

        int val = 0;
        switch (op) {
            case '+': val = a + b; break;
            case '-': val = a - b; break;
            case '*': val = a * b; break;
            case '/': val = a / b; break;
        }

        stack[++top] = val;
        i++;
    }

    *result = stack[top];
}


int main() {
    char infix[MAX];

    printf("> ");
    fgets(infix, MAX, stdin);

    char postfix[MAX];
    infixToPostfix(infix, postfix);
    printf("Postfix = %s\n", postfix);

    int res;
    calculate(postfix, &res);
    printf("Resultat: %d\n", res);

    return 0;
}
