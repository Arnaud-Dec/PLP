#ifndef ARITHMETIC_H
#define ARITHMETIC_H

// Résout la lambda (remplacement de texte)
int resolve_lambda(const char* input, char* output);
// Conversion Infix -> Postfix (remplace les variables par leurs valeurs)
int infixToPostfix(const char *infix, char *postfix);
// Calcul
int calculate(const char* expr, double* result);

#endif