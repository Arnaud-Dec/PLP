#include <stdio.h>
#include <stdbool.h>

// Effectue l'opération demandée et place le résultat dans *result
bool calculate(int num1, int num2, char op, int *result) {
    switch (op) {
        case '+':                     // Addition
            *result = num1 + num2;
            return true;
        case '-':                     // Soustraction
            *result = num1 - num2;
            return true;
        case '*':                     // Multiplication
            *result = num1 * num2;
            return true;
        case '/':                     // Division
            if (num2 == 0) {          // Vérification division par zéro
                printf("Erreur: division par zéro.\n");
                return false;
            }
            *result = num1 / num2;
            return true;
        case '%':                     // Modulo
            if (num2 == 0) {          // Modulo par zéro interdit
                printf("Erreur: modulo par zéro.\n");
                return false;
            }
            *result = num1 % num2;
            return true;
        case '&':                     // AND binaire
            *result = num1 & num2;
            return true;
        case '|':                     // OR binaire
            *result = num1 | num2;
            return true;
        default:                      // Opérateur non reconnu
            printf("Erreur: opérateur inconnu '%c'.\n", op);
            return false;
    }
}

int main() {
    int num1, num2, result;
    char op;
    char input[100];                  // Buffer pour lire l'expression

    printf("Entrez une opération (ex : 4+5, 4 + 5 ou ~4) : ");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {  // Lecture sécurisée
        printf("Erreur: lecture échouée.\n");
        return 1;
    }

    // Cas où l'utilisateur saisit un opérateur unaire (~)
    if (sscanf(input, " %c %d", &op, &num1) == 2 && op == '~') {
        result = ~num1;               // Complément binaire
        printf("~%d = %d\n", num1, result);
    }
    // Cas opération binaire : num1 op num2
    else if (sscanf(input, "%d %c %d", &num1, &op, &num2) == 3) {
        if (!calculate(num1, num2, op, &result)) { // Calcul via la fonction
            return 1;
        }
        printf("%d %c %d = %d\n", num1, op, num2, result);
    }
    else {                            // Format non valide
        printf("Erreur: format d'entrée invalide.\n");
        return 1;
    }

    return 0;
}
