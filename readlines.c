#include "tcpl.h"

int readlines(char *lineptr[], int maxlines)
{
        int nlines, len;
	nlines = 0;
	char *p, line[MAXLINE];
	while ((len = xgetline(line, MAXLINE)) > 0) {
                if (nlines > maxlines || (p = malloc(len)) == NULL)
                        return -1;
		line[len - 1] = '\0';
		strcpy(p, line);
                lineptr[nlines++] = p;
	}
	return nlines;

}

void writelines(char *lineptr[], int nlines)
{
	for (int i = 0; i < nlines; i++) {
		printf("%s\n", lineptr[i]);
	}
}
