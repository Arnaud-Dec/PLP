#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "var.h"
#include "type.h"

#define MAX_BUFFER 100
#define MAX_VARS 50


// --- UTILITAIRES ---

char* safe_strdup(const char* s) {
    char* p = malloc(strlen(s) + 1);
    if (p) strcpy(p, s);
    return p;
}

// Renvoie le libellé exact demandé dans l'exemple
const char* get_type_label(Type t) {
    switch (t) {
        case TYPE_INT:    return "entier";
        case TYPE_FLOAT:  return "nombre réel";
        case TYPE_STRING: return "chaîne de caractères";
        default:          return "inconnu";
    }
}

// --- CALCULATEUR (INT) ---

int get_precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Vérifie si une chaîne ressemble à une opération mathématique (+, -, *, / ou nombre)
int is_math_expression(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (is_operator(str[i]) || isdigit(str[i])) return 1;
    }
    return 0;
}

void infix_to_postfix(const char *infix, char *postfix) {
    char stack[MAX_BUFFER];
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
            if (top >= 0) top--; 
        } else if (is_operator(c)) {
            while (top >= 0 && get_precedence(stack[top]) >= get_precedence(c)) {
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

int evaluate_postfix(const char* expr, int* result) {
    int stack[MAX_BUFFER];
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
        } else if (is_operator(expr[i])) {
            if (top < 1) return 0;
            
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
                        printf("Erreur: Division par zero!\n");
                        return 0; 
                    }
                    val = a / b; 
                    break;
            }
            stack[++top] = val;
        } else {
            i++; 
        }
    }
    
    if (top != 0) return 0;
    *result = stack[top];
    return 1;
}

// --- GESTION DES VARIABLES ---

int find_variable_index(Var* tab_var, int count, const char* name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(tab_var[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void free_variables(Var* tab_var, int count) {
    for (int i = 0; i < count; i++) {
        free(tab_var[i].data);
    }
}

// Retourne 1 si c'est une affectation traitée, 0 sinon
int process_assignment(const char* input, Var* tab_var, int* var_count) {
    const char* eq_pos = strchr(input, '=');
    if (!eq_pos) return 0; 

    // 1. Extraire le nom
    int name_len = eq_pos - input;
    char name[30];
    if (name_len >= 30) name_len = 30;
    
    strncpy(name, input, name_len);
    name[name_len] = '\0';
    
    // Trim spaces at end of name
    char* end_name = name + strlen(name) - 1;
    while(end_name > name && isspace(*end_name)) *end_name-- = '\0';

    // 2. Extraire la valeur
    const char* val_start = eq_pos + 1;
    while (*val_start == ' ') val_start++; 

    Var new_var;
    strncpy(new_var.name, name, 30);
    new_var.name[30] = '\0';

    // Détection
    if (*val_start == '"') {
        val_start++; // Skip quote
        const char* quote_end = strchr(val_start, '"');
        int len = quote_end ? (quote_end - val_start) : strlen(val_start);
        
        new_var.data = malloc(len + 1);
        strncpy(new_var.data, val_start, len);
        new_var.data[len] = '\0';
        new_var.type = TYPE_STRING;
    } else {
        new_var.data = safe_strdup(val_start);
        if (strchr(val_start, '.')) {
            new_var.type = TYPE_FLOAT;
        } else {
            new_var.type = TYPE_INT;
        }
    }

    // 3. Stockage / Mise à jour
    int idx = find_variable_index(tab_var, *var_count, new_var.name);

    if (idx != -1) {
        // Variable existe déjà : check type
        if (tab_var[idx].type != new_var.type) {
            printf("Erreur : changement de type non autorisé pour la variable %s\n", new_var.name);
            free(new_var.data);
            return 1; 
        }
        // Mise à jour OK
        free(tab_var[idx].data);
        tab_var[idx].data = new_var.data;
        // FORMAT SORTIE DEMANDÉ
        printf("Variable %s définie avec la valeur %s (%s)\n", 
               new_var.name, new_var.data, get_type_label(new_var.type));
    } else {
        // Nouvelle variable
        if (*var_count < MAX_VARS) {
            tab_var[*var_count] = new_var;
            (*var_count)++;
            // FORMAT SORTIE DEMANDÉ
            printf("Variable %s définie avec la valeur %s (%s)\n", 
                   new_var.name, new_var.data, get_type_label(new_var.type));
        } else {
            printf("Erreur : Trop de variables.\n");
            free(new_var.data);
        }
    }

    return 1;
}

// --- MAIN ---

int main() {
    char input[MAX_BUFFER];
    Var tab_var[MAX_VARS];
    int var_count = 0;

    while(1) { 
        printf("> ");
        if (!fgets(input, MAX_BUFFER, stdin)) break;
        
        input[strcspn(input, "\n")] = '\0'; 
        if (strlen(input) == 0) continue;

        // 1. Affectation (ex: x = 4)
        if (process_assignment(input, tab_var, &var_count)) {
            continue;
        }

        // 2. Affichage Variable existante (ex: x)
        // On vérifie d'abord si c'est une variable connue
        int idx = find_variable_index(tab_var, var_count, input);
        if (idx != -1) {
            // FORMAT SORTIE "Variable = Valeur" ou juste la valeur ?
            // Votre exemple ne montre pas le cas "x" si x existe, 
            // mais on suppose qu'on affiche la valeur.
            printf("%s = %s\n", tab_var[idx].name, tab_var[idx].data);
            continue;
        }

        // 3. Variable INCONNUE (ex: y)
        // Si ce n'est pas une expression mathématique (pas de chiffres/opérateurs)
        // et qu'on ne l'a pas trouvée à l'étape 2, c'est une erreur de variable.
        if (!is_math_expression(input)) {
             printf("Erreur : la variable %s n'est pas définie\n", input);
             continue;
        }

        // 4. Calcul Mathématique
        char postfix[MAX_BUFFER];
        int result;
        
        infix_to_postfix(input, postfix);
        if (evaluate_postfix(postfix, &result)) {
            printf("Resultat: %d\n", result);
        } else {
            // Cas fallback
            printf("Commande inconnue.\n");
        }
    }

    free_variables(tab_var, var_count);
    return 0;
}