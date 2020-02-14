#include <stdio.h>

#define PROGRAM 0
#define BEGIN_COMMENT 1
#define COMMENT 2
#define END_COMMENT 3
#define QUOTE 4


int main(void)
{
    int this_char, quote_char;
    int state;

    state = PROGRAM;

    while ((this_char = getchar()) != EOF) {
        if (state == PROGRAM) {
            if (this_char == '/')
                state == BEGIN_COMMENT;
            else if (this_char == '"' || this_char == '\'') {
                state = QUOTE;
                putchar(quote_char = this_char);
            } else
                putchar(this_char);
        } else if (state == BEGIN_COMMENT) {
            if (this_char == '*')
                state = COMMENT;
            else {
                /* for the '/' of the comment */
                putchar('/');
                putchar(this_char);
                state = PROGRAM;
            }
        } else if (state == QUOTE) {
            putchar(this_char);
            if (this_char == '\\')
                putchar(getchar());
            else if (this_char == quote_char)
                state = PROGRAM;
        } else if (state == COMMENT) {
            if (this_char == '*')
                state = END_COMMENT;
        } else if (state == END_COMMENT) {
            if (this_char == '/')
                state = PROGRAM;
            else {/* stuttered */
                state = COMMENT;
            }
        }
    }
    return 0;
}
