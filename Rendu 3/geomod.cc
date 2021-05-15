#include <iostream>
#include <cmath>
#include "geomod.h"
#include "graphic.h"
#include "constantes.h"
#include <iostream>

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

void get_base_infos(Point centre, double rayon, int i){
	i = i%5;
    coord_norm(centre);
    Cercle base_est({rayon,centre}), base_ouest({rayon,centre}), base_nord({rayon,centre}), base_sud({rayon,centre});
    if((centre.x + 10*rayon ) > max) {
		base_est.centre.x = (centre.x)- 2*max;
		graphic_draw_base(base_est.centre.x, base_est.centre.y, base_est.rayon, i);
	}
    if((centre.x - 10*rayon ) < -max) {
		base_ouest.centre.x = (centre.x) + 2*max;
		graphic_draw_base(base_ouest.centre.x, base_ouest.centre.y, base_ouest.rayon, i);
	}
    if((centre.y + 10*rayon ) > max) { 
		base_sud.centre.x = (centre.y)- 2*max;
		graphic_draw_base(base_sud.centre.x, base_sud.centre.y, base_sud.rayon, i);
	}
    if((centre.y - 10*rayon ) < -max) { 
		base_nord.centre.x = (centre.y) + 2*max;
		graphic_draw_base(base_nord.centre.x, base_nord.centre.y, base_nord.rayon, i);
	}
    graphic_draw_base(centre.x, centre.y, rayon, i);
}

void get_gisement_infos(Point centre, double rayon){
    coord_norm(centre);
    Cercle gisement_est({rayon,centre}), gisement_ouest({rayon,centre}), gisement_nord({rayon,centre}), gisement_sud({rayon,centre});
    if((centre.x + rayon ) > max) {
		gisement_est.centre.x = (centre.x)- 2*max;
		graphic_draw_gisement(gisement_est.centre.x, gisement_est.centre.y, gisement_est.rayon, 0, 0, 0);
	}
    if((centre.x - rayon ) < -max) { 
		gisement_ouest.centre.x = (centre.x) + 2*max;
		graphic_draw_gisement(gisement_ouest.centre.x, gisement_ouest.centre.y, gisement_ouest.rayon, 0, 0, 0);
	}
    if((centre.y + rayon ) > max) { 
		gisement_sud.centre.x = (centre.y)- 2*max;
		graphic_draw_gisement(gisement_sud.centre.x, gisement_sud.centre.y, gisement_sud.rayon, 0, 0, 0);
	}
    if((centre.y - rayon ) < -max) { 
		gisement_nord.centre.x = (centre.y) + 2*max;
		graphic_draw_gisement(gisement_nord.centre.x, gisement_nord.centre.y, gisement_nord.rayon, 0, 0, 0);
	}
	graphic_draw_gisement(centre.x, centre.y, rayon,0, 0, 0);
}

void get_robot_infos(Point centre, int i){
	i = i%5;
    coord_norm(centre);
    graphic_draw_robot(centre.x, centre.y, i);
}
void get_robot_positionsAB(Point robot_A, Point B)
{
    double petit_norm(2*getMax());
    Point robot_B;
    for(int k = -1; k < 2; k++){
        //faire varier la position de B selon x
        double B_plan_x = B.x + k * 2* getMax();
        double distanceX(B_plan_x - robot_A.x);
        
        for(int j = -1; j < 2; j++){
            //faire varier la position de B selon y
            double B_plan_y = B.y + j * 2*getMax();
            double distanceY(B_plan_y - robot_A.y);
            double norm( sqrt( distanceX * distanceX + distanceY  * distanceY));
            
            if(norm < petit_norm){
                petit_norm = norm;
                robot_B.x = B_plan_x;
                robot_B.y = B_plan_y;
            }
        }
    }
    graphic_draw_line(robot_A.x, robot_A.y, robot_B.x, robot_B.y);
}

void get_robot_com_infos(Point centre){
//    i = i%5;
    coord_norm(centre);
    Point robot_com_est(centre), robot_com_ouest(centre), robot_com_nord(centre), robot_com_sud(centre);
    if((centre.x + rayon_comm ) > max) {
        robot_com_est.x = (centre.x)- 2*max;
        graphic_draw_robot_comm(robot_com_est.x, centre.y);
    }
    
    if((centre.x - rayon_comm ) < -max) {
        robot_com_ouest.x = (centre.x) + 2*max;
        graphic_draw_robot_comm(robot_com_ouest.x, centre.y);
    }
    
    if((centre.y + rayon_comm ) > max) {
        robot_com_sud.y = (centre.y)- 2*max;
        graphic_draw_robot_comm(centre.x, robot_com_sud.y);
    }
    
    if((centre.y - rayon_comm ) < -max) {
        robot_com_nord.y = (centre.y) + 2*max;
        graphic_draw_robot_comm(centre.x, robot_com_nord.y);
    }
    
    graphic_draw_robot_comm(centre.x, centre.y);
}
