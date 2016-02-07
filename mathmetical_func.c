#include "mathmetical_func.h"

int power(const struct NUMBER* a, const struct NUMBER* b, struct NUMBER* c)
{
    struct NUMBER i, tmp, one;
    struct NUMBER d, e;

    clearByZero(&i);
    clearByZero(&d);
    clearByZero(&e);


    if (isZero(a) == 0)
        return (-1);
    if (isZero(b) == 0)
    {
        setInt(c, 1);
        return (0);
    }
    if (getSign(b) == NEGATIVE)
        return (-1);

    setInt(&one, 1);
    if (numComp(b, &one)==0)
    {
        copyNumber(a, c);
        return 0;
    }
    copyNumber(a, &d);
    while (1)
    {
        directAdd(&i, &one);
        if (numComp(&i, b) >= 0)
            break;
        multiple(&d, a, &e);
        copyNumber(&e, &d);
    }
    copyNumber(&e, c);
    return (0);
}
// arctan(1/demon)*numer
int arctan(struct NUMBER* denom, struct NUMBER* solution)
{
	struct NUMBER one, two, count, divisor, prev_divisor;
	struct NUMBER shift, rem, increment, comm, denom_pow2;

	clearByZero(solution);
	clearByZero(&count);
	clearByZero(&comm);
	clearByZero(&shift);
	clearByZero(&denom_pow2);
	setInt(&one, 1);
	setInt(&two, 2);
	shift.n[KETA-1] = 1; // 10^(KETA-1) set

	// denom^2
	power(denom, &two, &denom_pow2);

	// First Term
	fast_divide(&shift, denom, &increment, &rem);
	directAdd(solution, &increment);
	copyNumber(denom, &prev_divisor);

	while (1)
	{
		directAdd(&count, &one);

		// 2n+1
		multiple(&count, &two, &comm);
        directAdd(&comm, &one);
		// (1/d)^2n+1
		multiple(&prev_divisor, &denom_pow2, &divisor);
		copyNumber(&divisor, &prev_divisor);
		// 2n+1*(1/d)^2n+1
		directMultiple(&divisor, &comm);

		if (numComp(&shift, &divisor) < 0)
			break;

		fast_divide(&shift, &divisor, &increment, &rem);
		if (isEven(&count) == 0)  // not even
			setSign(&increment, NEGATIVE);

		directAdd(solution, &increment);
	}

	return 0;
}
