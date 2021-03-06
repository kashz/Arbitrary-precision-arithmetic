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

	if (a_sign == POSITIVE && b_sign == POSITIVE)
	{
		for (i = 0; i < KETA; i++)
		{
			d = a->n[i] + b->n[i] + carry;
			c->n[i] = (d % 10);
			carry = d / 10;
		}
		if (carry != 0)
		{
			setSign(c, POSITIVE);
			return -1;
		}
		else
		{
			setSign(c, POSITIVE);
			return 0;
		}
	}
	else if (a_sign == POSITIVE && b_sign == NEGATIVE)
	{
		getAbs(b, &abs_b);
		retVal = sub(a, &abs_b, c);
		return retVal;
	}
	else if (a_sign == NEGATIVE && b_sign == POSITIVE)
	{
		getAbs(a, &abs_a);
		retVal = sub(b, &abs_a, c);
		return retVal;
	}
	else if (a_sign == NEGATIVE && b_sign == NEGATIVE)
	{
		getAbs(a, &abs_a);
		getAbs(b, &abs_b);
		retVal = add(&abs_a, &abs_b, c);
		setSign(c, NEGATIVE);
		return retVal;
	}
	return -1;
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

	if (a_sign == POSITIVE && b_sign == POSITIVE)
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
				setSign(c, POSITIVE);
				return -1;
			}
			else
			{
				setSign(c, POSITIVE);
				return 0;
			}
		}

		else if (isComp == 0)
			clearByZero(c);

		else if (isComp == -1)
		{
			retVal = sub(b, a, c);
			setSign(c, NEGATIVE);
			return retVal;
		}
	}
	else if (a_sign == POSITIVE && b_sign == NEGATIVE)
	{
		getAbs(b, &abs_b);
		retVal = add(a, &abs_b, c);
		return retVal;
	}
	else if (a_sign == NEGATIVE && b_sign == POSITIVE)
	{
		getAbs (a, &abs_a);
		retVal = add(&abs_a, b, c);
		setSign(c, -1);
		return retVal;
	}
	else if (a_sign == NEGATIVE && b_sign == NEGATIVE)
	{
		getAbs (a, &abs_a);
		getAbs (b, &abs_b);
		sub (&abs_b, &abs_a, c);
		return retVal;
	}
	return -1;
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
int directShiftLeft(struct NUMBER* number, int nBit)
{
	int status;
	struct NUMBER tmp;
	copyNumber(number, &tmp);
	status = shiftLeft (&tmp, number, nBit);
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
	int status = -1;

	if (isZero(a) == 0 || isZero(b) == 0)
	{
		status = 0;
		clearByZero(result);
	}
	else if (getSign(a) == POSITIVE && getSign(b) == POSITIVE)
	{
		clearByZero(result);
		for (i = 0; i < KETA; i++)
		{
			if (b->n[i] == 0)
				continue;
			oneDigitMultiple (a, b->n[i], &d);
			shiftLeft(&d, &e, i);
			status = directAdd(result, &e);
			if (status == -1)
			{
				break;
				printf("multiple error");
			}
		}
	}
	else if (getSign(a) == POSITIVE && getSign(b) == NEGATIVE)
	{
		getAbs(b, &abs_b);
		status = multiple(a, &abs_b, result);
		setSign(result, NEGATIVE);
	}
	else if (getSign(a) == NEGATIVE && getSign(b) == POSITIVE)
	{
		getAbs(a, &abs_a);
		status = multiple(&abs_a, b, result);
		setSign(result, NEGATIVE);
	}
	else if (getSign(a) == NEGATIVE && getSign(b) == NEGATIVE)
	{
		getAbs(a, &abs_a);
		getAbs(b, &abs_b);
		status = multiple (&abs_a, &abs_b, result);
	}
	return status;
}
int directSub (struct NUMBER* minuend, const struct NUMBER* subtrahend)
{
    struct NUMBER tmp;
	int status;

	copyNumber(minuend, &tmp);
	status = sub(&tmp, subtrahend, minuend);

	return (status);
}
int directMultiple (struct NUMBER* multiplicand, const struct NUMBER* multiplier)
{
	struct NUMBER tmp;
	int status;
	copyNumber(multiplicand, &tmp);
	status = multiple(&tmp, multiplier, multiplicand);
	return status;
}

int divide (const struct NUMBER* divend, const struct NUMBER* divisor, struct NUMBER* quotient, struct NUMBER* remainder)
{
	struct NUMBER dived, diver, quo, rem;
	struct NUMBER one;
	int status;

	if (isZero(divisor) == 0)
	{
		clearByZero(quotient);
		clearByZero(remainder);
		return -1;                 // divide by zero error
	}

	if (getSign(divend) == POSITIVE && getSign(divisor) == POSITIVE)
	{
		copyNumber(divend, &dived);
		copyNumber(divisor, &diver);
		clearByZero(&quo);
		clearByZero(&rem);
		setInt(&one, 1);

		while(numComp(&dived, &diver) >= 0)
		{
			directSub(&dived, &diver);
			directAdd(&quo, &one);
		}
		copyNumber(&quo, quotient);
		copyNumber(&dived, remainder);
		return 0;
	}
	else if (getSign(divend) == POSITIVE && getSign(divisor) == NEGATIVE)
	{
		getAbs(divisor, &diver);
		status = divide(divend, &diver, quotient, remainder);
		if(isZero(quotient) != 0)
			setSign(quotient, NEGATIVE);
		return status;
	}
	else if (getSign(divend) == NEGATIVE && getSign(divisor) == POSITIVE)
	{
		getAbs(divend, &dived);
		status = divide(&dived, divisor, quotient, remainder);
		if (isZero(quotient) != 0)
			setSign(quotient, NEGATIVE);
		if (isZero(remainder) != 0)
			setSign(remainder, NEGATIVE);
		return status;
	}
	else if (getSign(divend) == NEGATIVE && getSign(divisor) == NEGATIVE)
	{
		getAbs(divend, &dived);
		getAbs(divisor, &diver);
		status = divide(&dived, &diver, quotient, remainder);
		if (isZero(remainder) != 0)
			setSign(remainder, NEGATIVE);
		return status;
	}
	return -1;
}

int fast_divide (const struct NUMBER* divend, const struct NUMBER* divisor, struct NUMBER* quotient, struct NUMBER* remainder)
{
	int divendTopDigitIndex, divisorTopDigitIndex, firstIndex;
	int status;
	struct NUMBER partition, quo, rem, positive_divend, positive_divisor;

	if (isZero(divisor) == 0)
	{
		clearByZero(quotient);
		clearByZero(remainder);
		return -1;
	}
	else if (isZero(divend) == 0)
	{
		clearByZero(quotient);
		clearByZero(remainder);
		return 0;
	}

	if (getSign(divend) == POSITIVE && getSign(divisor) == POSITIVE)
	{
		if (numComp(divend, divisor) < 0)
		{
			clearByZero(quotient);
			copyNumber(divend, remainder);
			return 0;
		}

		divendTopDigitIndex  = getTopDigitIndex(divend);
		divisorTopDigitIndex = getTopDigitIndex(divisor);
		clearByZero(quotient);
		clearByZero(remainder);
		clearByZero(&quo);
		clearByZero(&rem);
		clearByZero(&partition);

		if (divend->n[divendTopDigitIndex] < divisor->n[divisorTopDigitIndex])
		{
			copyPartition(divend, divendTopDigitIndex, divendTopDigitIndex - divisorTopDigitIndex - 1, &partition);
		}
		else
		{
			copyPartition(divend, divendTopDigitIndex, divendTopDigitIndex - divisorTopDigitIndex, &partition);
		}
		firstIndex = divendTopDigitIndex - getTopDigitIndex(&partition);

		while (1)
		{
			//printf("par:"); dispNumber(&partition); nextLine();
			status = divide(&partition, divisor, &quo, &rem);
			//printf("quo:"); dispNumber(&quo); nextLine();
			//printf("rem:"); dispNumber(&rem); nextLine();
			quotient->n[firstIndex--] = quo.n[0];
			if (firstIndex < 0)
				break;
			copyNumber(&rem, &partition);
			directShiftLeft(&partition, 1);
			partition.n[0] = divend->n[firstIndex];
		}
		copyNumber(&rem, remainder);
		return status;
	}
	else if (getSign(divend) == POSITIVE && getSign(divisor) == NEGATIVE)
	{
		getAbs (divisor, &positive_divisor);
		status = fast_divide(divend, &positive_divisor, quotient, remainder);
		if(isZero(quotient) != 0)
			setSign(quotient, NEGATIVE);
		return status;
	}
	else if (getSign(divend) == NEGATIVE && getSign(divisor) == POSITIVE)
	{
		getAbs (divend, &positive_divend);
		status = fast_divide(&positive_divend, divisor, quotient, remainder);
		if (isZero(quotient) != 0)
			setSign(quotient, NEGATIVE);
		if (isZero(remainder) != 0)
			setSign(remainder, NEGATIVE);
		return status;
	}
	else if (getSign(divend) == NEGATIVE && getSign(divisor) == NEGATIVE)
	{
		getAbs (divend, &positive_divend);
		getAbs (divisor, &positive_divisor);
		status = fast_divide(&positive_divend, &positive_divisor, quotient, remainder);
		if (isZero(remainder) != 0)
			setSign(remainder, NEGATIVE);
		return status;
	}
	return -1;
}
