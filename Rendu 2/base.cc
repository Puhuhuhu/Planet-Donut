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
	Eb.push_back(b);   //ajout dans l'ensemble Eb
	string line;
	int i(0);
	//recuperation des lignes correspondant aux robots
	while (i < nbP+nbF+nbT+nbC){
		getline(config >> ws, line);
		if (line[0] == '#') {continue;}
		b.decodage_robot(line);
		++i;
	}
}



//Methodes 
void Base::decodage_robot(string line)
{
	//Automate de lecture
	enum etat_lecture{NB0, P, NB1, F, NB2, T, NB3, C};
	static int etat(NB0);
	static int i;
	switch(etat)
	{
		case NB0 :
			i = 0;
			if (nbP == 0) {etat = NB1, decodage_robot(line);}
			else {etat = P, decodage_robot(line);}
			break;
		
		case P :
			++i;
			lecture_robotP(line);
			if(i==nbP) {etat = NB1;}
			break;
		
		case NB1 :
			i = 0;
			if(nbF == 0) {etat = NB2, decodage_robot(line);}
			else {etat = F, decodage_robot(line);}
			break;
			
		case F :
			++i;
			lecture_robotF(line);
			if(i==nbF) {etat = NB2;}
			break;
		
		case NB2 :
			i = 0;
			if(nbT==0) {etat = NB3, decodage_robot(line);}
			else {etat = T, decodage_robot(line);}
			break;
			
		case T :
			++i;
			lecture_robotT(line);
			if(i==nbT) {etat = NB3;}
			break;
			
		case NB3 :
			i = 0;
			if(nbC==0) {etat = NB0;}
			else{etat = C, decodage_robot(line);}
			break;
		
		case C :
			++i;
			lecture_robotC(line);
			if(i==nbC) {etat = NB0;}
			break;
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
			Eb[i].get_centre().x, Eb[i].get_centre().y) << endl;
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
           
