#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'

/* support cos, sin, exp and sqrt */
enum
{
    COS,
    SIN,
    EXP,
    SQRT,
    UNKNOWN
};

void push(double f);
double pop(void);
int getop(char s[]);
void clear_stack(void);
/*
 * stack routine: push, pop
 */

#define MAXVAL 100

static int sp = 0;
static double val[MAXVAL];

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack overflow!\n");
}

double pop()
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("error: stack underflow\n");
        return 0.0;
    }
}

/* '=': print the top of stack without poping it.
 * '!': swap the top two elements.
 * '&': clear the stack.
 */
void print_stack()
{
    printf("the top of stack is %.8g\n", val[sp]);
}

void swap_stack()
{
    double t = val[sp];
    val[sp] = val[sp - 1];
    val[sp - 1] = t;
}

void clear_stack()
{
    sp = 0;
}

int getch(void);
void ungetch(int c);

int getop(char s[])
{
    int c, i, d;

    while ((s[0] = c = getch()) == ' ' || c == '\t') /* skip whitespace */
        ;

    if (isalpha(c))
    {
        i = 0;
        while (isalpha(s[++i] = c = getch()))
            ;
        if (c != EOF)
            ungetch(c);
        s[i] = '\0';
        if (!strcmp(s, "cos"))
            return COS;
        else if (!strcmp(s, "sin"))
            return SIN;
        else if (!strcmp(s, "exp"))
            return EXP;
        else if (!strcmp(s, "sqrt"))
            return SQRT;
        else
            return UNKNOWN;
    }
    if (!isdigit(c) && c != '.')
    {
        if (c == '-')
        { /* negative operand */
            if (isdigit(d = getch()) || d == '.')
                s[i = 1] = c = d;
            else
            {
                if (d != EOF)
                    ungetch(d);
                s[1] = '\0';
                return c;
            }
        }
        else
        {
            s[1] = '\0';
            return c;
        }
    }
    else
        i = 0;

    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

#define BUFFSIZE 100

static char buff[BUFFSIZE];
static int bufp = 0;

int getch()
{
    return bufp > 0 ? buff[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFFSIZE)
        printf("error: too many characters\n");
    else
        buff[bufp++] = c;
}

int main()
{
    int type;
    double op1, op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            break;
        case COS:
            push(cos(pop()));
            break;
        case SIN:
            push(sin(pop()));
            break;
        case EXP:
            push(sin(pop()));
            break;
        case SQRT:
            push(sqrt(pop()));
            break;
        case '+':
        case '*':
            if (type == '+')
                push(pop() + pop());
            else
                push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
        case '%':
            if ((op2 = pop()) != 0.0)
            {
                if (type == '/')
                    push(pop() / op2);
                else
                {
                    op1 = pop();
                    push(op1 - op2 * ((int)(op1 / op2))); /* a % b = a - b * (a / b) */
                }
            }
            else
                printf("error: zero divisor\n");
            break;
        case '=':
            print_stack();
            break;
        case '!':
            swap_stack();
            break;
        case '&':
            clear_stack();
            break;
        case ';':
        case '\n': /* print */
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s!\n", s);
            break;
        }
    }

    return 0;
}