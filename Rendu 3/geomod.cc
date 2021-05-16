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
    graphic_draw_base(centre.x, centre.y, rayon, i);
    Point base_est(centre), base_ouest(centre), base_nord(centre), base_sud(centre), base_ne(centre), base_no(centre), base_se(centre), base_so(centre);
    if((centre.x + 10*rayon ) > max) {
		base_ouest.x = centre.x - 2*max;
		graphic_draw_base(base_ouest.x, centre.y, 10*rayon, i);
	}
    if((centre.x - 10*rayon ) < -max) {
		base_est.x = centre.x + 2*max;
		graphic_draw_base(base_est.x, centre.y, 10*rayon, i);
	}
    if((centre.y + 10*rayon ) > max) { 
		base_sud.y = centre.y - 2*max;
		graphic_draw_base(centre.x, base_sud.y, 10*rayon, i);
	}
    if((centre.y - 10*rayon ) < -max) { 
		base_nord.y = centre.y + 2*max;
		graphic_draw_base(centre.x, base_nord.y, rayon, i);
	}
	if (((centre.x + 10*rayon ) > max) and ((centre.y + 10*rayon) > max)){
		base_so.x = centre.x - 2*max;
		base_so.y = centre.y - 2*max;
		graphic_draw_base(base_so.x, base_so.y, rayon, i);
	}
	if (((centre.x - 10*rayon ) > max) and ((centre.y + 10*rayon) > max)){
		base_se.x = centre.x + 2*max;
		base_se.y = centre.y - 2*max;
		graphic_draw_base(base_se.x, base_se.y, rayon, i);
	}
	if (((centre.x - 10*rayon ) > max) and ((centre.y - 10*rayon) > max)){
		base_ne.x = centre.x + 2*max;
		base_ne.y = centre.y + 2*max;
		graphic_draw_base(base_ne.x, base_ne.y, rayon, i);
	}
	if (((centre.x + 10*rayon ) > max) and ((centre.y - 10*rayon) > max)){
		base_no.x = centre.x - 2*max;
		base_no.y = centre.y + 2*max;
		graphic_draw_base(base_no.x, base_no.y, rayon, i);
	}
}

void get_gisement_infos(Point centre, double rayon){
    coord_norm(centre);
    graphic_draw_gisement(centre.x, centre.y, rayon,0, 0, 0);
    Point gisement_est(centre), gisement_ouest(centre), gisement_nord(centre), gisement_sud(centre), gisement_ne(centre), gisement_no(centre), gisement_se(centre), gisement_so(centre);
    if((centre.x + rayon ) > max) {
		gisement_ouest.x = centre.x - 2*max;
		graphic_draw_gisement(gisement_ouest.x, centre.y, rayon, 0, 0, 0);		
	}
    if((centre.x - rayon ) < -max) { 
		gisement_est.x = centre.x + 2*max;
		graphic_draw_gisement(gisement_ouest.x, centre.y, rayon, 0, 0, 0);
	}
    if((centre.y + rayon ) > max) { 
		gisement_sud.y = centre.y - 2*max;
		graphic_draw_gisement(centre.x, gisement_sud.y, rayon, 0, 0, 0);
	}
    if((centre.y - rayon ) < -max) { 
		gisement_nord.y = centre.y + 2*max;
		graphic_draw_gisement(centre.x, gisement_nord.y, rayon, 0, 0, 0);
	}
	if (((centre.x + rayon ) > max) and ((centre.y + rayon) > max)){
		gisement_so.x = centre.x - 2*max;
		gisement_so.y = centre.y - 2*max;
		graphic_draw_gisement(gisement_so.x, gisement_so.y, rayon, 0, 0, 0);
	}
	if (((centre.x - rayon ) < -max) and ((centre.y + rayon) > max)){
		gisement_se.x = centre.x + 2*max;
		gisement_se.y = centre.y - 2*max;
		graphic_draw_gisement(gisement_se.x, gisement_se.y, rayon, 0, 0, 0);
	}
	if (((centre.x - rayon ) < -max) and ((centre.y - rayon) < -max)){
		gisement_ne.x = centre.x + 2*max;
		gisement_ne.y = centre.y + 2*max;
		graphic_draw_gisement(gisement_ne.x, gisement_ne.y, rayon, 0, 0, 0);
	}
	if (((centre.x + rayon ) > max) and ((centre.y - rayon) < -max)){
		gisement_no.x = centre.x - 2*max;
		gisement_no.y = centre.y + 2*max;
		graphic_draw_gisement(gisement_no.x, gisement_no.y, rayon, 0, 0, 0);
	}
}

void get_robotP_infos(Point centre, int i){
	i = i%5;
    coord_norm(centre);
    graphic_draw_robotP(centre.x, centre.y, i);
}

void get_robotF_infos(Point centre, int i){
	i = i%5;
    coord_norm(centre);
    graphic_draw_robotF(centre.x, centre.y, i);
}

void get_robotT_infos(Point centre, int i){
	i = i%5;
    coord_norm(centre);
    graphic_draw_robotT(centre.x, centre.y, i);
}

void get_robotC_infos(Point centre, int i){
	i = i%5;
    coord_norm(centre);
    graphic_draw_robotC(centre.x, centre.y, i);
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
