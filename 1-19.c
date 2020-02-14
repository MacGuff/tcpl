#include <stdio.h>

#define MAXLINE 1024

void discardnewline(char s[])
{
    int i;
    for (i = 0; s[i]; i++) {
        if (s[i] == '\n')
            s[i] = '\0';
    }
}

void reverse(char s[])
{
    char c;
    int i, j;
    for (j = 0; s[j]; j++)
        ;
    --j;
    for (i = 0; i < j; i++) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
        j--;
    }
}

int getline(char s[], int lim)
{
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

int main()
{
    char line[MAXLINE];
    while (getline(line, MAXLINE) > 0) {
        discardnewline(line);
        reverse(line);
        printf("%s\n", line);
    }
}