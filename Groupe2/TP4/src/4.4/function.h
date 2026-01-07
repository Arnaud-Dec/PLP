/**
 * Nom du fichier : function.h
 * Objectif       : Définition de la structure `function` utilisée pour associer
 * les noms de commandes (EN/FR) à leurs pointeurs de fonctions.
 * Contient les prototypes des fonctions de traitement (echo, date, calcul...).
 * Auteurs        : 1. Théo DEMARIA
 * 2. Arnaud DECOURT
 */

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
void traiter_calcul(char* commande, int fr);

// Fonction utilitaire
void normaliser_cmd(char* dest, const char* src);

#endif