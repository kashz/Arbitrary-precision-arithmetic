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
    {
        return (-1);
    }

    setInt(&one, 1);
    if (numComp(b, &one)==0)
    {
        copyNumber(a, c);
        return 0;
    }
    copyNumber(a, &d);
    while (1)
    {
        increment(&i, &tmp);
        i = tmp;
        if (numComp(&i, b) >= 0)
            break;
        multiple(&d, a, &e);
        copyNumber(&e, &d);
    }
    copyNumber(&e, c);
    return (0);
}
int isPrime(const struct NUMBER* a)
{
    int i;
    struct NUMBER one, two;
    struct NUMBER result, d, e, remainder;

    if (getSign(a) == NEGATIVE)
        return 0;
    setInt(&one, 1);
    if (numComp(a, &one) == 0)
        return 1;
    setInt(&two, 2);
    if (numComp(a, &two) == 0)
        return 1;
    divide(a, &two, &result, &remainder);
    if (isZero(&remainder) == 0)
    {
        return 0;
    }

    setInt(&d, 3);
    while(1)
    {
        if (numComp(a, &d) <= 0)
            break;
        divide(a, &d, &result, &remainder);
        if (isZero(&remainder) == 0)
            return 0;
        directAdd(&d, &two);
    }
    return 1;
}

int gcd (const struct NUMBER* a, const struct NUMBER* b, struct NUMBER* c)
{
    struct NUMBER bigger, smaller, quotient, remainder;
    int r_comp;

    r_comp = numComp(a, b);
    if (r_comp > 0)
    {
        copyNumber(a, &bigger);
        copyNumber(b, &smaller);
    }
    else if (r_comp == 0)
    {
        copyNumber(a, c);
        return 0;
    }
    else if (r_comp < 0)
    {
        copyNumber(a, &smaller);
        copyNumber(b, &bigger);
    }

    while (1)
    {
        divide(&bigger, &smaller, &quotient, &remainder);
        if (isZero(&remainder) == 0)
            break;
        copyNumber(&smaller, &bigger);
        copyNumber(&remainder, &smaller);
    }
    copyNumber(&smaller, c);
    return 0;
}

int lcm (const struct NUMBER* a, const struct NUMBER* b, struct NUMBER* c)
{
    struct NUMBER gcd_val, ans, re, q;

    gcd(a, b, &gcd_val);
    divide(a, &gcd_val, &q, &re);
    multiple(&q, b, &ans);

    copyNumber(&ans, c);
    return 0;
}
int simple_sqrt(const struct NUMBER* sq, struct NUMBER* min_int)
{
    struct NUMBER N, sub_val, two;

    if (getSign(sq) == NEGATIVE)
        return -1;

    setInt(&sub_val, 1);
    setInt(&two, 2);
    copyNumber(sq, &N);
    while(numComp(&N, &sub_val) >= 0)
    {
        directSub(&N, &sub_val);
        directAdd(&sub_val, &two);
    }

    copyNumber(&N, min_int);
    return 0;
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
