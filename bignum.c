#include "bignum.h"
#include "accessor.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void clearByZero(struct NUMBER* a)
{
	int i;

	for (i = 0; i < KETA; i++)
	{
		a->n [i] = 0;
	}
	setSign (a, 1);
}
void setRnd (struct NUMBER* a, int n)
{
	int i;

	if (n < 0 || 30 < n)
		printf("Out of range.");
	else
	{
		for (i = 0; i < KETA; i++)
		{
			if (i < n)
				a->n[i] = random()%10;
			else
				a->n[i] = 0;
		}
		if( random()%2 )
			setSign (a, 1);
		else
			setSign (a, -1);
	}
}
void copyNumber(const struct NUMBER* a, struct NUMBER* b)
{
	int i;

	setSign(b, getSign(a));
	for (i = 0; i < KETA; i++)
		b->n[i] = a->n[i];
}
void getAbs(const struct NUMBER* a, struct NUMBER* b)
{
	copyNumber(a, b);
	setSign(b, 1);
}
int isZero (const struct NUMBER* a)
{
	int i;

	for (i = 0; i < KETA; i++)
	{
		if (a->n[i] != 0)
			return (-1);
	}
	return (0);
}
void swap (struct NUMBER* a, struct NUMBER* b)
{
	struct NUMBER c;

	copyNumber(a, &c);
	copyNumber(b, a);
	copyNumber(&c, b);
}
int setInt (struct NUMBER* a, int x)
{
	int mod, i = 0;

	clearByZero (a);
	if (x < 0)
	{
		setSign(a, -1);
		x *= -1;
	}

	while (x > 0)
	{
		mod = x % 10;
		x -= mod;
		x /= 10;
		a->n[i++] = mod;
		if (i > KETA)
			return -1;
	}

	return 0;
}
int numComp (const struct NUMBER* a, const struct NUMBER* b)
{
	int i;

	if (getSign(a) == 1 && getSign(b) == -1)
		return 1;
	else if (getSign(a) == -1 && getSign(b) == 1)
		return -1;
	else if (getSign(a) == 1 && getSign(b) == 1)
	{
		for (i = 0; i < KETA; i++)
		{
			if (a->n[KETA-i-1] > b->n[KETA-i-1])
				return 1;
			else if (a->n[KETA-i-1] < b->n[KETA-i-1])
				return -1;
		}
		return 0;
	}
	else if (getSign(a) == -1 && getSign(b) == -1)
	{
		for (i = 0; i < KETA; i++)
		{
			if (a->n[KETA-i-1] > b->n[KETA-i-1])
				return -1;
			else if (a->n[KETA-i-1] < b->n[KETA-i-1])
				return 1;
		}
		return 0;
	}
	return (-1);
}
int isEven (const struct NUMBER* number)
{
	if (number->n[0]%2 == 0)
		return 1;
	else if (number->n[0]%2 == 1)
		return 0;

	return -1;
}
int getTopDigitIndex(const struct NUMBER* number)
{
	int i;
	for (i = KETA - 1; i >= 0; i--)
	{
		if (number->n[i] != 0)
			break;
	}
	return i;
}
void copyPartition (const struct NUMBER* original, int firstIndex, int lastIndex, struct NUMBER* copied)
{
	int i;

	for (i = firstIndex; i >= lastIndex; i--)
	{
		copied->n[i-lastIndex] = original->n[i];
	}
}
