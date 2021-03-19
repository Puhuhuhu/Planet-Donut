#ifndef GEOMOD_H
#define GEOMOD_H

struct Point
{
	double x;
	double y;
};

struct Vect
{
	double norme;
	double x;
	double y;
};

bool equal_zero(double epsilon_zero, double val);

void setMax(double init_max);

double getMax();

double getEpsilon();

void coord_norm(double &val);

void coord_norm(Point &p);

Vect distanceAB(Point &A, Point &B);

bool egalite(Point &p1, Point &p2);


#endif




