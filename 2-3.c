#include <stdio.h>

int hexalpha2int(int c)
{
    char hexalpha[] = "aAbBcCdDeEfF";
    int i;
    int answer = 0;

    for (i = 0; answer == 0 && hexalpha[i] != '\0'; i++) {
        if (hexalpha[i] == c)
            answer = 10 + (i / 2);
    }

    return answer;
}
unsigned int htoi(const char *s)
{
    unsigned int ans = 0;
    int i = 0;
    int valid = 1;
    int hexit;

    if (s[i] == 0) {
        ++i;
        if (s[i] == 'x' || s[i] == 'X') {
            ++i;
        }
    }

    while (valid && s[i] != '\0') {
        ans = ans * 16;
        if (s[i] >= '0' && s[i] <= '9') {
            ans += s[i] - '0';
        } else {
            hexit = hexalpha2int(s[i]);
            if (hexit == 0)
                valid = 0;
            else
                ans += hexit;
        }

        ++i;
        if (!valid)
            ans = -1; /* -1 means something wrong happens */
        return ans;
    }
}