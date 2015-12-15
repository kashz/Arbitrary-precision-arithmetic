#include <stdio.h>
#include <stdlib.h>
#include "bignum.h"
#include "accessor.h"
#include "bignumIO.h"
#include "operation.h"

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

	setInt(&a, 1234);
	setInt(&b, 568);
	multiple(&a, &b, &c);
	//directAdd (&a, &b);
	printf("c = ");
	dispNumber(&c);
	nextLine();
	return (0);
}