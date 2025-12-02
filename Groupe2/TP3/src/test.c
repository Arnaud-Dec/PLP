#include <stdio.h>
#include "lexer.h"
#include "parseur.h"

void test_expression(const char* expr_str) {
    printf("========================================\n");
    printf("Test: \"%s\"\n", expr_str);
    printf("----------------------------------------\n");
    
    Expression expr = parser_parse(expr_str);
    parser_afficher_expression(expr);
    printf("\n");
}

int main() {
    printf("=== Test du Lexer et du Parseur ===\n\n");
    
    // Tests valides
    printf("TESTS VALIDES :\n\n");
    test_expression("2 + 3");
    test_expression("10 - 4");
    test_expression("5 * 6");
    test_expression("20 / 4");
    test_expression("1.5 + 2.5");
    test_expression("10.0 / 4.0");
    test_expression("3.14 * 2");
    
    // Tests d'erreurs
    printf("\nTESTS D'ERREURS :\n\n");
    test_expression("2 3");              // Opérateur manquant
    test_expression("2 +");              // Deuxième opérande manquant
    test_expression("+ 3");              // Premier opérande manquant
    test_expression("2 & 3");            // Caractère invalide
    test_expression("2 + 3 + 4");        // Trop d'éléments
    test_expression("2.5.5 + 3");        // Nombre mal formé
    test_expression("");                 // Expression vide
    
    return 0;
}