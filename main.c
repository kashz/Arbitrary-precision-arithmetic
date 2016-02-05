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

// arctan(1/demon)*numer
int arctan(struct NUMBER* denom, struct NUMBER* solution)
{
	struct NUMBER prev_answer, denom_pow2;
	struct NUMBER one, two, count, divisor, comm;
	struct NUMBER shift, rem, quo;
	struct NUMBER increment, prev_increment;
	struct NUMBER tmp, prev_divisor;

	clearByZero(solution);
	clearByZero(&count);
	clearByZero(&comm);
	clearByZero(&shift);
	clearByZero(&denom_pow2);
	setInt(&one, 1);
	setInt(&two, 2);
	shift.n[KETA-1] = 1; // 10^(KETA-1) set

	// denom^2
	power(denom, &two, &denom_pow2);

	// First Term
	fast_divide(&shift, denom, &increment, &rem);
	directAdd(solution, &increment);
	copyNumber(&increment, &prev_increment);
	copyNumber(denom, &prev_divisor);

	while (1)
	{
		directAdd(&count, &one);

		// 2n+1
		multiple(&count, &two, &comm);
        directAdd(&comm, &one);
		// (1/d)^2n+1
		multiple(&prev_divisor, &denom_pow2, &divisor);
		copyNumber(&divisor, &prev_divisor);
		// 2n+1*(1/d)^2n+1
		directMultiple(&divisor, &comm);

		if (numComp(&shift, &divisor) < 0)
			break;

		fast_divide(&shift, &divisor, &increment, &rem);
		if (isEven(&count) == 0)
			setSign(&increment, NEGATIVE);

		directAdd(solution, &increment);
	}

	return 0;
}

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
