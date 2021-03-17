#ifndef GEOMOD_H
#define GEOMOD_H

struct Point
{
	double x;
	double y;
};


bool equal_zero(double epsilon_zero, double val);

void setMax(double init_max);

double getMax();

double getEpsilon();

void coord_norm(double &val);

void coord_norm(Point &p);

void distanceAB(Point &A, Point &B);


#endif




