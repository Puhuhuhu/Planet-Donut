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

void coord_norm(double &val)
{
	if (val > max){val = val-2*max;}
	if (val < -max){val = val+2*max;}
}

void coord_norm(point &p)
{
	if ((p.x) > max){p.x = p.x-2*max;}
	if ((p.x) < -max){p.x = p.x+2*max;}
	if ((p.y) > max){p.y = p.y-2*max;}
	if ((p.y) < -max){p.y = p.y+2*max;}
}





