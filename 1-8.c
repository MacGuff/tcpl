#include <stdio.h>
#define SPACE ' '
#define TABLE '\t'
#define NL '\n'

int main()
{
    int space, table, nl;

    space = table = nl = 0;

    int c;
    while ((c = getchar()) != EOF) {
        if (c == SPACE)
            space++;
        else if (c == TABLE)
            table++;
        else if (c == NL)
            nl++;
    }

    printf("spaces: %d, tables: %d, newlines: %d\n", space, table, nl);
    return 0;
}