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
	b.intersection();  //test d'intersection
	b.intersection_base_gisement(b.centre, b.rayon);
	Eb.push_back(b);   //ajout dans l'ensemble Eb
	string line;
	b.decodage_robotP(nbP, config);
	b.decodage_robotF(nbF, config);
	b.decodage_robotT(nbC, config);
	b.decodage_robotC(nbT, config);
}



//Methodes 
void Base::decodage_robotP(int nbP, ifstream &config)
{
	string line;
	int i(0);
	while (i<nbP){
		getline(config >> ws, line);
		if (line[0] == '#') {continue;}
		lecture_robotP(line);
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
		lecture_robotF(line);
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
		lecture_robotT(line);
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
		lecture_robotC(line);
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


//Getters
Point Base::get_centre() {return centre;}

double Base::get_ressources() {return ressources;}

double Base::get_rayon() {return rayon;}

int Base::get_nbC() {return nbC;}

int Base::get_nbF() {return nbF;}

int Base::get_nbP() {return nbP;}

int Base::get_nbT() {return nbT;}

vector<Robot> Base::get_Er() {return Er;}



//Constructeur
Base::Base(double x, double y, double ressources, int nbP, int nbF,
           int nbT, int nbC)
           : centre({x, y}), ressources(ressources), rayon(rayon_base), nbP(nbP), 
           nbF(nbF), nbT(nbT), nbC(nbC) {}
           
