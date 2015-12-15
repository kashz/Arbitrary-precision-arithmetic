#ifndef __OPERATION_H__
#define __OPERATION_H__

int mulBy10(const struct NUMBER*, struct NUMBER*);
int divBy10 (const struct NUMBER*, struct NUMBER*);

int add (const struct NUMBER*, const struct NUMBER*, struct NUMBER*);
int directAdd(struct NUMBER* addedNum, struct NUMBER* addNum);
int increment (const struct NUMBER*, struct NUMBER*);

int sub (const struct NUMBER*, const struct NUMBER*, struct NUMBER*);
int decrement (const struct NUMBER*, struct NUMBER*);

int oneDigitMultiple (const struct NUMBER* a, int oneDigitNum, struct NUMBER* result);
int multiple (const struct NUMBER*, const struct NUMBER*, struct NUMBER*);

int shiftLeft (const struct NUMBER* a, struct NUMBER* b, int nBit);



#endif //__OPERATION_H__