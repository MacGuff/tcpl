#define MAXLINE 1000
#define MAXLINES 5000

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

extern int xgetline(char s[], int lim);
extern int readlines(char *lineptr[], int maxlines);
extern void writelines(char *lineptr[], int nlines);
void xqsort(void *v[], int left, int right, int (*comp)(void *, void *));
