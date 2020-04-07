#include <stdio.h>

#define MAXVAL 1000
#define MAXLINE 1000

typedef struct {
	int top;
	int val[MAXVAL];
	int pos[MAXVAL];
} stack;

/* stack push function */
int push(stack * s, int foo, int bar)
{
	if (s->top == MAXVAL) {
		printf("stack overflow.\n");
		return 1;
	}
	s->val[s->top] = foo;
	s->pos[s->top] = bar;
	s->top++;
	return 0;
}

/* stack pop function */
int pop(stack * s, int *foo, int *bar)
{
	if (s->top == 0) {
		printf("stack underlow.\n");
		return 1;
	}

	s->top--;
	*foo = s->val[s->top];
	*bar = s->pos[s->top];
	return 0;
}

int getline(char *s, int lim)
{
	int i, c;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n';
	     i++) {
		s[i] = c;
	}
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

void scanline(stack * stk, stack * errstk, char *s, int len)
{
	int i, c, d, foo;
	static int string = 0, comment = 0, isconst = 0, escape = 0;
	for (i = 0; i < len; i++) {
		c = s[i];
		if (!comment) {
			if (c == '\\') {
				/* escape */
				if ((d = s[++i]) == '\\' ||
				    d == 'n' ||
				    d == 'r' ||
				    d == 't' ||
				    d == '\'' ||
				    d == '\"' ||
				    d == 'x' || d == 'a' || d == 'b') {
					continue;
				} else {
					push(errstk, 5, i);
				}
			} else if (c == '\"') {
				/* maybe a text string */
				if (!string)
					string = 1;
				else
					string = 0;
			} else if (c == '\'') {
				/* maybe it is a constant */
				if (!isconst)
					isconst = 1;
				else
					isconst = 0;
			}
		}

		if (!isconst && !string && comment && c == '/') {
			if ((d = s[++i]) == '*')
				comment = 1;
			else if (comment && c == '*') {
				if ((d = s[++i]) == '/') {
					comment = 0;
					continue;	/* done with the comment stuff -- start over */
				}
			}
		}

		/* only bother about ({[]}) that's not in
		 * a string, constant or comment
		 */
		if (!isconst && !string && !comment) {
			if (c == '(' || c == '{' || c == '[') {
				push(stk, c, 0);
			} else if (c == ']' || c == '}' || c == ')') {
				if (pop(stk, &d, &foo)) {
					push(errstk, 4, i);
				}
				if (c == ')' && d != '(') {
					push(stk, d, 0);
					push(errstk, 1, i);
				} else if (c == ']' && d != '[') {
					push(stk, d, 0);
					push(errstk, 2, i);
				} else if (c == '}' && d != '{') {
					push(stk, d, 0);
					push(errstk, 3, i);
				}
			}
		}
	}
}

void print_err(stack * errstk, int lineno)
{
	int errno, pos;

	while (!pop(errstk, &errno, &pos)) {
		printf("on line number %d: ", lineno);
		switch (errno) {
		case 1:
			printf
			    ("closing unopened parantheses, coloumn %d\n",
			     pos + 1);
			break;
		case 2:
			printf
			    ("closing unopened square bracket, coloumn %d\n",
			     pos + 1);
			break;
		case 3:
			printf
			    ("closing unopened curly braces, coloumn %d\n",
			     pos + 1);
			break;
		case 4:
			printf
			    ("trying to close unopened block/control structure, colimn %d\n",
			     pos + 1);
			break;
		case 5:
			printf("illegal escape sequence, column %d\n",
			       pos + 1);
			break;
		default:
			printf("unknown error\n");
			break;
		}
	}
}

int main(int argc, char const *argv[])
{
	stack errstk = { 0 }, stk = { 0 };
	int c, linenbr = 0, errno = 0, linelen;
	char line[MAXLINE];

	while ((linelen = getline(line, MAXLINE)) > 0) {
		linenbr++;
		scanline(&stk, &errstk, line, linelen);
		if (errstk.top) {
			print_err(&errstk, linenbr);
			errno++;
		}
	}

	if (errno)
		printf("%d lines contained error(s)\n", errno);
	else
		printf("well, i didn't find any syntax errors\n");

	return 0;
}
