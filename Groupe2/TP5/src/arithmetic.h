/**
 * Nom du fichier : arithmetic.h
 * Objectif       : Prototypes pour le moteur mathématique. Contient les fonctions pour
 * la conversion Infixe vers Postfixe (Shunting-yard), le calcul RPN
 * et la résolution des expressions Lambda.
 * Auteurs        : 1. Théo DEMARIA
 * 2. Arnaud DECOURT
 */

#ifndef ARITHMETIC_H
#define ARITHMETIC_H

// Résout la lambda (remplacement de texte)
int resolve_lambda(const char* input, char* output);
// Conversion Infix -> Postfix (remplace les variables par leurs valeurs)
int infixToPostfix(const char *infix, char *postfix);
// Calcul
int calculate(const char* expr, double* result);

#endif