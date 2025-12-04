#include <stdio.h>
#include "lexer.h"
#include "parseur.h"
#include "evaluation.h"

void test_complet(const char* expr_str) {
    printf("========================================\n");
    printf("Expression : \"%s\"\n", expr_str);
    printf("----------------------------------------\n");
    
    // Étape 1 : Parser l'expression
    Expression expr = parser_parse(expr_str);
    
    if (expr.valide) {
        // Afficher la représentation interne
        printf("Parsing réussi :\n");
        parser_afficher_expression(expr);
        printf("----------------------------------------\n");
        
        // Étape 2 : Évaluer l'expression
        ResultatEvaluation res = evaluer_expression(expr);
        afficher_resultat(res);
    } else {
        printf("Parsing échoué - Impossible d'évaluer\n");
    }
    
    printf("\n");
}

int main() {
    printf("=== Test Complet : Lexer + Parseur + Évaluateur ===\n\n");
    
    // Tests valides - opérations de base
    printf("TESTS D'ADDITION :\n");
    test_complet("2 + 3");
    test_complet("1.5 + 2.5");
    test_complet("100 + 25");
    
    printf("TESTS DE SOUSTRACTION :\n");
    test_complet("10 - 4");
    test_complet("5.5 - 1.3");
    test_complet("0 - 7");
    
    printf("TESTS DE MULTIPLICATION :\n");
    test_complet("5 * 6");
    test_complet("1.2 * 4.0");
    test_complet("3.14 * 2");
    
    printf("TESTS DE DIVISION :\n");
    test_complet("20 / 4");
    test_complet("10.0 / 4.0");
    test_complet("7 / 2");
    
    printf("TESTS D'ERREURS :\n");
    test_complet("10 / 0");         // Division par zéro
    test_complet("2 3");             // Opérateur manquant
    test_complet("2 +");             // Opérande manquant
    test_complet("2 & 3");           // Caractère invalide
    test_complet("2 + 3 + 4");       // Trop d'éléments
    
    return 0;
}