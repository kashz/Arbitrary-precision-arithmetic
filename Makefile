main : main.o bignum.o bignumIO.o accessor.o operation.o
	gcc -o main main.o bignum.o bignumIO.o accessor.o operation.o

.c.o :
	gcc -c $<
