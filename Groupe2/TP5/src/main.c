#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "type.h"
#include "var.h"
// --- DEFINITIONS (remplace var.h et type.h pour la compilation) ---

#define MAX_BUFFER 256
#define MAX_VARS 50

// --- UTILITAIRES ---

char* safe_strdup(const char* s) {
    char* p = malloc(strlen(s) + 1);
    if (p) strcpy(p, s);
    return p;
}

const char* get_type_label(Type t) {
    switch (t) {
        case TYPE_INT:    return "entier";
        case TYPE_FLOAT:  return "nombre réel";
        case TYPE_STRING: return "chaîne de caractères";
        default:          return "inconnu";
    }
}

// --- CALCULATEUR (Pile et Evaluation) ---

int get_precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int is_math_expression(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        // On accepte chiffres, opérateurs ou parenthèses
        if (is_operator(str[i]) || isdigit(str[i]) || str[i] == '(') return 1;
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
            while (isdigit(infix[i]) || infix[i] == '.') { // Support basique float parsing (ignoré au calcul int)
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

// --- LOGIQUE LAMBDA (Refactorisée) ---

// Cette fonction prend l'input brut (ex: "(lambda x.x+2) 3")
// et remplit `final_expr` avec l'expression résolue (ex: "3+2")
// Retourne 1 si succès, 0 si échec
int resolve_lambda(const char* input, Var* tab_var, int var_count, char* final_expr) {
    
    // 1. Parsing structurel
    const char* ptr = input;
    
    // Vérification préfixe
    if (strncmp(ptr, "(lambda", 7) != 0) return 0;
    
    // Trouver le point '.' qui sépare la variable du corps
    const char* dot_pos = strchr(ptr, '.');
    if (!dot_pos) return 0;

    // Trouver la parenthèse fermante de la lambda
    // On cherche la parenthèse correspondante (simplification: la première fermante après le point)
    // Note: Pour une vraie gestion imbriquée, il faudrait un compteur de parenthèses.
    const char* close_par = strrchr(ptr, ')'); // On prend la dernière pour englober l'expression
    if (!close_par || close_par < dot_pos) return 0;

    // 2. Extraire le corps de la fonction (entre . et ))
    char body[MAX_BUFFER];
    int len_body = close_par - (dot_pos + 1);
    strncpy(body, dot_pos + 1, len_body);
    body[len_body] = '\0';

    // 3. Extraire l'argument (après la parenthèse fermante)
    const char* arg_start = close_par + 1;
    while (*arg_start == ' ') arg_start++; // Skip spaces
    
    char arg_val[MAX_BUFFER];
    
    // L'argument est-il un nombre ou une variable ?
    int is_number = 1;
    for(int k=0; k<strlen(arg_start); k++) {
        if(!isdigit(arg_start[k]) && arg_start[k] != '\0' && arg_start[k] != '\n') {
            is_number = 0; break;
        }
    }

    if (is_number && strlen(arg_start) > 0) {
        strcpy(arg_val, arg_start);
    } else {
        // C'est une variable, on la cherche
        char var_name[30];
        strncpy(var_name, arg_start, 29);
        var_name[strcspn(var_name, " \n")] = '\0'; // Trim
        
        int idx = find_variable_index(tab_var, var_count, var_name);
        if (idx == -1) {
            printf("Erreur : la variable argument '%s' n'est pas définie\n", var_name);
            return 0;
        }
        strcpy(arg_val, tab_var[idx].data);
    }

    // Nettoyer l'argument (enlever saut de ligne éventuel)
    arg_val[strcspn(arg_val, "\n")] = '\0';

    // 4. Substitution : Remplacer 'x' par arg_val dans body
    // Simplification : on suppose que la variable lambda est 'x' comme demandé dans le TP
    int y = 0;
    for (int k = 0; body[k] != '\0'; k++) {
        if (body[k] == 'x') {
            // On vérifie que c'est bien la variable x et pas une partie d'un mot (ex: 'max')
            // Ici context TP math simple : on assume x est la variable.
            for (int m = 0; m < strlen(arg_val); m++) {
                final_expr[y++] = arg_val[m];
            }
        } else {
            final_expr[y++] = body[k];
        }
    }
    final_expr[y] = '\0';

    // printf("Debug Lambda résolue : %s\n", final_expr); // Décommenter pour debug
    return 1;
}

// --- GESTION AFFECTATION ---

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
        // Nettoyage saut de ligne
        new_var.data[strcspn(new_var.data, "\n")] = '\0';

        if (strchr(val_start, '.')) {
            new_var.type = TYPE_FLOAT;
        } else {
            new_var.type = TYPE_INT;
        }
    }

    // 3. Stockage / Mise à jour
    int idx = find_variable_index(tab_var, *var_count, new_var.name);

    if (idx != -1) {
        if (tab_var[idx].type != new_var.type) {
            printf("Erreur : changement de type non autorisé pour la variable %s\n", new_var.name);
            free(new_var.data);
            return 1; 
        }
        free(tab_var[idx].data);
        tab_var[idx].data = new_var.data;
        printf("Variable %s définie avec la valeur %s (%s)\n", 
               new_var.name, new_var.data, get_type_label(new_var.type));
    } else {
        if (*var_count < MAX_VARS) {
            tab_var[*var_count] = new_var;
            (*var_count)++;
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

    printf("Interpreteur demarre. (Ctrl+C pour quitter)\n");

    while(1) { 
        printf("> ");
        if (!fgets(input, MAX_BUFFER, stdin)) break;
        
        input[strcspn(input, "\n")] = '\0'; 
        if (strlen(input) == 0) continue;

        // --- 1. Gestion Lambda ---
        // On vérifie d'abord si c'est une lambda
        if (strncmp(input, "(lambda", 7) == 0) {
            char expression_resolue[MAX_BUFFER];
            
            // On transforme la lambda en expression mathématique simple (ex: "3 + 2 * 3")
            if (resolve_lambda(input, tab_var, var_count, expression_resolue)) {
                // Si la résolution a marché, on calcule le résultat
                char postfix[MAX_BUFFER];
                int result;
                infix_to_postfix(expression_resolue, postfix);
                if (evaluate_postfix(postfix, &result)) {
                    printf("%d\n", result);
                } else {
                    printf("Erreur lors du calcul de l'expression lambda.\n");
                }
            }
            continue; // On passe à la boucle suivante
        }

        // --- 2. Affectation (ex: x = 4) ---
        if (strchr(input, '=') != NULL) {
            if (process_assignment(input, tab_var, &var_count)) {
                continue;
            }
        }

        // --- 3. Affichage Variable existante (ex: x) ---
        int idx = find_variable_index(tab_var, var_count, input);
        if (idx != -1) {
            printf("%s = %s\n", tab_var[idx].name, tab_var[idx].data);
            continue;
        }

        // --- 4. Calcul Mathématique Standard ---
        // Si ce n'est pas une affectation, ni une variable connue, on essaie de calculer
        if (is_math_expression(input)) {
            char postfix[MAX_BUFFER];
            int result;
            
            infix_to_postfix(input, postfix);
            if (evaluate_postfix(postfix, &result)) {
                printf("%d\n", result);
            } else {
                printf("Erreur de syntaxe ou calcul impossible.\n");
            }
        } else {
             // Si tout le reste a échoué
             printf("Erreur : la variable %s n'est pas définie ou commande inconnue\n", input);
        }
    }

    free_variables(tab_var, var_count);
    return 0;
}