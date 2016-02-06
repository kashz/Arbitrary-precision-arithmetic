#include <stdio.h>
#include <stdlib.h>
#include "bignum.h"
#include "accessor.h"
#include "bignumIO.h"

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
	{
		printf("%2d", a->n[KETA-i-1]);
	}
}
void dispNumberZeroSuppress(const struct NUMBER* a)
{
	int i, startIndex = 0;
	char sign;

	if (getSign(a) == POSITIVE)
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
void outputToLocalFile(const struct NUMBER* output_data)
{
	FILE* output_stream;
	int i;

	if ((output_stream = fopen("my.txt", "w+")) == NULL)
	{
		exit(EXIT_FAILURE);
	}

	fprintf(output_stream, "%d.", output_data->n[KETA-1]);
	for (i = KETA-2; i >= KETA-1000; i--)
	{
		fprintf(output_stream, "%d", output_data->n[i]);
	}
	fprintf(output_stream, "\n");
	fclose(output_stream);
}
