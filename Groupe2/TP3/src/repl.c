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


void afficher_version(char* commande ,int fr){
    printf("%s\n", version);
}

void afficher_aide(char* commande ,int fr){

    if(fr == 0){
        printf("===== Help - Commandes disponibles =====\n");
        printf("help        : Affiche cette aide\n");
        printf("version     : Affiche la version du programme\n");
        printf("date        : Affiche la date et l'heure actuelles\n");
        printf("echo <txt>  : Affiche le texte suivant la commande\n");
        printf("quit        : Quitte le programme\n");
        printf("========================================\n");
    }
    else {
        printf("===== Aide - Commandes disponibles =====\n");
        printf("aide        : Affiche cette aide\n");
        printf("version     : Affiche la version du programme\n");
        printf("date        : Affiche la date et l'heure actuelles\n");
        printf("echo <txt>  : Affiche le texte suivant la commande\n");
        printf("quit        : Quitte le programme\n");
        printf("========================================\n");
    }
}

void traiter_date(char* commande , int fr){
    time_t t = time(NULL);
    printf("%s\n", ctime(&t));
}

void traiter_echo(char* commande , int fr){

    if (fr == 0){

        // Traite la commande "echo" pour afficher du texte
        printf("Echo: ");

        // Imprime la chaîne
        for (int i = 5; commande[i] != '\0'; i++)
        {
            printf("%c", commande[i]);
        }
        printf("\n"); // Saut de ligne après la sortie
    }else{
        printf("Affiché: ");

        // Imprime la chaîne
        for (int i = 9; commande[i] != '\0'; i++)
        {
            printf("%c", commande[i]);
        }
        printf("\n"); // Saut de ligne après la sortie
    }
}

void traiter_quit(char* commande ,int fr){

    if(fr == 0){
        printf("Stop...\n");
    }else{
        printf("Arrêt...\n");
    }
    continuer = 0;
}

void normaliser_cmd(char* dest, const char* src) {
    int j = 0;
    int debut = 1;

    for (int i = 0; src[i] != '\0' || src[i] == 32; i++) {
        unsigned char c = src[i];

        if (c < 128) {
            if (debut && c == ' ') continue;
            debut = 0;
            if (c >= 'A' && c <= 'Z')
                dest[j++] = c + 32;
            else
                dest[j++] = c;
        }
        else {
            dest[j++] = c;
        }
    }
    dest[j] = '\0';
}

int main()
{
    struct function table_f[] = {
        {"echo" ,"affiché ", traiter_echo },
        {"quit" ,"kuitter" ,traiter_quit},
        {"version", "version_fr" , afficher_version},
        {"help" , "aide" ,afficher_aide},
        {"date" , "date" , traiter_date}
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
        int fr ;

        char cmd[1024];
        normaliser_cmd(cmd, commande);

        for(int i = 0; i < nb_cmd ; i++){
            fr = 0;
            if (strncmp(cmd, table_f[i].name, strlen(cmd)) == 0){
                table_f[i].func(commande, fr);
                find_f = 1;
            }
            else if (strncmp(cmd, table_f[i].name_fr, strlen(cmd)) == 0){
                fr = 1;
                table_f[i].func(commande, fr);
                find_f = 1;
            }
        }

        if (!find_f) {
            printf("Commande non reconnue. Essayer help ou aide pour connaître toutes les commandes disponibles.\n");
        }

        printf("\n"); // Saut de ligne après la sortie
    }

    return 0;
}
