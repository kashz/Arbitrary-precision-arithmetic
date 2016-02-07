#include "bignum.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void setSign (struct NUMBER* a, int s)
{
	if (s == POSITIVE)
		a->sign = POSITIVE;
	else if (s == NEGATIVE)
		a->sign = NEGATIVE;
}
int getSign (const struct NUMBER* a)
{
	int sign = 0;
	if (a->sign == POSITIVE)
		sign = POSITIVE;
	else if (a->sign == NEGATIVE)
		sign = NEGATIVE;

	return sign;
}
void clearByZero(struct NUMBER* a)
{
	int i;

	for (i = 0; i < KETA; i++)
		a->n [i] = 0;
	setSign (a, POSITIVE);
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
	setSign(b, POSITIVE);
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

	if (getSign(a) == POSITIVE && getSign(b) == NEGATIVE)
		return 1;
	else if (getSign(a) == NEGATIVE && getSign(b) == POSITIVE)
		return -1;
	else if (getSign(a) == POSITIVE && getSign(b) == POSITIVE)
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
	else if (getSign(a) == NEGATIVE && getSign(b) == NEGATIVE)
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

	setSign(copied, getSign(original));
	for (i = firstIndex; i >= lastIndex; i--)
		copied->n[i-lastIndex] = original->n[i];
}
void dispNumber(const struct NUMBER* a)
{
	int i;
	char sign;

	if (getSign(a) == POSITIVE)
		sign = '+';
	else
		sign = '-';
	printf("%c", sign);
	for (i = 0; i < KETA; i++)
		printf("%2d", a->n[KETA-i-1]);
}
void outputToLocalFile(const struct NUMBER* output_data)
{
	FILE* output_stream;
	int i;

	if ((output_stream = fopen("my.txt", "w+")) == NULL)
		exit(EXIT_FAILURE);

	fprintf(output_stream, "%d.", output_data->n[KETA-1]);
	for (i = KETA-2; i >= 0; i--)
		fprintf(output_stream, "%d", output_data->n[i]);
	fprintf(output_stream, "\n");
	fclose(output_stream);
}
