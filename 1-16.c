#include <stdio.h>

#define MAXLINE 1000 /* maximum input line size*/

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
int main() {
    int len; /* current line length */
    int max; /* maximum length seen fo far */
    char line[MAXLINE]; /* current line */
    char longest[MAXLINE]; /* longest line saved here */

    max = 0;
    while ((line = getline(line, MAXLINE)) > 0) {
        printf("%d: %s", len, line);

        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }

    if (max > 0) {
        printf("longest is %d characters:\n%s", max, longest);
    }
    printf("\n");
    return 0;
}

/* read a line into s, return length */
int getline(char s[], int lim) {
    int c, i, j;
    for (i = 0, j = 0; (c = getchar()) != EOF && c != '\n'; ++i) {
        if (i < lim - 1) {
            s[j++] = c;
        }
    }
    if (c == '\n') {
        if ( i <= lim - 1) {
            s[j++] = c;
        }
        ++i;
    }
    s[j] = '\0';
    return i;
}

void copy(char to[], char from[]) {
    int i = 0;
    while ((to[i] = from[i]) != '\0') ++i;
}