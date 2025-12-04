#include "evaluation.h"
#include <stdio.h>
#include <string.h>

// Évalue une expression mathématique
ResultatEvaluation evaluer_expression(Expression expr) {
    ResultatEvaluation res;
    res.valide = 0;
    res.resultat = 0.0;
    strcpy(res.erreur, "");
    
    // Vérifier que l'expression est valide
    if (!expr.valide) {
        strcpy(res.erreur, "Expression invalide (erreur de parsing)");
        return res;
    }
    
    // Effectuer le calcul selon l'opération
    switch (expr.operation) {
        case '+':
            res.resultat = expr.operande1 + expr.operande2;
            res.valide = 1;
            break;
            
        case '-':
            res.resultat = expr.operande1 - expr.operande2;
            res.valide = 1;
            break;
            
        case '*':
            res.resultat = expr.operande1 * expr.operande2;
            res.valide = 1;
            break;
            
        case '/':
            // Vérifier la division par zéro
            if (expr.operande2 == 0.0) {
                strcpy(res.erreur, "Erreur : Division par zéro");
                res.valide = 0;
            } else {
                res.resultat = expr.operande1 / expr.operande2;
                res.valide = 1;
            }
            break;
            
        default:
            sprintf(res.erreur, "Erreur : Opérateur inconnu '%c'", expr.operation);
            res.valide = 0;
            break;
    }
    
    return res;
}

// Affiche le résultat de l'évaluation
void afficher_resultat(ResultatEvaluation res) {
    if (res.valide) {
        printf("Résultat : %g\n", res.resultat);
    } else {
        printf("%s\n", res.erreur);
    }
}