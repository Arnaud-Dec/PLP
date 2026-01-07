#include "variable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_VARS 100

static Variable symbol_table[MAX_VARS];
static int var_count = 0;

void var_init() {
    var_count = 0;
}

void var_free() {
    for (int i = 0; i < var_count; i++) {
        free(symbol_table[i].value);
    }
    var_count = 0;
}

static int find_var_index(const char* name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) return i;
    }
    return -1;
}

const char* var_get_value(const char* name) {
    int idx = find_var_index(name);
    if (idx != -1) return symbol_table[idx].value;
    return NULL;
}

static char* safe_strdup(const char* s) {
    char* d = malloc(strlen(s) + 1);
    if (d) strcpy(d, s);
    return d;
}

void var_print(const char* name) {
    int idx = find_var_index(name);
    if (idx != -1) {
        const char* t = "inconnu";
        if (symbol_table[idx].type == TYPE_INT) t = "entier";
        if (symbol_table[idx].type == TYPE_FLOAT) t = "nombre réel";
        if (symbol_table[idx].type == TYPE_STRING) t = "chaîne de caractères";
        printf("Variable %s définie avec la valeur %s (%s)\n", name, symbol_table[idx].value, t);
    } else {
        printf("Erreur : la variable %s n'est pas définie\n", name);
    }
}

int var_process_assignment(const char* command) {
    const char* eq_pos = strchr(command, '=');
    if (!eq_pos) return 0;

    // 1. Nom (Partie gauche)
    int name_len = eq_pos - command;
    char name[50];
    if (name_len >= 50) name_len = 49;
    strncpy(name, command, name_len);
    name[name_len] = '\0';

    // Trim fin nom
    char* end = name + strlen(name) - 1;
    while(end > name && isspace(*end)) *end-- = '\0';
    // Trim début nom
    char* start = name;
    while(*start && isspace(*start)) start++;
    if (*start == '\0') return 0;

    // 2. Valeur (Partie droite)
    const char* val_ptr = eq_pos + 1;
    while (*val_ptr && isspace(*val_ptr)) val_ptr++;
    
    // --- CORRECTION DU TYPE ---
    VarType type;
    char cleaned_val[1024];
    
    // Cas A : Chaîne de caractères (commence par ")
    if (val_ptr[0] == '"') {
        type = TYPE_STRING;
        strncpy(cleaned_val, val_ptr + 1, 1023); // Copie après le "
        char* end_quote = strrchr(cleaned_val, '"');
        if (end_quote) *end_quote = '\0';        // Coupe le " final
    } 
    // Cas B : Nombre (commence par un chiffre ou un signe -)
    else if (isdigit(val_ptr[0]) || val_ptr[0] == '-') {
        strcpy(cleaned_val, val_ptr);
        
        // Est-ce un float ou un int ?
        if (strchr(val_ptr, '.')) {
            type = TYPE_FLOAT;
        } else {
            type = TYPE_INT;
        }
    }
    // Cas C : Erreur (ni string, ni nombre valide)
    else {
        // Optionnel : On pourrait vérifier ici si c'est une autre variable (ex: x = y)
        // Pour l'instant, on rejette le texte brut comme "bonjour"
        printf("Erreur : Valeur '%s' invalide (attendu: nombre ou \"texte\")\n", val_ptr);
        return 0; // On quitte sans rien sauvegarder
    }

    // 3. Stockage (Code inchangé)
    int idx = find_var_index(start);
    if (idx != -1) {
        if (symbol_table[idx].type != type) {
            printf("Erreur : changement de type non autorisé pour la variable %s\n", start);
            return 1;
        }
        free(symbol_table[idx].value);
        symbol_table[idx].value = safe_strdup(cleaned_val);
        var_print(start);
    } else {
        if (var_count >= MAX_VARS) {
            printf("Erreur : Trop de variables.\n");
            return 1;
        }
        strcpy(symbol_table[var_count].name, start);
        symbol_table[var_count].type = type;
        symbol_table[var_count].value = safe_strdup(cleaned_val);
        var_count++;
        var_print(start);
    }
    return 1;
}