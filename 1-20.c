#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 1024
#define SPACE ' '
#define TAB '\t'

int numberOfSpaces(int offset, int tabsize) {
    return tabsize - (offset % tabsize);
}

int getline(char s[], int lim) {
    int c, i;
    for(i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }

    if (c == '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

int main() {
    char buffer[MAX_BUFFER];
    int tabsize = 4;
    int i, j, k, l;
    while ((getline(buffer, MAX_BUFFER)) > 0) {
        for (i = 0, l = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] == TAB) {
                j = numberOfSpaces(l, tabsize);
                for (k = 0; k < j; k++) {
                    putchar(SPACE);
                    l++;
                }
            }
            else {
                putchar(buffer[i]);
                l++;
            }
        }
    }
}