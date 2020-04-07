#include <stdio.h>
/* bitcount: count 1 bits in x */
int bitcount1(unsigned x)
{
	int b;
	for (b = 0; x != 0; x >>= 1)
		if (x & 01)
			b++;
	return b;
}

/* v2 */
int bitcount2(unsigned x)
{
	int b;
	for (b = 0; x != 0; x &= (x - 1))
		b++;
	return b;
}

/* test */
int main()
{
	int i;
	for (i = 0; i < 1000; i++) {
		printf("bitcount1(%d)=%d, bitcount2(%d)=%d\n", i,
		       bitcount1(i), i, bitcount2(i));
	}
}
