#include <stdio.h>
#include <string.h>
char *m_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	for (; i < n; i++)
		dest[i] = '\0';

	return dest;
}

char *m_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return dest;
}

int strncmp(const char *s1, const char *s2, size_t n)
{
        return 0;
}

int main(void)
{
	char str1[] = "To be or not to be";
	char str2[40];
	char str3[40];

	puts(str1);
	m_strncpy(str2, str1, sizeof(str2));
	puts(str2);

	m_strncpy(str3, str1, 5);
	puts(str3);
}
