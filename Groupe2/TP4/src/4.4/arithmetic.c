#include "arithmetic.h"
#include "lexer.h"
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

void infixToPostfix(const char *infix, char *postfix) {
    Lexer lexer;
    lexer_init(&lexer, infix);
    Token token;

    char stack[MAX_STACK]; // Pile d'opérateurs
    int top = -1;
    int j = 0; // Index pour la chaîne postfix (sortie)

    while ((token = lexer_next_token(&lexer)).type != TOKEN_END) {
        
        if (token.type == TOKEN_NUMBER) {
            // On écrit le nombre suivi d'un espace dans la sortie
            j += sprintf(&postfix[j], "%g ", token.value);
        }
        else if (token.type == TOKEN_LPAREN) {
            stack[++top] = '(';
        }
        else if (token.type == TOKEN_RPAREN) {
            while (top >= 0 && stack[top] != '(') {
                postfix[j++] = stack[top--];
                postfix[j++] = ' ';
            }
            if (top >= 0 && stack[top] == '(') {
                top--; // On enlève la parenthèse ouvrante
            }
        }
        else if (token.type == TOKEN_OPERATOR) {
            while (top >= 0 && stack[top] != '(' && 
                   precedence(stack[top]) >= precedence(token.operator)) {
                postfix[j++] = stack[top--];
                postfix[j++] = ' ';
            }
            stack[++top] = token.operator;
        }
    }

    // Vider la pile restante
    while (top >= 0) {
        postfix[j++] = stack[top--];
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
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