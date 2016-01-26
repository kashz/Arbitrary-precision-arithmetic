main : main.o bignum.o bignumIO.o accessor.o operation.o mathmetical_func.o
	gcc -o main main.o bignum.o bignumIO.o accessor.o operation.o mathmetical_func.o

.c.o :
	gcc -c $<
clean :
	rm *.o
