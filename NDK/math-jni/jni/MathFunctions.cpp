#include "MathFunctions.h"

float power(float base, int exponent){
	
	float result = 1;
	while(exponent--) result *= base;
	return exponent > 0 ? result : (float)(1) / result;
}