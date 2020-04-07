#include <stdio.h>

#define MAXLINE 1000

int main(int argc, char const *argv[])
{
	int i = 0;
	int c;
	char s[MAXLINE];

	while (i < MAXLINE - 1) {
		c = getchar();
		if (c == EOF)
			break;
		if (c == '\n')
			break;
		s[i++] = c;
	}
	s[i] = '\0';
	return 0;
}
