#include "tcpl.h"

char *lineptr[MAXLINES];
int reverse = 0;
int ignorecase = 0;
int numeric = 0;
int xstrcmp(char *s1, char *s2)
{
        int ret = 0;
        char *p1, *p2;
        p1 = s1;
        p2 = s2;
        if (ignorecase) {
                ret = strcasecmp(s1, s2);
        } else
                ret = strcmp(s1, s2);
        return reverse ? -ret: ret;
}

int numcmp(char *s1, char *s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	return v1 < v2 ? -1 : (v1 > v2 ? 1 : 0);
}

int xnumcmp(char *s1, char *s2)
{
         return reverse ? numcmp(s2, s1) : numcmp(s1, s2);
}

int main(int argc, char *argv[])
{
	int nlines;

        for (int i = 1; i < argc; i++) {
                if (strncmp(argv[i], "-",1) == 0) {
                        while (*++argv[i]) {
                                switch (argv[i][0]) {
                                case 'f':
                                        ignorecase = 1;
                                        break;
                                case 'r':
                                        reverse = 1;
                                        break;
                                case 'n':
                                        numeric = 1;
                                        break;
                                case 'd':
                                        break;
                                default:
                                        fprintf(stderr, "illegal option: %c\n", argv[i][0]);
                                        exit(1);
                                }
                        }
                }
        }

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		xqsort((void **) lineptr, 0, nlines - 1,
		       (int (*)(void *, void *)) (numeric ? xnumcmp :
						  xstrcmp)
		    );
		writelines(lineptr, nlines);
		return 0;
	}
	return 1;
}
