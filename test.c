#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bignum.h"
#include "accessor.h"
#include "bignumIO.h"
#include "operation.h"
#include "mathmetical_func.h"

int main(void)
{
	struct NUMBER a, b, c, d, e, f, ans;
	int i, r, j;
	int num1, num2, num3;
	int x,y,z;
	clearByZero(&a);
	clearByZero(&b);
	clearByZero(&c);
	clearByZero(&d);
	clearByZero(&e);
    clearByZero(&f);
	clearByZero(&ans);

	srandom(time(NULL));

   for (i = 0; i < 100000; i++)
   {
        x = random()%100000+1;
        y = random()%100+1;
        if (random()%2) x *= -1;
        if (random()%2) y *= -1;
        setInt(&a, x);
        setInt(&b, y);
        setInt(&e, x*y);
        multiple(&a, &b, &c);
        if (numComp(&c, &e) != 0)
        {
            printf("error\n");
            dispNumber(&a);nextLine();
        	dispNumber(&b);nextLine();nextLine();
            dispNumber(&c);nextLine();
        	dispNumber(&e);nextLine();
        }
   }
	return (0);
}
