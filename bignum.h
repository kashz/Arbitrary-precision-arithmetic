#ifndef __BIGNUM_H__
#define __BIGNUM_H__

#define KETA 1050
#define POSITIVE (1)
#define NEGATIVE (-1)

struct NUMBER
{
	int n [KETA];
	int sign;
};

// setter
void setSign (struct NUMBER* a, int s);
// getter
int getSign (const struct NUMBER* a);
void clearByZero(struct NUMBER*);
int setInt (struct NUMBER*, int);
void copyNumber(const struct NUMBER*, struct NUMBER*);
void getAbs(const struct NUMBER*, struct NUMBER*);
int isZero (const struct NUMBER*); // if a is zero, return 0;
int numComp (const struct NUMBER*, const struct NUMBER*);
int isEven (const struct NUMBER* number);
int getTopDigitIndex(const struct NUMBER* number);
void copyPartition (const struct NUMBER* original, int firstIndex, int lastIndex, struct NUMBER* copied);   // first > last

// OUTPUT
void dispNumber(const struct NUMBER*);
void outputToLocalFile(const struct NUMBER* output_data);

#endif // __BIGNUM_H__
