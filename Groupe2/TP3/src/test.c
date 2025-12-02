#include <stdio.h>
#include "lexer.h"
#include "parseur.h"

void evaluer_expression(const char* expr) {
    printf("Expression : %s\n", expr);
    
    Lexer lexer;
    lexer_init(&lexer, expr);
    
    Parser parser;
    parser_init(&parser, &lexer);
    
    double resultat = parser_parse_expression(&parser);
    
    if (!parser_has_error(&parser)) {
        printf("Résultat   : %g\n", resultat);
    } else {
        printf("Résultat   : ERREUR\n");
    }
    printf("\n");
}

int main() {
    printf("=== Test de l'évaluateur d'expressions ===\n\n");
    
    // Tests simples
    evaluer_expression("2 + 3");
    evaluer_expression("10 - 4");
    evaluer_expression("5 * 6");
    evaluer_expression("20 / 4");
    
    // Tests avec priorité des opérateurs
    evaluer_expression("1 + 20 * 5");       // = 1 + 100 = 101
    evaluer_expression("2 * 3 + 4");        // = 6 + 4 = 10
    evaluer_expression("10 + 5 * 2 - 3");   // = 10 + 10 - 3 = 17
    evaluer_expression("100 / 5 + 2 * 3");  // = 20 + 6 = 26
    
    // Tests avec nombres réels
    evaluer_expression("1.5 + 2.5");
    evaluer_expression("10.0 / 4.0");
    evaluer_expression("3.14 * 2");
    
    // Tests d'erreurs
    evaluer_expression("10 / 0");           // Division par zéro
    evaluer_expression("5 +");              // Expression incomplète
    evaluer_expression("* 5");              // Commence par un opérateur
    evaluer_expression("2 & 3");            // Caractère invalide
    
    return 0;
}