#include <stdio.h>
#include <stdlib.h>
#include "bignum.h"

int simpleMultiple (int a, int b, int* c)
{
	int status = 0;
	int i;

	*c = 0;
	for (i = 0; i < b; ++i)
	{
		*c += a;
	}

	return status;
}

/*********************************/

int main(void)
{
	struct NUMBER a, b, c, d, e, f;
	int i, r;
	int num1, num2, num3;
	int x,y,z;
	clearByZero(&a);
	clearByZero(&b);

	srandom(time(NULL));

	for (i = 0; i < 9000000; i++)
	{
		num1 = random()%10000;
		num2 = random()%10000;
		if (random()%2 == 1)
			num1 *= -1;
		if (random()%2 == 1)
			num2 *= -1;
		setInt(&a, num1);
		setInt(&b, num2);
		setInt(&e, (num1+num2));
		setInt(&f, (num1-num2));
		x = add(&a, &b, &c);
		y = sub(&a, &b, &d);

		if(numComp(&e, &c)||numComp(&f, &d))
		{
			printf("%d , %d\n", num1, num2);
			printf("a = ");
			dispNumber(&a);
			nextLine();
			printf("b = ");
			dispNumber(&b);
			nextLine();
			if (x == -1)
				printf("error\n");
			else
			{
				printf("c = ");
				dispNumber(&c);
				nextLine();
			}
			printf("e = ");
			dispNumber(&e);
			nextLine();
			if (y == -1)
				printf("error\n");
			else
			{
				printf("d = ");
				dispNumber(&d);
				nextLine();
			}
			printf("f = ");
			dispNumber(&f);
			nextLine();
			nextLine();
		}
	}

	return (0);
}