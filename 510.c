#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 1024

void panic(const char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(EXIT_FAILURE);
}


static double stack[STACK_SIZE];
static int sp = -1;		// stack pointer

void push(double e)
{
	sp++;
	if (sp > STACK_SIZE)
		panic("stack overflow!");
	stack[sp] = e;
}

double pop(void)
{
	if (sp < 0)
		panic("stack underflow!");
	return stack[sp--];
}

double top(void)
{
	return stack[sp];
}

int main(int argc, char *argv[])
{
	int i;
	double value;
	for (i = 1; i < argc; i++) {
		switch (argv[i][0]) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			push(atof(argv[i]));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '-':
			value = pop();
			push(pop() - value);
			break;
		case '*':
			push(pop() * pop());
			break;
		case '/':
			value = pop();
			push(pop() / value);
			break;
		default:
			panic("unkonwn operator");
		}
	}

	printf("%g\n", pop());
	return 0;
}
