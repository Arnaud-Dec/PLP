#include <stdio.h>

void afficher_binaire(unsigned int n) {
    if (n > 1) {
        afficher_binaire(n / 2);
    }
    printf("%d", n % 2);
}

int main() {
    unsigned int valeurs[] = {0, 4096, 65536, 65535, 1024};
    int nb_valeurs = sizeof(valeurs) / sizeof(unsigned int);
        
    for (int i = 0; i < nb_valeurs; i++) {
        printf("Décimal : %6u  ->  Binaire : ", valeurs[i]);
        afficher_binaire(valeurs[i]);
        printf("\n");
    }
    
    return 0;
}