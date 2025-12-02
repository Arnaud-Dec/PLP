#include <stdio.h>
#include "lexer.h"
#include "parseur.h"

void evaluateur(const char* expr) {

    Lexer lexer;
    lexer_init(&lexer, expr);

}