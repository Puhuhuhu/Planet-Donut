#include "base.h"
#include "robot.h"
#include "gisement.h"
#include "message.h"
#include "geomod.h"
#include "constantes.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
using namespace std;

static vector<unique_ptr<Base>> Eb; //Ensemble Eb


//Fonctions
void lecture_base(string line, ifstream &config)
{
	istringstream data(line);
	double x, y, ressources;
	int nbP, nbF, nbT, nbC;
	//Verification de la syntaxe
	if(!(data >> x >> y >> ressources >> nbP >> nbF >> nbT >> nbC)) {exit(0);}
	else {creer_base(x, y, ressources, nbP, nbF, nbT, nbC, config);}
	
}



void creer_base(double x, double y, double ressources, int nbP, int nbF, int nbT, 
                int nbC, ifstream &config)
{
	coord_norm(x);
	coord_norm(y);
	Eb.push_back(unique_ptr<Base>(new Base(x, y, ressources, nbP, nbF, nbT, nbC)));  // Creation de la base
	Eb.back()->intersection();
	Eb.back()->decodage_robotP(nbP, config);
	Eb.back()->decodage_robotF(nbF, config);
	Eb.back()->decodage_robotT(nbT, config);
	Eb.back()->decodage_robotC(nbC, config);
	intersection_base_gisement(Eb.back()->get_centre(), Eb.back()->get_rayon());
	Eb.back()->test_uid();
	Eb.back()->test_robocom();
}


void save_base(ofstream& sauvegarde)
{
	for (size_t i(0); i<Eb.size() ; ++i){
		sauvegarde << "    " << Eb[i]->get_centre().x << " " << Eb[i]->get_centre().y 
		           << " " << Eb[i]->get_ressources() << " " << Eb[i]->get_nbP() << " " 
		           << Eb[i]->get_nbF() << " " << Eb[i]->get_nbT() << " " 
		           << Eb[i]->get_nbC() << endl;
		save_robot(sauvegarde, i);
	}
}

void save_robot(ofstream& sauvegarde, int j)
{
	sauvegarde << "        # Prospector" << endl;
	for (size_t i(0); i<Eb[j]->get_ErP().size(); ++i){
		save_robotP(sauvegarde, j, i);
	}
	sauvegarde << "        # Drilling" << endl;
	for (size_t i(0); i<Eb[j]->get_ErF().size(); ++i){
		save_robotF(sauvegarde, j, i);
	}
	sauvegarde << "        # Transport" << endl;
	for (size_t i(0); i<Eb[j]->get_ErT().size(); ++i){
		save_robotT(sauvegarde, j, i);
	}
	sauvegarde << "        # Communication" << endl;
	for (size_t i(0); i<Eb[j]->get_ErC().size(); ++i){
		save_robotC(sauvegarde, j, i);
	}
}

void save_robotP(ofstream& sauvegarde, int j, int i)
{
	string atteintst, retourst, foundst;
	if (Eb[j]->get_ErP()[i]->get_at() == 0) {atteintst = "false";}
	else {atteintst = "true";}
	if (Eb[j]->get_ErP()[i]->get_rt() == 0) {retourst = "false";}
	else {retourst = "true";}
	if (Eb[j]->get_ErP()[i]->get_fd() == 0) {foundst = "false";}
	else {foundst = "true";}
	
	sauvegarde << "        " << Eb[j]->get_ErP()[i]->get_uid() << " " 
	           << Eb[j]->get_ErP()[i]->get_dp() << " "
	           << Eb[j]->get_ErP()[i]->get_position().x << " " 
	           << Eb[j]->get_ErP()[i]->get_position().y << " " 
	           << Eb[j]->get_ErP()[i]->get_position_but().x << " "
		       << Eb[j]->get_ErP()[i]->get_position_but().y << " " 
		       << atteintst << " " 
		       << retourst << " " 
		       << foundst;
	if (Eb[j]->get_ErP()[i]->get_fd()){
		sauvegarde << " " << Eb[j]->get_ErP()[i]->get_position_gisement().x << " " 
		           << Eb[j]->get_ErP()[i]->get_position_gisement().y << " " 
		           << Eb[j]->get_ErP()[i]->get_rg()
		           << " " << Eb[j]->get_ErP()[i]->get_cg() << endl;
	}else{sauvegarde << endl;}
}


void save_robotF(ofstream& sauvegarde, int j, int i)
{
	string atteintst;
	if (Eb[j]->get_ErF()[i]->get_at() == 0) {atteintst = "false";}
	else {atteintst = "true";}
	
	sauvegarde << "        " << Eb[j]->get_ErF()[i]->get_uid() << " " 
	           << Eb[j]->get_ErF()[i]->get_dp() << " "
		       << Eb[j]->get_ErF()[i]->get_position().x << " " 
		       << Eb[j]->get_ErF()[i]->get_position().y  << " " 
		       << Eb[j]->get_ErF()[i]->get_position_but().x << " " 
		       << Eb[j]->get_ErF()[i]->get_position_but().y << " " 
		       << atteintst << endl;	
}

void save_robotT(ofstream& sauvegarde, int j, int i)
{
	string atteintst, retourst;
	if (Eb[j]->get_ErT()[i]->get_at() == 0) {atteintst = "false";}
	else {atteintst = "true";}
	if (Eb[j]->get_ErT()[i]->get_rt() == 0) {retourst = "false";}
	else {retourst= "true";}
	
	sauvegarde << "        " << Eb[j]->get_ErT()[i]->get_uid() << " " 
			   << Eb[j]->get_ErT()[i]->get_dp() << " "
		       <<Eb[j]->get_ErT()[i]->get_position().x << " " 
		       << Eb[j]->get_ErT()[i]->get_position().y << " " 
		       << Eb[j]->get_ErT()[i]->get_position_but().x << " "
		       << Eb[j]->get_ErT()[i]->get_position_but().y << " " 
		       << atteintst << " " 
		       << retourst << endl;	
}

void save_robotC(ofstream& sauvegarde, int j, int i)
{
	string atteintst;
	if (Eb[j]->get_ErC()[i]->get_at() == 0) {atteintst = "false";}
	else {atteintst = "true";}
	
	sauvegarde << "        " << Eb[j]->get_ErC()[i]->get_uid() << " " 
			   << Eb[j]->get_ErC()[i]->get_dp() << " "
		       << Eb[j]->get_ErC()[i]->get_position().x << " " 
		       << Eb[j]->get_ErC()[i]->get_position().y << " " 
		       << Eb[j]->get_ErC()[i]->get_position_but().x << " " 
		       << Eb[j]->get_ErC()[i]->get_position_but().y << " " 
		       << atteintst << endl;
}
//Methodes 
void Base::decodage_robotP(int nbP, ifstream &config)
{
	string line;
	int i(0);
	while (i<nbP){
		getline(config >> ws, line);
		if (line[0] == '#') {continue;}
		ErP.push_back(shared_ptr<RobotP> (new RobotP(creer_robotP(line))));
		Er.push_back(ErP.back());
		++i;
	}
}

void Base::decodage_robotF(int nbF, ifstream &config)
{
	string line;
	int i(0);
	while (i<nbF){
		getline(config >> ws, line);
		if (line[0] == '#') {continue;}
		ErF.push_back(shared_ptr<RobotF> (new RobotF(creer_robotF(line))));
		Er.push_back(ErF.back());
		++i;
	}
}

void Base::decodage_robotT(int nbT, ifstream &config)
{
	string line;
	int i(0);
	while (i<nbT){
		getline(config >> ws, line);
		if (line[0] == '#') {continue;}
		ErT.push_back(shared_ptr<RobotT> (new RobotT(creer_robotT(line))));
		Er.push_back(ErT.back());
		++i;
	}
}

void Base::decodage_robotC(int nbC, ifstream &config)
{
	string line;
	int i(0);
	while (i<nbC){
		getline(config >> ws, line);
		if (line[0] == '#') {continue;}
		ErC.push_back(shared_ptr<RobotC> (new RobotC(creer_robotC(line))));
		Er.push_back(ErC.back());
		
		++i;
	}
}
		


void Base::intersection(){
	//parcours de l'ensemble
	for(size_t i(0); i<Eb.size()-1; ++i){
		Point centre2(Eb[i]->get_centre());
		double rayon2(Eb[i]->get_rayon());
		//test d'intersection
		if(cercle_cercle(centre, rayon, centre2, rayon2)){
			cout << message::base_superposition(centre.x, centre.y, 
			centre2.x, centre2.y);
			exit(0); //quitte le programme si il y a une intersection
		}
	}
}

void Base::test_uid()
{
	for (size_t i(0); i<Er.size(); ++i){
		for(size_t j(i+1) ; j<Er.size(); ++j){
			if(Er[i]->get_uid() == Er[j]->get_uid()){
				cout << message::identical_robot_uid(Er[i]->get_uid());
				exit(0);
			}
		}
	}
}
			

void Base::test_robocom(){
	bool robocom(false);
	for(size_t i(0); i<ErC.size(); ++i){
		Point centre2(ErC[i]->get_position());
		if (egalite(centre, centre2)){
			robocom = true;
		}
	}
	if(!robocom){
		cout << message::missing_robot_communication(centre.x, centre.y);
		exit(0);
	}
}
	
//Getters Setters
Point& Base::get_centre() {return centre;}

double Base::get_ressources() {return ressources;}

double Base::get_rayon() {return rayon;}

vector<shared_ptr<Robot>>& Base::get_Er() {return Er;}
vector<shared_ptr<RobotP>>& Base::get_ErP() {return ErP;}
vector<shared_ptr<RobotF>>& Base::get_ErF() {return ErF;}
vector<shared_ptr<RobotT>>& Base::get_ErT() {return ErT;}
vector<shared_ptr<RobotC>>& Base::get_ErC() {return ErC;}

vector<unique_ptr<Base>>& get_Eb() {return Eb;}

int Base::get_nbP() {return nbP;}
int Base::get_nbF() {return nbF;}
int Base::get_nbT() {return nbT;}
int Base::get_nbC() {return nbC;}

void Base::set_ressources(double r) {ressources = r;}

int Base::get_nb_com() {return nb_com;}

void Base::set_nb_com(int n) {nb_com = n;}

void Base::set_nbP(int n) {nbP = n;}
void Base::set_nbF(int n) {nbF = n;}
void Base::set_nbT(int n) {nbT = n;}
void Base::set_nbC(int n) {nbC = n;}

//Constructeur
Base::Base(double x, double y, double ressources, int nbP, int nbF,
           int nbT, int nbC)
           : centre({x, y}), ressources(ressources), rayon(rayon_base), nbP(nbP), 
           nbF(nbF), nbT(nbT), nbC(nbC) {nb_com = 1;}








