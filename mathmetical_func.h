#ifndef MATHMETICAL_FUNC
#define MATHMETICAL_FUNC

#include "bignum.h"
#include "accessor.h"
#include "operation.h"

// c = a^b
int power (const struct NUMBER* a, const struct NUMBER* b, struct NUMBER* c);
// If a is prime, return 1.
int isPrime(const struct NUMBER* a);
// Euclidean algorithm
int gcd (const struct NUMBER* a, const struct NUMBER* b, struct NUMBER* c);
//
int lcm (const struct NUMBER* a, const struct NUMBER* b, struct NUMBER* c);
int simple_sqrt(const struct NUMBER* sq, struct NUMBER* min_int);
// arctan(1/demon)*numer
int arctan(struct NUMBER* denom, struct NUMBER* solution);


#endif // MATHMETICAL_FUNC
