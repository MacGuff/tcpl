#include "tcpl.h"

char *lineptr[MAXLINES];

int numcmp(char *s1, char *s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	return v1 < v2 ? -1 : (v1 > v2 ? 1 : 0);
}

int main(int argc, char *argv[])
{
	int nlines;
	int numeric = 0;

	if (argc > 1 && strcmp(argv[1], "-n") == 0)
		numeric = 1;

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		xqsort((void **) lineptr, 0, nlines - 1,
		       (int (*)(void *, void *)) (numeric ? numcmp :
						  strcmp)
		    );
		writelines(lineptr, nlines);
		return 0;
	}
	return 1;
}
