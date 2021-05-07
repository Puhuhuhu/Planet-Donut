#include <iostream>
#include <cmath>
#include "geomod.h"
#include "graphic.h"


static double epsilon_zero(0);
static double max(0);

bool equal_zero(double val)
{
	if (sqrt(pow(val, 2)) < epsilon_zero){
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

void coord_norm(Point &p)
{
	if ((p.x) > max){p.x = p.x-2*max;}
	if ((p.x) < -max){p.x = p.x+2*max;}
	if ((p.y) > max){p.y = p.y-2*max;}
	if ((p.y) < -max){p.y = p.y+2*max;}
}

Vect distanceAB(Point &A, Point &B)
{
	coord_norm(A);
	double petit_norm(2*getMax()), petit_x, petit_y;
	for(int k = -1; k < 2; k++){
		//faire varier la position de B selon x
		double B_plan_x = B.x + k * 2* getMax();
		double distanceX(B_plan_x - A.x);
		for(int j = -1; j < 2; j++){
			//faire varier la position de B selon y
			double B_plan_y = B.y + j * 2*getMax();
			double distanceY(B_plan_y - A.y);
			double norm( sqrt( distanceX * distanceX + distanceY  * distanceY));
			if(norm < petit_norm){
				petit_norm = norm;
				petit_x = distanceX;
				petit_y = distanceY;
			}
		}
	}
	Vect v({petit_norm, petit_x, petit_y});
	return v;
}

bool egalite(Point &p1, Point &p2)
{
	Vect v(distanceAB(p1, p2));
	return equal_zero(v.norme);
}

bool point_cercle(Point &p, Cercle &c)
{
	Vect v (distanceAB(p, c.centre));
	if (v.norme < (c.rayon)-epsilon_zero) {return true;}
	else {return false;}
}

bool point_cercle(Point &p1,  Point &p2, double &r)
{
	Vect v(distanceAB(p1, p2));
	if (v.norme < (r-epsilon_zero)){return true;}
	else {return false;}
}

bool cercle_cercle(Cercle &c1, Cercle &c2)
{
	Vect v(distanceAB(c1.centre, c2.centre));
	if (v.norme < ((c1.rayon + c2.rayon)-epsilon_zero)){
		return true;
	}else{ 
		return false;
	}
}
	
bool cercle_cercle(Point &p1, double &r1, Point &p2, double &r2)
{
	Vect v(distanceAB(p1, p2));
	if (v.norme < (r1 +r2 -epsilon_zero)){
		return true;
	}else{return false;}
}

bool cercle_cercle(Point &p1, const double &r1, Point &p2, const double &r2)
{
	Vect v(distanceAB(p1, p2));
	if (v.norme < (r1 +r2 -epsilon_zero)){
		return true;
	}else{return false;}
}

