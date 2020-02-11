#include <stdio.h>
#include <ctype.h>

int main() {
    int c;
    int inspace = 1;
    while ((c = getchar()) != EOF) {
        if (isspace(c)) {
            if (!inspace) {
                putchar('\n');
                inspace = 1;
            }
        }
        else {
            putchar(c);
            inspace = 0;
        }
    }
    return 0;
}