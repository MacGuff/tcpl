#include <stdio.h>

#define MAXLINE 1000

char line[MAXLINE];

int getline(char s[])
{
    int c, i;
    for(i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }

    if (c == '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

#define FOLDLENGTH 70

int main()
{
    int t, len;
    int location, spaceHolder;

    while ((len = getline(line)) > 0) {
        if (len >= FOLDLENGTH) {
            t = 0;
            location = 0;
            while (t < len) {
                if (line[t] == ' ')
                    spaceHolder = t;
                if (location == FOLDLENGTH) {
                    line[spaceHolder] = '\n';
                    location = 0;
                }
                location++;
                t++;
            }
        }
        printf("%s", line);
    }

    return 0;
}