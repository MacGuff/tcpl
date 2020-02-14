#include <stdio.h>

void squeeze(char s1[], char s2[])
{
    int i, j, k;
    int instr2;

    for(i = j = 0; s1[i] != '\0'; i++) {
        instr2 = 0;

        for( k = 0; s2[k] != '\0'; k++) {
            if (s2[k] == s1[i]) {
                instr2 = 1;
                break;
            }
        }

        if (!instr2)
            s1[j++] = s1[i];

    }
    s1[j] = '\0';
}

