#ifndef PARSEUR_H
#define PARSEUR_H

#include "lexer.h"

// Structure pour le parseur
typedef struct {
    Lexer* lexer;
    Token current_token;
    int has_error;
} Parser;

// Fonctions du parseur
void parser_init(Parser* parser, Lexer* lexer);
double parser_parse_expression(Parser* parser);
int parser_has_error(Parser* parser);

#endif