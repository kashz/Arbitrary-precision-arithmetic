#ifndef __BIGNUM_H__
#define __BIGNUM_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KETA 30

struct NUMBER
{
	int n [KETA];
	int sign;
};

/*********************************/

void clearByZero(struct NUMBER*);
void dispNumber(const struct NUMBER*);
void nextLine();
void dispNumberZeroSuppress(const struct NUMBER*);
void setRnd (struct NUMBER*, int);
void copyNumber(const struct NUMBER*, struct NUMBER*);
void getAbs(const struct NUMBER*, struct NUMBER*);
int isZero (const struct NUMBER*);
int mulBy10(const struct NUMBER*, struct NUMBER*);
int divBy10 (const struct NUMBER*, struct NUMBER*);
void swap (struct NUMBER*, struct NUMBER*);
int setInt (struct NUMBER*, int);
int numComp (const struct NUMBER*, const struct NUMBER*);
int add (const struct NUMBER*, const struct NUMBER*, struct NUMBER*);
int sub (const struct NUMBER*, const struct NUMBER*, struct NUMBER*);

/*********************************/
// getter, setter
void setSign (struct NUMBER* a, int s);
int getSign (const struct NUMBER* a);
/*********************************/


#endif // __BIGNUM_H__