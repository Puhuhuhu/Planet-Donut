#include "robot.h"
#include "gisement.h"
#include "message.h"
#include "geomod.h"
#include "constantes.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

RobotP creer_robotP(string line)
{
	istringstream data (line);
	int uid;
	double x, y, xb, yb, dp, xg, yg, rayong, capaciteg;
	string atteintst, retourst, foundst;
	bool atteint, retour, found;
	if (!(data >> uid >> dp >> x >> y >> xb >> yb >> 
	      atteintst >> retourst >> foundst)){
		exit (0);
	}else{
		if (foundst == "false"){
			found = false;
			RobotP p(uid, dp, x, y, xb, yb, atteint, retour, found, 0, 0, 0, 0);
			return p;
		}
		if (foundst ==" true"){
			if(!(data >> xg >> yg >> rayong >> capaciteg)){
				exit(0);
			}else{
				found = true;
				if (retourst == "true") {retour = true;}
				else {retour = false;}
				if (foundst == "true") {found = true;}
				else {found = false;}
				RobotP p(uid, dp, x, y, xb, yb, atteint, retour, 
				         found, xg, yg, rayong, capaciteg);
				return p;
			}
		}
	}
}

RobotF creer_robotF(string line)
{
	istringstream data(line);
	int uid;
	double dp, x, y, xb, yb;
	string atteintst;
	bool atteint;
	if(!(data >> uid >> dp >> x >> y >> xb >> yb >> atteintst)) {exit(0);}
	else {
		if (atteintst=="true") {atteint = true;}
		else {atteint = false;}
		RobotF f(uid, dp, x, y, xb, yb, atteint);
		return f;
	}
}
		
RobotT creer_robotT(string line)
{
	istringstream data(line);
	int uid;
	double dp, x, y, xb, yb;
	string atteintst, retourst;
	bool atteint, retour;
	if(!(data >> uid >> dp >> x >> y >> xb >> yb >> atteintst >> retourst)) {exit(0);}
	else {
		if (atteintst=="true") {atteint = true;}
		else {atteint = false;}
		if (retourst == "true") {retour = true;}
		else {retour = false;}
		RobotT t(uid, dp, x, y, xb, yb, atteint, retour);
		return t;
	}
}

RobotC creer_robotC(string line)
{
	istringstream data(line);
	int uid;
	double dp, x, y, xb, yb;
	string atteintst;
	bool atteint;
	if(!(data >> uid >> dp >> x >> y >> xb >> yb >> atteintst)) {exit(0);}
	else{
		if (atteintst=="true") {atteint = true;}
		else {atteint = false;}
		RobotC c(uid, dp, x, y, xb, yb, atteint);
		return c;
	}
}


Robot::Robot(int uid, double dp, double x, double y, double xb, 
             double yb, bool atteint)
	: uid(uid), dp(dp), position({x, y}), position_base({xb, yb}), atteint(atteint) {}
	
RobotP::RobotP(int uid, double dp, double x, double y, double xb, 
               double yb, bool atteint, double xg, double yg, double rayong, 
               double capaciteg, bool retour, bool found)
	: Robot(uid, dp, x, y, xb, yb, atteint), position_gisement({xg, yg}), 
	  retour(retour), found(found) {}

RobotF::RobotF(int uid, double dp, double x, double y, double xb, 
               double yb, bool atteint)
	: Robot(uid, dp, x, y, xb, yb, atteint) {}

RobotT::RobotT(int uid, double dp, double x, double y, double xb, 
               double yb, bool atteint, bool retour)
	: Robot(uid, dp, x, y, xb, yb, atteint), retour(retour) {}
	

RobotC::RobotC(int uid, double dp, double x, double y, double xb, 
               double yb, bool atteint)
	: Robot(uid, dp, x, y, xb, yb, atteint) {}



int Robot::get_uid(){
    return uid;
    }

Point Robot::get_position(){
	return position;
    }
    
double Robot::get_xb(){
    return position_base.x;
    }
    
double Robot::get_yb(){
    return position_base.y;
    }
    
bool Robot::get_at(){
    return atteint;
    }
    
bool RobotP::get_rt(){
    return retour;
    }
    
bool RobotP::get_fd(){
    return found;
    }

double RobotP::get_xg(){
    return position_gisement.x;
}
double RobotP::get_yg(){
    return position_gisement.y;
}

double RobotP::get_rg(){
    return rayong;
}

double RobotP::get_cg(){
    return capaciteg;
}

bool RobotT::get_rt(){
    return retour;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
