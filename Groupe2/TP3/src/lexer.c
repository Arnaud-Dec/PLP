#include "lexer.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Initialise le lexer avec une chaîne d'entrée
void lexer_init(Lexer* lexer, const char* input) {
    lexer->input = input;
    lexer->position = 0;
}

// Ignore les espaces blancs
static void skip_whitespace(Lexer* lexer) {
    while (lexer->input[lexer->position] == ' ' || 
           lexer->input[lexer->position] == '\t' ||
           lexer->input[lexer->position] == '\n' ||
           lexer->input[lexer->position] == '\r') {
        lexer->position++;
    }
}

// Lit un nombre (entier ou réel)
static Token read_number(Lexer* lexer) {
    Token token;
    token.type = TOKEN_NUMBER;
    
    int start = lexer->position;
    int has_dot = 0;
    
    // Lit les chiffres et éventuellement un point décimal
    while (isdigit(lexer->input[lexer->position]) || 
           lexer->input[lexer->position] == '.') {
        
        if (lexer->input[lexer->position] == '.') {
            if (has_dot) {
                // Erreur : deux points décimaux
                token.type = TOKEN_ERROR;
                return token;
            }
            has_dot = 1;
        }
        lexer->position++;
    }
    
    // Convertit la sous-chaîne en nombre
    char buffer[100];
    int length = lexer->position - start;
    strncpy(buffer, &lexer->input[start], length);
    buffer[length] = '\0';
    
    token.value = atof(buffer);
    return token;
}

// Lit le prochain token
Token lexer_next_token(Lexer* lexer) {
    Token token;
    
    // Ignore les espaces
    skip_whitespace(lexer);
    
    // Vérifie la fin de la chaîne
    if (lexer->input[lexer->position] == '\0') {
        token.type = TOKEN_END;
        return token;
    }
    
    char current = lexer->input[lexer->position];
    
    // Si c'est un chiffre, lit un nombre
    if (isdigit(current)) {
        return read_number(lexer);
    }
    
    // Si c'est un opérateur
    switch(current) {
        case '+':
            token.type = TOKEN_PLUS;
            lexer->position++;
            return token;
        case '-':
            token.type = TOKEN_MINUS;
            lexer->position++;
            return token;
        case '*':
            token.type = TOKEN_MULTIPLY;
            lexer->position++;
            return token;
        case '/':
            token.type = TOKEN_DIVIDE;
            lexer->position++;
            return token;
    }
    
    // Caractère non reconnu = erreur
    token.type = TOKEN_ERROR;
    return token;
}

// Regarde le prochain token sans avancer
Token lexer_peek_token(Lexer* lexer) {
    int saved_position = lexer->position;
    Token token = lexer_next_token(lexer);
    lexer->position = saved_position;
    return token;
}