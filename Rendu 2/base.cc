#include "base.h"
#include "robot.h"
#include "gisement.h"
#include "message.h"
#include "geomod.h"
#include "constantes.h"
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

static vector<Base> Eb; //Ensemble Eb


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
	Base b(x, y, ressources, nbP, nbF, nbT, nbC);  // Creation de la base
	b.intersection();  //tests d'intersection
	intersection_base_gisement(b.get_centre(), b.get_rayon());
	Eb.push_back(b);   //ajout dans l'ensemble Eb
	string line;
	b.decodage_robotP(nbP, config);
	b.decodage_robotF(nbF, config);
	b.decodage_robotT(nbT, config);
	b.decodage_robotC(nbC, config);
	b.test_uid();
	b.test_robocom();
}



//Methodes 
void Base::decodage_robotP(int nbP, ifstream &config)
{
	string line;
	int i(0);
	while (i<nbP){
		getline(config >> ws, line);
		if (line[0] == '#') {continue;}
		ErP.push_back(new RobotP(creer_robotP(line)));
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
		ErF.push_back(new RobotF(creer_robotF(line)));
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
		ErT.push_back(new RobotT(creer_robotT(line)));
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
		ErC.push_back(new RobotC(creer_robotC(line)));
		Er.push_back(ErC.back());
		
		++i;
	}
}
		


void Base::intersection(){
	//parcours de l'ensemble
	for(size_t i(0); i<Eb.size(); ++i){
		Point centre2(Eb[i].get_centre());
		double rayon2(Eb[i].get_rayon());
		//test d'intersection
		if(cercle_cercle(centre, rayon, centre2, rayon2)){
			cout << message::base_superposition(centre.x, centre.y, 
			centre2.x, centre2.y) << endl;
			exit(0); //quitte le programme si il y a une intersection
		}
	}
}

void Base::test_uid()
{
	for (size_t i(0); i<Er.size(); ++i){
		for(size_t j(i+1) ; j<Er.size(); ++j){
			if(Er[i]->get_uid() == Er[j]->get_uid()){
				cout << message::identical_robot_uid(Er[i]->get_uid()) << endl;
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
		cout << message::missing_robot_communication(centre.x, centre.y) << endl;
		exit(0);
	}
}

	
//Getters
Point Base::get_centre() {return centre;}

double Base::get_ressources() {return ressources;}

double Base::get_rayon() {return rayon;}

vector<Robot*> Base::get_Er() {return Er;}
vector<RobotP*> Base::get_ErP() {return ErP;}
vector<RobotF*> Base::get_ErF() {return ErF;}
vector<RobotT*> Base::get_ErT() {return ErT;}
vector<RobotC*> Base::get_ErC() {return ErC;}



//Constructeur
Base::Base(double x, double y, double ressources, int nbP, int nbF,
           int nbT, int nbC)
           : centre({x, y}), ressources(ressources), rayon(rayon_base), nbP(nbP), 
           nbF(nbF), nbT(nbT), nbC(nbC) {}
           
