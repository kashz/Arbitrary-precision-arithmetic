#include "bignum.h"
#include "accessor.h"

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
