#include <stdio.h>

int main() {
    int c, pc; /* c = current char, pc = previous char */
    pc = EOF;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            if (pc != ' ')
                putchar(c);                
        }
        else
            putchar(c);
        pc = c;
    }
    return 0;
}