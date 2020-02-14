#include <stdio.h>

int main()
{
    float fahr, celsius;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    printf("C----->F\n\n");
    celsius = lower;
    for(celsius = upper; celsius >= lower; celsius = celsius - step) {
        printf("%3.0f %6.1f\n", celsius, fahr);
    }
    return 0;
}