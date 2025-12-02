#include <stdio.h>
#include "lexer.h"

void test_lexer(const char* expression) {
    printf("Expression: %s\n", expression);
    
    Lexer lexer;
    lexer_init(&lexer, expression);
    
    Token token;
    do {
        token = lexer_next_token(&lexer);
        
        switch(token.type) {
            case TOKEN_NUMBER:
                printf("  NUMBER: %g\n", token.value);
                break;
            case TOKEN_OPERATOR:
                printf("  OPERATOR: %c\n", token.operator);
                break;
            case TOKEN_END:
                printf("  END\n");
                break;
            case TOKEN_ERROR:
                printf("  ERROR: Caractere non autorise\n");
                break;
        }
    } while (token.type != TOKEN_END && token.type != TOKEN_ERROR);
    
    printf("\n");
}

int main() {
    test_lexer("2 + 3 + 2");
    test_lexer("1.2 * 4.0");
    test_lexer("10 / 2");
    test_lexer("5.5 - 1.3");
    test_lexer("2 & 3");  // Test d'erreur
    
    return 0;
}