#include "parseur.h"
#include <stdio.h>

// Initialise le parseur
void parser_init(Parser* parser, Lexer* lexer) {
    parser->lexer = lexer;
    parser->has_error = 0;
    parser->current_token = lexer_next_token(lexer);
}

// Avance au token suivant
static void parser_advance(Parser* parser) {
    parser->current_token = lexer_next_token(parser->lexer);
}

// Vérifie s'il y a une erreur
int parser_has_error(Parser* parser) {
    return parser->has_error;
}

// Parse un nombre (facteur)
static double parser_parse_factor(Parser* parser) {
    if (parser->current_token.type == TOKEN_NUMBER) {
        double value = parser->current_token.value;
        parser_advance(parser);
        return value;
    }
    
    printf("Erreur : Nombre attendu\n");
    parser->has_error = 1;
    return 0.0;
}

// Parse la multiplication et la division (priorité haute)
static double parser_parse_term(Parser* parser) {
    double left = parser_parse_factor(parser);
    
    while (parser->current_token.type == TOKEN_MULTIPLY || 
           parser->current_token.type == TOKEN_DIVIDE) {
        
        TokenType op = parser->current_token.type;
        parser_advance(parser);
        double right = parser_parse_factor(parser);
        
        if (op == TOKEN_MULTIPLY) {
            left = left * right;
        } else {
            if (right == 0.0) {
                printf("Erreur : Division par zéro\n");
                parser->has_error = 1;
                return 0.0;
            }
            left = left / right;
        }
    }
    
    return left;
}

// Parse l'addition et la soustraction (priorité basse)
double parser_parse_expression(Parser* parser) {
    double left = parser_parse_term(parser);
    
    while (parser->current_token.type == TOKEN_PLUS || 
           parser->current_token.type == TOKEN_MINUS) {
        
        TokenType op = parser->current_token.type;
        parser_advance(parser);
        double right = parser_parse_term(parser);
        
        if (op == TOKEN_PLUS) {
            left = left + right;
        } else {
            left = left - right;
        }
    }
    
    // Vérifier qu'on a bien atteint la fin
    if (parser->current_token.type != TOKEN_END) {
        printf("Erreur : Caractères inattendus à la fin de l'expression\n");
        parser->has_error = 1;
    }
    
    return left;
}