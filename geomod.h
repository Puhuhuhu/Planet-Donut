#ifndef GEOMOD_H
#define GEOMOD_H

struct point
{
	double x;
	double y;
};


bool equal_zero(double epsilon_zero, double val);

void setMax(double init_max);

double getMax();

double getEpsilon();

void coord_norm(double &val);

void coord_norm(point &p);

#endif




