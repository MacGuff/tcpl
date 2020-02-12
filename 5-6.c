#include <stdio.h>
#include <ctype.h>
int m_getline(char *s, int lim)
{
	int c;
	char *p;

	p = s;

	while (--lim > 0 && (c = getchar()) != EOF && c != '\n'){
		*p++ = (char)c;
	}

	if (c == '\n')
		*p++ = c;
	*p = '\0';
	return p - s;
}

int m_atoi(char *s)
{
	int n = 0;
	int sign = 1;

	while(isspace(*s))
		s++;
	sign = (*s == '-')? -1 : 1;
	if (*s == '+' || *s == '-')
		s++;
	for(; isdigit(*s); s++){
		n = n * 10 + *s - '0';
	}
	return sign * n;
}

int main(void)
{
	char s[100];
	int len;
	fputs(">>> ", stdout);
	len = m_getline(s, 100);
	printf("%s%d chars\n",s, len);
	

	printf("%d\n", m_atoi("123"));
	printf("%d\n", m_atoi("-123"));
	printf("%d\n", m_atoi("   123"));
	printf("%d\n", m_atoi("xxxx"));
	printf("%d\n", m_atoi("123   "));
}
