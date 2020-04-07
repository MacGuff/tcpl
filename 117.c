#include <stdio.h>

#define MINLEN 81

int readbuff(char buffer[])
{
	size_t i = 0;
	int c;
	while (i < MINLEN) {
		c = getchar();
		if (c == EOF)
			return -1;
		if (c == '\n')
			return 0;
		buffer[i++] = c;
	}
	return 1;
}

int copyline(char buffer[])
{
	size_t i;
	int c;
	int status = 1;
	for (i = 0; i < MINLEN; i++) {
		putchar(buffer[i]);
	}
	while (status == 1) {
		c = getchar();
		if (c == EOF)
			status == -1;
		else if (c == '\n')
			status = 0;
		else
			putchar(c);
	}
	putchar('\n');
	return status;
}

int main()
{
	char buffer[MINLEN];
	int status = 0;
	while (status != -1) {
		status = readbuff(buffer);
		if (status == 1)
			status = copyline(buffer);
	}
}
