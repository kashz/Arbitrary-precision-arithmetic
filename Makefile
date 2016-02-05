main : main.o bignum.o bignumIO.o accessor.o operation.o mathmetical_func.o
	gcc -o main main.o bignum.o bignumIO.o accessor.o operation.o mathmetical_func.o
test : test.o bignum.o bignumIO.o accessor.o operation.o mathmetical_func.o
	gcc -o test test.o bignum.o bignumIO.o accessor.o operation.o mathmetical_func.o
.c.o :
	gcc -c $<
clean :
	-rm main main.o bignum.o bignumIO.o accessor.o operation.o mathmetical_func.o test test.o
