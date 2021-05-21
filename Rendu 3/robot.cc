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
	: Robot(uid, dp, x, y, xb, yb, atteint) {used = false; ressources_recup = 0; transp_envoye = false; gisement_vide = false;}

RobotT::RobotT(int uid, double dp, double x, double y, double xb, 
               double yb, bool atteint, bool retour)
	: Robot(uid, dp, x, y, xb, yb, atteint), retour(retour) {used = false;}
	

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
//donner
void RobotP::set_fd(bool fd){
    found = fd;
}

void RobotP::set_position_gisement(double x, double y){
    position_gisement.x = x;
    position_gisement.y = y;
}


Point& RobotP::get_position_gisement(){
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

void RobotP::set_capaciteg(double c) {capaciteg = c;}

void RobotP::set_rayong(double r) {rayong = r;}

bool RobotT::get_used() {return used;}

void RobotT::set_used(bool u) {used = u;}

bool RobotF::get_used() {return used;}

void RobotF::set_used(bool u) {used = u;}

void RobotF::set_ressources_recup(double r) {ressources_recup = r;}

double RobotF::get_ressources_recup() {return ressources_recup;}

bool RobotF::get_transp_envoye() {return transp_envoye;}

void RobotF::set_transp_envoye(bool t) {transp_envoye = t;}

RobotF* RobotT::get_robotF() {return robotF;}

void RobotT::set_robotF(RobotF* r) {robotF = r;}

void RobotT::set_rt(bool r) {retour = r;}

double RobotT::get_ressources_transp() {return ressources_transp;}

void RobotT::set_ressources_transp(double r) {ressources_transp = r;}

bool RobotF::get_gisement_vide() {return gisement_vide;}

void RobotF::set_gisement_vide(bool g) {gisement_vide = g;}
	
	
