#ifndef __BIGNUM_H__
#define __BIGNUM_H__

#define KETA 30

struct NUMBER
{
	int n [KETA];
	int sign;
};

/*********************************/

void clearByZero(struct NUMBER*);
void setRnd (struct NUMBER*, int);
int setInt (struct NUMBER*, int);
void copyNumber(const struct NUMBER*, struct NUMBER*);
void getAbs(const struct NUMBER*, struct NUMBER*);
int isZero (const struct NUMBER*);
void swap (struct NUMBER*, struct NUMBER*);
int numComp (const struct NUMBER*, const struct NUMBER*);







#endif // __BIGNUM_H__