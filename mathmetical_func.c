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
    if (getSign(b) == -1)
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

    if (getSign(a) == -1)
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
