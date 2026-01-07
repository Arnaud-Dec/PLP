#ifndef VARIABLE_H
#define VARIABLE_H

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
} VarType;

typedef struct {
    char name[50];
    VarType type;
    char* value; // On stocke la valeur en chaîne pour simplifier
} Variable;

// Initialise la table
void var_init();
// Nettoie la mémoire
void var_free();
// Gère "x = 10" -> Retourne 1 si succès, 0 si ce n'est pas une affectation
int var_process_assignment(const char* command);
// Récupère la valeur brute (NULL si introuvable)
const char* var_get_value(const char* name);
// Affiche une variable
void var_print(const char* name);

#endif