#include <stdio.h>
#include <stdbool.h>

bool calculate(int num1, int num2, char op, int *result) {
    switch (op) {
        case '+':
            *result = num1 + num2;
            return true;
        case '-':
            *result = num1 - num2;
            return true;
        case '*':
            *result = num1 * num2;
            return true;
        case '/':
            if (num2 == 0) {
                printf("Erreur: division par zéro.\n");
                return false;
            }
            *result = num1 / num2;
            return true;
        case '%':
            if (num2 == 0) {
                printf("Erreur: modulo par zéro.\n");
                return false;
            }
            *result = num1 % num2;
            return true;
        case '&':
            *result = num1 & num2;
            return true;
        case '|':
            *result = num1 | num2;
            return true;
        case '^':
            *result = num1 ^ num2;
            return true;
        default:
            printf("Erreur: opérateur inconnu '%c'.\n", op);
            return false;
    }
}

int main() {
    int num1, num2, result;
    char op;
    char input[100];

    printf("Entrez une opération (ex : 4+5, 4 + 5 ou ~4) : ");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Erreur: lecture échouée.\n");
        return 1;
    }

    if (sscanf(input, " %c %d", &op, &num1) == 2 && op == '~') {
        result = ~num1;
        printf("~%d = %d\n", num1, result);
    }
    else if (sscanf(input, "%d %c %d", &num1, &op, &num2) == 3) {
        if (!calculate(num1, num2, op, &result)) {
            return 1;
        }
        printf("%d %c %d = %d\n", num1, op, num2, result);
    }
    else {
        printf("Erreur: format d'entrée invalide.\n");
        return 1;
    }

    return 0;
}