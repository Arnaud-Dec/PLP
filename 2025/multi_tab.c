#include <stdio.h>

int main(){
    char msg[][10] = {
        "bonjour",
        "le monde",
        "l'année",
        "2025"
    };
    for (int i =0; i<4 ; i++) {
        printf("msg : [%d]: %s\n",i, msg[i]);
    }

    for (int i =0; i<4 ; i++) {
        printf("\n");
        for (int j =0; j<10 ; j++) {
            printf("%c", msg[i][j]);
        }
    }
    printf ("%d", sizeof(msg));

    return 0;
}