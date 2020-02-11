#include <stdio.h>

#define PROGRAM 0
#define SLASH 1
#define COMMENT 2
#define STAR 3
#define QUOTE 4
#define LITERAL 5

int main(int argc, char const *argv[])
{
    int state; /* state machine's current state, one of the above values. */
    int quote; /* if state == QUOTE, then ' or ", otherwise, undefined. */
    int c; /* input character. */

    state = PROGRAM;
    while ((c = getchar()) != EOF) {
        /* The following cases are in guesstimated order from most common
        to least common. */
        if (state == PROGRAM || state == SLASH) {
            /* program text following a slash. */
            if (state == SLASH) {
                if (c == '*')
                    state = COMMENT;
                else {
                    putchar('/');
                    state = PROGRAM;
                }
            }

            if (state == PROGRAM) {
                /* program text. */
                if (c == '\'' ||c == '"') {
                    quote = c;
                    state = QUOTE;
                    putchar(c);
                }
                else if (c == "/*"[0])
                    state = SLASH;
                else
                    putchar(c);
            }
        }
        else if (state == QUOTE) {
            /* within quoted string or character constant. */
            putchar(c);
            if (c == '\\')
                state = LITERAL;
            else if (c == quote)
                ;
            else if (state == STAR) {
                /*comment following a star */
                if (c == '/')
                    state = PROGRAM;
                else if (c != '*')
                    state = COMMENT;
            }
            else /* state == LITERAL */ {
                putchar(c);
                state = QUOTE;
            }
        }


    }
            if (state == SLASH)
            putchar('/');
    return 0;
}
