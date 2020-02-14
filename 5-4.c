#include <stdio.h>

int strlen(char *s)
{
    int n = 0;
    while(*s++ != '\0') {
        n++;
    }

    return n;
}

int strcmp(char *s, char *t)
{
    for(; *s == *t; s++, t++)
        ;
    return *s - * t;
}

int strend(char *s, char *t)
{
    int s_len = strlen(s);
    int t_len = strlen(t);

    if ( s_len >= t_len) {
        s += s_len - t_len;

        if(!strcmp(s, t))
            return 1;
    }

    return 0;
}

int main(void)
{
    char *s1 = "some really long string";
    char *s2 = "ng.";
    char *s3 = "ng";

    if(strend(s1, s2)) {
        printf("string (%s) has (%s) at the end.\n", s1, s2);
    } else {
        printf("string (%s) doesn't has (%s) at the end.\n", s1, s2);
    }

}
