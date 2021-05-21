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
#include <memory>

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
			if (retourst == "true") {retour = true;}
			else {retour = false;}
			if (atteintst =="true") {atteint = true;}
			else {atteint = false;}
			coord_norm(x);
			coord_norm(y);
			RobotP p(uid, dp, x, y, xb, yb, atteint, retour, found, 0, 0, 0, 0);
			return p;
		}
		if (foundst =="true"){
			found = true;
			if(!(data >> xg >> yg >> rayong >> capaciteg)){
				exit(0);
			}else{
				if (retourst == "true") {retour = true;}
				else {retour = false;}
				if (atteintst =="true") {atteint = true;}
				else {atteint = false;}
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
		coord_norm(x);
		coord_norm(y);
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
		coord_norm(x);
		coord_norm(y);
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
		coord_norm(x);
		coord_norm(y);
		RobotC c(uid, dp, x, y, xb, yb, atteint);
		return c;
	}
}

Robot::Robot(int uid, double dp, double x, double y, double xb, 
             double yb, bool atteint)
	: uid(uid), dp(dp), position({x, y}), position_but({xb, yb}), atteint(atteint) {}
	
RobotP::RobotP(int uid, double dp, double x, double y, double xb, 
               double yb, bool atteint, bool retour, bool found,
               double xg, double yg, double rayong, double capaciteg)
	: Robot(uid, dp, x, y, xb, yb, atteint), position_gisement({xg, yg}), 
	  rayong(rayong), capaciteg(capaciteg), retour(retour), found(found) {cycle = 0;}

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
    
double Robot::get_dp(){
	return dp;
}

Point& Robot::get_position(){
	return position;
}
    
Point& Robot::get_position_but(){
	return position_but;
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

Point RobotP::get_position_gisement(){
    return position_gisement;
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
	
bool Robot::get_visited() {return visited;}

void Robot::set_visited(bool v) {visited = v;}	

void Robot::set_connect(bool c) {connect = c;}

bool Robot::get_connect() {return connect;}

void Robot::set_dp(double d) {dp = d;}

vector<Robot*>& Robot::get_voisin()
{
	return voisin;
}
	
void Robot::set_position(double x, double y)
{
	position.x = x;
	position.y = y;
}

void Robot::set_position_but(double x, double y)
{
	position_but.x = x;
	position_but.y = y;
}
	
void Robot::set_position_but(Point but)
{
	position_but = but;
}

void RobotP::set_rt(bool r) {retour = r;}

int RobotP::get_cycle() {return cycle;}

void RobotP::set_cycle(int c) {cycle = c;}
	
void Robot::set_at(bool a) {atteint = a;}
	
	
	
