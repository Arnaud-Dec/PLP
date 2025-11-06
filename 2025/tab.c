#include <stdio.h>

int main() {
    int tab[5] = {11, 12, 13, 14, 15};
    for (int i = 0; i < 5; i++)
        printf("test %d\n", tab[i]);
    printf("%d\n",sizeof(tab));
    return 0;
}