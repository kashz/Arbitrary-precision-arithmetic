main : main.o bignum.o
	gcc -o main main.o bignum.o

.c.o :
	gcc -c $<
