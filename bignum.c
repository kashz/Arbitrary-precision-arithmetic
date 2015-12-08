#include "bignum.h"

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

void clearByZero(struct NUMBER* a)
{
	int i;

	for (i = 0; i < KETA; i++)
	{
		a->n [i] = 0;
	}
	setSign (a, 1);
}
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