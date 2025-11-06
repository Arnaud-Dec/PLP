#include <stdio.h>

void typeFor(int taille) {
    for (int i = 1; i <= taille; i++) {
        for (int j = 1; j <= i; j++) {

            if (i == taille) {
                printf("* ");
            }
            else if (i <= 2) {
                printf("* ");
            }
            else {
                if (j == 1 || j == i)
                    printf("* ");
                else
                    printf("# ");
            }
        }
        printf("\n");
    }
}

void typeWhile(const int taille) {
    int i = 1;
    while (i <= taille) {
        int j = 1;
        while (j <= i) {
            if (i == taille) {
                printf("* ");
            }
            else if (i <= 2) {
                printf("* ");
            }
            else {
                if (j == 1 || j == i)
                    printf("* ");
                else
                    printf("# ");
            }
            j++;
        }
        printf("\n");
        i++;
    }
}

int main() {
    int taille;
    const int max = 100;

    do {
        printf("Entrez une taille (<%d) : ", max);
        scanf("%d", &taille);
    } while (taille >= max || taille <= 0);


    typeFor(taille);
    
    printf("\n");

    typeWhile(taille);

    return 0;
}
