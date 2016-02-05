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
int isZero (const struct NUMBER*); // if a is zero, return 0;
void swap (struct NUMBER*, struct NUMBER*);
int numComp (const struct NUMBER*, const struct NUMBER*);
int isEven (const struct NUMBER* number);
int getTopDigitIndex(const struct NUMBER* number);
void copyPartition (const struct NUMBER* original, int firstIndex, int lastIndex, struct NUMBER* copied);   // first > last

#endif // __BIGNUM_H__
