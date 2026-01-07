/**
 * Nom du fichier : arithmetic.h
 * Objectif       : Prototypes des fonctions de calcul mathématique (TP4).
 * Déclare les fonctions de conversion Infixe -> Postfixe
 * et l'évaluation des expressions en notation polonaise inverse.
 * Auteurs        : 1. Théo DEMARIA
 * 2. Arnaud DECOURT
 */

#ifndef ARITHMETIC_H
#define ARITHMETIC_H

void infixToPostfix(const char *infix, char *postfix);

int calculate(const char* expr, double* result);

#endif