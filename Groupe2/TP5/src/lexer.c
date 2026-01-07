/**
 * Nom du fichier : lexer.c
 * Objectif       : Analyseur lexical. Découpe la chaîne d'entrée brute en une suite
 * de tokens intelligibles (nombres, opérateurs, parenthèses, variables)
 * pour être traités par le parseur mathématique.
 * Auteurs        : 1. Théo DEMARIA
 * 2. Arnaud DECOURT
 */

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

// Vérifie si un caractère est un opérateur valide
static int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
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
    if (length >= 100) length = 99; // Sécurité buffer
    strncpy(buffer, &lexer->input[start], length);
    buffer[length] = '\0';
    
    token.value = atof(buffer);
    return token;
}

// --- FONCTION AJOUTÉE (Celle qui manquait) ---
// Lit un identifiant (nom de variable comme x, toto, pi...)
static Token read_identifier(Lexer* lexer) {
    Token token;
    token.type = TOKEN_IDENTIFIER;
    int i = 0;
    
    // On lit tant que ce n'est pas un espace, un opérateur ou une parenthèse
    while (lexer->input[lexer->position] != '\0' && 
           !is_operator(lexer->input[lexer->position]) && 
           !isspace(lexer->input[lexer->position]) &&
           lexer->input[lexer->position] != '(' &&
           lexer->input[lexer->position] != ')') {
        
        // On remplit le buffer du nom (limité à 49 caractères)
        if (i < 49) {
            token.identifier[i++] = lexer->input[lexer->position];
        }
        lexer->position++;
    }
    token.identifier[i] = '\0'; // Fin de chaîne
    return token;
}
// ---------------------------------------------

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
    if (isdigit(current) || current == '.') {
        return read_number(lexer);
    }
    
    // Si c'est un opérateur
    if (is_operator(current)) {
        token.type = TOKEN_OPERATOR;
        token.operator = current;
        lexer->position++;
        return token;
    }

    if (current == '(') {
        token.type = TOKEN_LPAREN;
        token.operator = '(';
        lexer->position++;
        return token;
    }
    if (current == ')') {
        token.type = TOKEN_RPAREN;
        token.operator = ')';
        lexer->position++;
        return token;
    }
    
    // Si rien de tout ça, c'est un identifiant (variable)
    return read_identifier(lexer);
}