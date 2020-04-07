#include <stdio.h>

void strcat(char *s, char *t)
{
	while (*s != '\0') {
		s++;
	}

	while ((*s++ = *t++) != '\0');
}

int main(void)
{
	char s[1024] = "string one";
	char t[1024] = "string two";
	printf("string one is: %s\n", s);
	printf("string two is: %s\n", t);

	strcat(s, t);
	printf("the concated string is: %s\n", s);

	return 0;
}
