#include "bignum.h"
#include "operation.h"
#include "accessor.h"
#include <stdio.h>

int mulBy10(const struct NUMBER* a, struct NUMBER* b)
{
	int i, retVal;

	if(a->n[KETA-1] == 0)
		retVal = 0;
	else
		retVal = -1;

	for (i = 0; i < KETA-1; i++)
	{
		b->n[i+1] = a->n[i];
	}
	b->n[0] = 0;
	setSign (b, getSign(a));

	return retVal;
}
int divBy10 (const struct NUMBER* a, struct NUMBER* b)
{
	int i, mod;

	mod = getSign(a) * a->n[0];

	for (i = 1; i < KETA; i++)
	{
		b->n[i-1] = a->n[i];
	}
	b->n[KETA-1] = 0;
	setSign(b, getSign(a));
	return mod;
}
int add (const struct NUMBER* a, const struct NUMBER* b, struct NUMBER* c)
{
	int i;
	int d, carry = 0, retVal;
	struct NUMBER abs_a, abs_b;
	int a_sign, b_sign;

	a_sign = getSign(a);
	b_sign = getSign(b);

	if (a_sign == 1 && b_sign == 1)
	{
		for (i = 0; i < KETA; i++)
		{
			d = a->n[i] + b->n[i] + carry;
			c->n[i] = (d % 10);
			carry = d / 10;
		}
		if (carry != 0)
		{
			setSign(c, 1);
			return -1;
		}
		else
		{
			setSign(c, 1);
			return 0;
		}
	}
	else if (a_sign == 1 && b_sign == -1)
	{
		getAbs(b, &abs_b);
		retVal = sub(a, &abs_b, c);
		return retVal;
	}
	else if (a_sign == -1 && b_sign == 1)
	{
		getAbs(a, &abs_a);
		retVal = sub(b, &abs_a, c);
		return retVal;
	}
	else if (a_sign == -1 && b_sign == -1)
	{
		getAbs(a, &abs_a);
		getAbs(b, &abs_b);
		retVal = add(&abs_a, &abs_b, c);
		setSign(c, -1);
		return retVal;
	}
}

int sub (const struct NUMBER* a, const struct NUMBER* b, struct NUMBER* c)
{
	int i, tmp;
	int d, borrow = 0;
	int retVal;
	int isComp;
	struct NUMBER abs_a, abs_b;
	int a_sign, b_sign;

	a_sign = getSign(a);
	b_sign = getSign(b);

	if (a_sign == 1 && b_sign == 1)
	{
		isComp = numComp(a, b);
		if (isComp == 1)
		{
			for (i = 0; i < KETA; i++)
			{
				tmp = a->n[i] - borrow;
				if (tmp >= b->n[i])
				{
					c->n[i] = tmp - b->n[i];
					borrow = 0;
				}
				else if (tmp < b->n[i])
				{
					c->n[i] = 10 + tmp - b->n[i];
					borrow = 1;
				}
			}
			if (borrow != 0)
			{
				setSign(c, 1);
				return -1;
			}
			else
			{
				setSign(c, 1);
				return 0;
			}
		}

		else if (isComp == 0)
			clearByZero(c);

		else if (isComp == -1)
		{
			retVal = sub(b, a, c);
			setSign(c, -1);
			return retVal;
		}
	}
	else if (a_sign == 1 && b_sign == -1)
	{
		getAbs(b, &abs_b);
		retVal = add(a, &abs_b, c);
		return retVal;
	}
	else if (a_sign == -1 && b_sign == 1)
	{
		getAbs (a, &abs_a);
		retVal = add(&abs_a, b, c);
		setSign(c, -1);
		return retVal;
	}
	else if (a_sign == -1 && b_sign == -1)
	{
		getAbs (a, &abs_a);
		getAbs (b, &abs_b);
		sub (&abs_b, &abs_a, c);
		return retVal;
	}
}
int increment (const struct NUMBER* a, struct NUMBER * b)
{
	struct NUMBER one;
	int r;
	setInt(&one, 1);
	r = add(a, &one, b);

	return (r);
}
int decrement (const struct NUMBER* a, struct NUMBER* b)
{
	struct NUMBER one;
	int r;
	setInt(&one, 1);
	r = sub(a, &one, b);

	return (r);
}
int oneDigitMultiple (const struct NUMBER* a, int oneDigitNum, struct NUMBER* result)
{
	int i, d;
	int h = 0;
	int status = 0;

	clearByZero (result);

	for (i = 0; i < KETA; i++)
	{
		d = a->n[i] * oneDigitNum + h;
		result->n[i] = d % 10;
		h = d / 10;
	}
	if (h != 0)
	{
		status = -1;
	}

	return status;
}
int shiftLeft (const struct NUMBER* a, struct NUMBER* b, int nBit)
{
	int i;
	int status = 0;

	if (nBit == 0)
	{
		copyNumber(a, b);
	}
	else if (nBit < KETA)
	{
		clearByZero(b);
		for (i = 0; i < KETA; i++)
		{
			b->n[nBit + i] = a->n[i];
		}
		if (a->n[KETA-nBit] != 0)
		{
			status = -1;
		}
		setSign(b, getSign(a));
	}
	else
	{
		status = -1;
	}
	return status;
}
int directAdd(struct NUMBER* addedNum, const struct NUMBER* addNum)
{
	struct NUMBER tmp;
	int status;

	copyNumber(addedNum, &tmp);
	status = add(&tmp, addNum, addedNum);

	return (status);
}
int multiple (const struct NUMBER* a, const struct NUMBER* b, struct NUMBER* result)
{
	int i, j;
	struct NUMBER d, e, f;
	struct NUMBER abs_a, abs_b;
	int status;

	if (isZero(a) == 0 || isZero(b) == 0)
	{
		status = 0;
		clearByZero(result);
	}
	else if (getSign(a) == 1 && getSign(b) == 1)
	{
	clearByZero(result);
	for (i = 0; i < KETA; i++)
		{
			oneDigitMultiple (a, b->n[i], &d);
			if (isZero(&d) == -1)
			{
				shiftLeft(&d, &e, i);
				status = directAdd(result, &e);
				if (status == -1)
				{
					break;
					printf("multiple error");
				}
			}
		}
	}
	else if (getSign(a) == 1 && getSign(b) == -1)
	{
		getAbs(b, &abs_b);
		status = multiple(a, &abs_b, result);
		setSign(result, -1);
	}
	else if (getSign(a) == -1 && getSign(b) == 1)
	{
		getAbs(a, &abs_a);
		status = multiple(&abs_a, b, result);
		setSign(result, -1);
	}
	else if (getSign(a) == -1 && getSign(b) == -1)
	{
		getAbs(a, &abs_a);
		getAbs(b, &abs_b);
		status = multiple (&abs_a, &abs_b, result);
	}
	return status;
}