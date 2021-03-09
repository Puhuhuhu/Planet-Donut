#include <iostream>
#include <cmath>
#include "geomod.h"


static double epsilon_zero(0);
static double max(0);

bool equal_zero(double val)
{
	if (abs(val) < epsilon_zero){
		return true;
	}else{
		return false;
	}
}

void setMax(double init_max)
{
	max = init_max;
	epsilon_zero = pow(10, -10)*max;
}

double getMax()
{
	return max;
}

double getEpsilon()
{
	return epsilon_zero;
}






