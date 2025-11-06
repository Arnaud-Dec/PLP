#include <stdio.h>

int main(){
    
    char chaine1[50];
    char chaine2[50];
    char chaine3[50];

    printf("Chaine 1 < 25 char:");
    scanf("%s", chaine1);

    printf("\nChaine 2 < 25 char:");
    scanf("%s", chaine2);

    // calcul longeur chaine
    int i = 0;
    while(chaine1[i] != '\0' ){
        i++;
    }

    printf("\nLongeur de la chaine 1 = %d\n" , i);

    // Copie chaine
    int j = 0;
    while(chaine1[j] != '\0'){
        chaine3[j] = chaine1[j];
        j++;
    }
    printf("affichage de la chaine 3 (copie de la chaine 1) : %s\n", chaine3);

    // Concaténer deux chaînes
    
    int w = 0;
    while(chaine2[w] != '\0'){
        chaine1[i] = chaine2[w];
        i++;
        w++;
    }
    printf("Concaténation de chaine 1 et chaine 2 : %s\n" , chaine1);

    return 0;
}