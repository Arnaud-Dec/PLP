#ifndef LEXER_H
#define LEXER_H

// Types de tokens possibles
typedef enum {
    TOKEN_NUMBER,      // Nombre (entier ou réel)
    TOKEN_PLUS,        // +
    TOKEN_MINUS,       // -
    TOKEN_MULTIPLY,    // *
    TOKEN_DIVIDE,      // /
    TOKEN_END,         // Fin de l'expression
    TOKEN_ERROR        // Erreur de syntaxe
} TokenType;

// Structure représentant un token
typedef struct {
    TokenType type;
    double value;      // Pour les nombres
} Token;

// Structure pour gérer l'état du lexer
typedef struct {
    const char* input;  // Chaîne d'entrée
    int position;       // Position actuelle dans la chaîne
} Lexer;

// Fonctions du lexer
void lexer_init(Lexer* lexer, const char* input);
Token lexer_next_token(Lexer* lexer);
Token lexer_peek_token(Lexer* lexer);  // Regarde le prochain token sans avancer

#endif