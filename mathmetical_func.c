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
