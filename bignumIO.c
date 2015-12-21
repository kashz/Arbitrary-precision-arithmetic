#include <stdio.h>
#include "bignum.h"
#include "accessor.h"
#include "bignumIO.h"

void dispNumber(const struct NUMBER* a)
{
	int i;
	char sign;

	if (getSign(a) == 1)
		sign = '+';
	else
		sign = '-';
	printf("%c", sign);
	for (i = 0; i < KETA; i++)
	{
		printf("%2d", a->n[KETA-i-1]);
	}
}
void dispNumberZeroSuppress(const struct NUMBER* a)
{
	int i, startIndex = 0;
	char sign;

	if (getSign(a) == 1)
		sign = '+';
	else
		sign = '-';
	printf("%c", sign);
	for (i = 0; i < KETA; i++)
	{
		if (a->n[KETA-i-1] != 0)
		{
			startIndex = i;
			break;
		}
	}
	for (i = startIndex; i < KETA; i++)
	{
		printf("%2d", a->n[KETA-i-1]);
	}
}
void nextLine()
{
	putchar('\n');
}