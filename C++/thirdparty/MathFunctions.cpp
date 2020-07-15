#include "MathFunctions.h"

double power(double base, int exponent){
	
	double result = 1;
	while(exponent--) result *= base;
	return exponent > 0 ? result : (double)(1) / result;
}