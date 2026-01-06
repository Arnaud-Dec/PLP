#ifndef ARITHMETIC_H
#define ARITHMETIC_H

void infixToPostfix(const char *infix, char *postfix);

int calculate(const char* expr, double* result);

#endif