#ifndef EVALUATION_H
#define EVALUATION_H

#include "parseur.h"

// Structure pour le résultat de l'évaluation
typedef struct {
    double resultat;     // Résultat du calcul
    int valide;          // 1 si l'évaluation a réussi, 0 sinon
    char erreur[100];    // Message d'erreur si échec
} ResultatEvaluation;

// Fonction d'évaluation
ResultatEvaluation evaluer_expression(Expression expr);

// Fonction pour afficher le résultat
void afficher_resultat(ResultatEvaluation res);

#endif