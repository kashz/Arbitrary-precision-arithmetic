#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "bignum.h"
#include "accessor.h"
#include "bignumIO.h"
#include "operation.h"
#include "mathmetical_func.h"


/*********************************/



int main(void)
{
	struct NUMBER solution;
	struct NUMBER arctan_denom, arctan_solution;
	struct NUMBER multiplier;
	struct timeval tv;
	double tstart, tend;

	gettimeofday(&tv, NULL);
	tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;


	clearByZero(&solution);
	clearByZero(&arctan_denom);
	clearByZero(&arctan_solution);
	clearByZero(&multiplier);

	// 48*arctan(1/18)
	setInt(&arctan_denom, 18);
	arctan(&arctan_denom, &arctan_solution);
	setInt(&multiplier, 48);
	directMultiple(&arctan_solution, &multiplier);
	directAdd(&solution, &arctan_solution);

	// 32*arctan(1/57)
	setInt(&arctan_denom, 57);
	arctan(&arctan_denom, &arctan_solution);
	setInt(&multiplier, 32);
	directMultiple(&arctan_solution, &multiplier);
	directAdd(&solution, &arctan_solution);

	// -20*arctan(1/239)
	setInt(&arctan_denom, 239);
	arctan(&arctan_denom, &arctan_solution);
	setInt(&multiplier, 20);
	directMultiple(&arctan_solution, &multiplier);
	directSub(&solution, &arctan_solution);

	outputToLocalFile(&solution);


	gettimeofday(&tv, NULL);
	tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;

	printf("Execution Time:%lf\n", tend - tstart);

	return (0);
}
