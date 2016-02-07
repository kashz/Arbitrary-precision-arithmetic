#ifndef MATHMETICAL_FUNC
#define MATHMETICAL_FUNC

#include "bignum.h"
#include "operation.h"

// c = a^b
int power (const struct NUMBER* a, const struct NUMBER* b, struct NUMBER* c);
// arctan(1/demon)*numer
int arctan(struct NUMBER* denom, struct NUMBER* solution);


#endif // MATHMETICAL_FUNC
