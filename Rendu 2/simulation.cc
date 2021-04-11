#include "simulation.h"
#include "base.h"
#include "gisement.h"
#include "geomod.h"
#include "constantes.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;


//Methodes
void Simulation::lecture(char* nom_config)
{
	string line;
	ifstream config(nom_config);
	if (!config.fail()){
		while (getline(config >> ws, line)){
			if (line[0]=='#'){continue;}
			decodage(line, config);
		}
	}else{exit(0);}
}



void Simulation::decodage(string line, ifstream& config)
{
	//Automate de lecture
	istringstream data(line);
	enum etat_lecture{NB0=1, G=2, NB1=3, B=4, FIN=5};
	static int etat(NB0);
	static int total;
	static int i;
	switch(etat)
	{
		case NB0 :
			if(!(data >> total)) exit(0);
			else {i=0;}
			if (total == 0) {etat = NB1; nbG = 0;}
			else {etat = G; nbG = total;}
			break;
			
		case G :
			++i;
			if (i == total) {etat = NB1;}
			lecture_gisement(line);
			break;
		
		case NB1 :
			if(!(data >> total)) exit(0);
			else {i=0;}
			if (total == 0) {etat = FIN; nbB=0;}
			else {etat = B; nbB = total;}
			break;
			
		case B :
			++i;
			if (i == total) {etat = FIN;}
			lecture_base(line, config);
			break;
			
		case FIN :
			break;
	}
}	


//Constructeur			
Simulation::Simulation() {setMax(dim_max);}
