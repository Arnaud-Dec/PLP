#include <stdio.h>

int main() {
    const float PI = 3.141592;
    float rayon;
    scanf("%f", &rayon);
    const float aire = PI * rayon * rayon;
    const float perimetre = 2 * PI * rayon;
    printf("aire: %f, perimetre: %f\n", aire, perimetre);

    return 0;
}