#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "var.h"
#include "type.h"

#define MAX 100

// Fonction pour donner la priorité des opérateurs
int precedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
    }
    return 0;
}

// Conversion infix -> postfix
void infixToPostfix(const char *infix, char *postfix) {
    char stack[MAX];
    int top = -1;
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        if (c == ' ') continue;

        if (isdigit(c)) {
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            i--;
        } else if (c == '(') {
            stack[++top] = c;
        } else if (c == ')') {
            while (top >= 0 && stack[top] != '(') {
                postfix[j++] = stack[top--];
                postfix[j++] = ' ';
            }
            top--;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (top >= 0 && precedence(stack[top]) >= precedence(c)) {
                postfix[j++] = stack[top--];
                postfix[j++] = ' ';
            }
            stack[++top] = c;
        }
    }

    while (top >= 0) {
        postfix[j++] = stack[top--];
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
}

// Calcul postfix expression
void calculate(const char* expr, int* result) {
    int stack[MAX];
    int top = -1;
    int i = 0;

    while (expr[i] != '\0') {
        if (expr[i] == ' ') { i++; continue; }

        if (isdigit(expr[i])) {
            int num = 0;
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            stack[++top] = num;
            continue;
        }

        char op = expr[i++];
        int b = stack[top--];
        int a = stack[top--];
        int val = 0;

        switch (op) {
            case '+': val = a + b; break;
            case '-': val = a - b; break;
            case '*': val = a * b; break;
            case '/': 
                if(b == 0) { 
                    printf("Division par zero!\n"); 
                    exit(1);
                }
                val = a / b; 
                break;
        }
        stack[++top] = val;
    }

    *result = stack[top];
}

// Check if input is a variable assignment
int checkVar(const char* input, Var* tab_var, int* var_tab_len){
    const char* eq = strchr(input, '=');
    if (!eq) return 0; // Not a variable assignment

    // Extract variable name
    int name_len = eq - input;
    while (name_len > 0 && input[name_len - 1] == ' ') name_len--; // trim spaces
    char name[30];
    strncpy(name, input, name_len);
    name[name_len] = '\0';

    // Extract value
    const char* value = eq + 1;
    while (*value == ' ') value++; // skip spaces

    Var var;
    strcpy(var.name, name);

    if (*value == '"') {
        // String
        value++; // skip opening quote
        int len = 0;
        while (value[len] != '"' && value[len] != '\0') len++; // calcule la longueur
        var.data = malloc(len + 1); // alloue la mémoire
        if (!var.data) {
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            exit(1);
        }
        strncpy(var.data, value, len);
        var.data[len] = '\0'; // termine la chaîne
        var.type = STRING;
    }else if(strchr(value, '.')){
        var.data = malloc(strlen(value) + 1);
        strcpy(var.data, value);
        var.type = FLOAT;
    } else {
        // Assume integer
        var.data = malloc(strlen(value) + 1);
        strcpy(var.data, value);
        var.type = INT;
    }
    int len = *var_tab_len;
    for(int var_index = 0; var_index < len || *var_tab_len == 0; var_index++){
        if(strcmp(tab_var[var_index].name, var.name) == 0){
            if(tab_var[var_index].type == var.type){
                free(tab_var[var_index].data);
                tab_var[var_index].data = malloc(strlen(var.data) + 1);
                strcpy( tab_var[var_index].data, var.data);
                break;
            }else{
                printf("Erreur : changement de type non autorisé pour la variable %s\n" , var.name);
                return 2;
            }

        }else{
            tab_var[*var_tab_len] = var;
            (*var_tab_len)++;
            break;
        }
    }
    return 1; // It's a variable assignment
}

int main() {
    char input[MAX];
    int tab_var_len = 0;
    Var tab_var[10];

    while(1) { 
        printf("> ");
        fgets(input, MAX, stdin);
        input[strcspn(input, "\n")] = '\0';

        for(int i = 0; i < tab_var_len; i++) {
            if (strcmp(tab_var[i].name, input) == 0) {
                printf("Variable %s definie avec la valeur %s\n", input, tab_var[i].data);
                continue;
            }
        }

        if(!checkVar(input, tab_var, &tab_var_len)) {
            char postfix[MAX];
            infixToPostfix(input, postfix);
            printf("Postfix = %s\n", postfix);

            int res;
            calculate(postfix, &res);
            printf("Resultat: %d\n", res);
        }

        for(int i = 0; i < tab_var_len; i++) {
            printf("%s: %s", tab_var[i].name, tab_var[i].data);

            switch(tab_var[i].type) {
                case INT:    printf(" (INT)"); break;
                case FLOAT:  printf(" (FLOAT)"); break;
                case STRING: printf(" (STRING)"); break;
                default:     printf(" (UNKNOWN)"); break;
            }

            printf("\n");
        }
    }

    for(int i = 0; i < tab_var_len; i++) {
        free(tab_var[i].data);
    }
    return 0;
}
