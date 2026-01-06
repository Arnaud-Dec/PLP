#ifndef FUNCTION_H
#define FUNCTION_H

struct function
{
    char name[50];
    char name_fr[50];
     void (*func)(char* ,int);
};


// Déclarations des fonctions
void afficher_version(char* commande, int fr);
void afficher_aide(char* commande, int fr);
void traiter_date(char* commande, int fr);
void traiter_echo(char* commande, int fr);
void traiter_quit(char* commande, int fr);
void traiter_calcul(char* commande, int fr);  // NOUVELLE FONCTION

// Fonction utilitaire
void normaliser_cmd(char* dest, const char* src);

#endif