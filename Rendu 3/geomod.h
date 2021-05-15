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

struct Cercle
{
	double rayon;
	Point centre;
};

bool equal_zero(double epsilon_zero, double val);

void setMax(double init_max);

double getMax();

double getEpsilon();

void coord_norm(double &val);

void coord_norm(Point &p);

Vect distanceAB(Point &A, Point &B);

bool egalite(Point &p1, Point &p2);

bool point_cercle(Point &p, Cercle &c);

bool point_cercle(Point &p1,  Point &p2, double &r);

bool cercle_cercle(Cercle &c1, Cercle &c2);

bool cercle_cercle(Point &p1, double &r1, Point &p2, double &r2);

bool cercle_cercle(Point &p1, const double &r1, Point &p2, const double &r2);

void get_base_infos(Point centre, double rayon, int i);

void get_gisement_infos(Point centre, double rayon);

void get_robotP_infos(Point centre, int i);

void get_robotF_infos(Point centre, int i);

void get_robotT_infos(Point centre, int i);

void get_robotC_infos(Point centre, int i);

void get_robot_positionsAB(Point robot_A, Point B);

void get_robot_com_infos(Point centre);


#endif




