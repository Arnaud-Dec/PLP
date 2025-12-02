#ifndef PARSEUR_H
#define PARSEUR_H

#include "lexer.h"

// Structure représentant une expression simple (A opérateur B)
typedef struct {
    double operande1;    // Premier nombre (A)
    char operation;      // Opérateur (+, -, *, /)
    double operande2;    // Deuxième nombre (B)
    int valide;          // 1 si l'expression est valide, 0 sinon
} Expression;

// Fonction principale du parseur
Expression parser_parse(const char* input);

// Fonction pour afficher l'expression (utile pour déboguer)
void parser_afficher_expression(Expression expr);

#endif