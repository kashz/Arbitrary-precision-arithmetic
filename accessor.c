#include "bignum.h"
#include "accessor.h"

void setSign (struct NUMBER* a, int s)
{
	if (s == 1)
		a->sign = 1;
	else if (s == -1)
		a->sign = -1;
}
int getSign (const struct NUMBER* a)
{
	if (a->sign == 1)
		return 1;
	else if (a->sign == -1)
		return -1;
}
