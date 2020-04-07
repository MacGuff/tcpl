#include <stdio.h>
#include <string.h>

#define MAXLEN 1000
#define MAXLINES 5000

int m_getline(char *s, int lim)
{
	int c, i;
	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

int readlines(char lines[][MAXLEN], int maxlines)
{
	int len, nlines;

	nlines = 0;

	while ((len = m_getline(lines[nlines], MAXLEN)) > 0) {
		if (nlines > MAXLINES)
			return -1;
		else
			lines[nlines++][len - 1] = '\0';
	}

	return nlines;
}

void writelines(char lines[][MAXLEN], int nlines)
{
	while (nlines-- > 0)
		puts(*lines++);
}

char lines[MAXLINES][MAXLEN];

int main(void)
{
	int nlines = readlines(lines, MAXLINES);

	writelines(lines, nlines);

	return 0;
}
