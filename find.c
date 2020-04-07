#include <stdio.h>
#include <string.h>

extern int xgetline(char *s, int lim);

int main(int argc, char *argv[])
{
	char line[1000];

	long lineno = 0;
	int c, except = 0, number = 0, found = 0;

	while (--argc > 0 && (*++argv)[0] == '-') {
		while (c = *++argv[0]) {
			switch (c) {
			case 'n':
				number = 1;
				break;
			case 'x':
				except = 1;
				break;
			default:
				printf("illegal option %c\n", c);
				argc = 0;
				found = -1;
				break;
			}
		}
	}
	if (argc != 1)
		printf("Usage: find -n -x pattern\n");
	else
		while (xgetline(line, 1000) > 0) {
			lineno++;
			if ((strstr(line, *argv) != NULL) != except) {
				if (number)
					printf("%ld:", lineno);
				printf("%s", line);
				found++;
			}
		}

	return found;
}
