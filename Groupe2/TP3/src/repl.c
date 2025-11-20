#include <stdio.h>
#include <string.h>
#include <time.h>
#include "function.h"

/**
 * Programme qui simule un interpréteur de commandes simple.
 * Il lit les commandes utilisateur et les traite en fonction de leur contenu.
 */

const char* version = "1.0.1";
int continuer = 1; // Variable pour contrôler la boucle principale


void afficher_version(){
    printf("%s\n", version);
}

void afficher_aide(){
    printf("===== Aide - Commandes disponibles =====\n");
    printf("help        : Affiche cette aide\n");
    printf("version     : Affiche la version du programme\n");
    printf("date        : Affiche la date et l'heure actuelles\n");
    printf("echo <txt>  : Affiche le texte suivant la commande\n");
    printf("quit        : Quitte le programme\n");
    printf("========================================\n");
}

void traiter_echo(char* commande){
    // Traite la commande "echo" pour afficher du texte
            printf("Echo: ");

            // Imprime la chaîne
            for (int i = 5; commande[i] != '\0'; i++)
            {
                printf("%c", commande[i]);
            }
            printf("\n"); // Saut de ligne après la sortie
}

void traiter_quit(){
    printf("Arrêt...\n");
    continuer = 0;
}


int main()
{
    struct function table_f[] = {
        {"echo " , traiter_echo},
        {"quit" , traiter_quit},
        {"version" , afficher_version},
        {"help" , afficher_aide}
    };
    
    // Boucle principale qui lit et traite les commandes utilisateur
    while (continuer)
    {
        printf("> "); // Affiche le prompt de commande

        // Buffer pour stocker la commande utilisateur
        char commande[1024];

        // Lit la commande utilisateur et la stocke dans le buffer
        fgets(commande, sizeof(commande), stdin);

        // Enlève le caractère de fin de ligne ajouté par fgets
        commande[strcspn(commande, "\n")] = 0;

        int nb_cmd = sizeof(table_f) / sizeof(table_f[0]);
        int find_f = 0;

        for(int i = 0; i < nb_cmd ; i++){
            if (strncmp(commande, table_f[i].name, strlen(table_f[i].name)) == 0){
                table_f[i].func(commande);
                find_f = 1;
            }
        }

        if (!find_f) {
            printf("Commande non reconnue. Essayez 'echo <text>' pour afficher du texte, ou tapez 'quit' pour quitter.\n");
        }

        printf("\n"); // Saut de ligne après la sortie
    }

    return 0;
}
