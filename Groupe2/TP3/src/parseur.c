#include "parseur.h"
#include <stdio.h>

// Parse une expression de la forme "A opérateur B"
Expression parser_parse(const char* input) {
    Expression expr;
    expr.valide = 0;  // Par défaut, non valide
    
    // Initialise le lexer
    Lexer lexer;
    lexer_init(&lexer, input);
    
    // Étape 1 : Lire le premier nombre (opérande 1)
    Token token1 = lexer_next_token(&lexer);
    
    if (token1.type == TOKEN_ERROR) {
        printf("Erreur : Caractère non autorisé dans l'expression\n");
        return expr;
    }
    
    if (token1.type != TOKEN_NUMBER) {
        printf("Erreur : Premier opérande manquant ou invalide\n");
        return expr;
    }
    expr.operande1 = token1.value;
    
    // Étape 2 : Lire l'opérateur
    Token token_op = lexer_next_token(&lexer);
    
    if (token_op.type == TOKEN_ERROR) {
        printf("Erreur : Caractère non autorisé dans l'expression\n");
        return expr;
    }
    
    if (token_op.type != TOKEN_OPERATOR) {
        printf("Erreur : Opérateur manquant ou invalide (attendu +, -, *, /)\n");
        return expr;
    }
    expr.operation = token_op.operator;
    
    // Étape 3 : Lire le deuxième nombre (opérande 2)
    Token token2 = lexer_next_token(&lexer);
    
    if (token2.type == TOKEN_ERROR) {
        printf("Erreur : Caractère non autorisé dans l'expression\n");
        return expr;
    }
    
    if (token2.type != TOKEN_NUMBER) {
        printf("Erreur : Deuxième opérande manquant ou invalide\n");
        return expr;
    }
    expr.operande2 = token2.value;
    
    // Étape 4 : Vérifier qu'il n'y a rien d'autre après
    Token token_end = lexer_next_token(&lexer);
    
    if (token_end.type == TOKEN_ERROR) {
        printf("Erreur : Caractère non autorisé à la fin de l'expression\n");
        return expr;
    }
    
    if (token_end.type != TOKEN_END) {
        printf("Erreur : Caractères supplémentaires après l'expression (format attendu: A opérateur B)\n");
        return expr;
    }
    
    // Tout est bon !
    expr.valide = 1;
    return expr;
}

// Affiche l'expression parsée
void parser_afficher_expression(Expression expr) {
    if (!expr.valide) {
        printf("Expression invalide\n");
        return;
    }
    
    printf("Représentation interne :\n");
    printf("  opération  : %c\n", expr.operation);
    printf("  opérande 1 : %g\n", expr.operande1);
    printf("  opérande 2 : %g\n", expr.operande2);
}