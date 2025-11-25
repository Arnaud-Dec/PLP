#include <stdio.h>

int main() {

    // Boucle for : nombres non divisibles par 4 mais divisibles par 6
    for(int i = 0 ; i < 1001 ; i++ ) {
        if( i%4 != 0 && i%6 == 0){
            printf("la valeur %d n'est pas divisible par 4 et divisible par 6\n", i);
        }
    }

    // Boucle while : nombres pairs et divisibles par 8
    int j = 0;
    while (j < 1001) {
        if( j%2 == 0 && j%8 == 0){
            printf("la valeur %d est pair et divisible par 8\n", j);
        }
        j++;
    }

    // Boucle do-while : nombres divisibles par 5 ou 7 mais pas par 10
    int w = 0;
    do {
        if((w%5 == 0 || w%7 == 0) && w%10 != 0){
            printf("la valeur %d est divisible par 5 ou 7 mais pas par 10\n", w);
        }
        w++;
    } while ( w <= 1000);

    return 0;
}
