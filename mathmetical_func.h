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

#endif // MATHMETICAL_FUNC
