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
            postfix[j++] = c;
            postfix[j++] = ' '; // séparateur
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

int main() {
    char infix[MAX] = "(3 + 4) * 5";
    char postfix[MAX];

    infixToPostfix(infix, postfix);
    printf("Postfix = %s\n", postfix);

    return 0;
}
