#include "simulation.h"
#include "base.h"
#include "gisement.h"
#include "geomod.h"
#include "constantes.h"
#include "message.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

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
	enum etat_lecture{NB0, G, NB1, B};
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
			if (total == 0) {nbB=0;}
			else {etat = B; nbB = total;}
			break;
			
		case B :
			++i;
			lecture_base(line, config);
			if (i==total) {cout << message::success();}
			break;
	}
}	

void Simulation::update_voisin()
{
	for (int i(0); i<nbB; ++i){
		for (int j(0); j<nbB; ++j){
			int s1(get_Eb()[i].get_Er().size());
			int s2(get_Eb()[j].get_Er().size());
			for (int k(0); k<s1; ++k){
				get_Eb()[i].get_Er()[k]->get_voisin().clear();
			}
			for (int k(0); k<s1; ++k){
				for (int m(0); m<s2; ++m){
					if(cercle_cercle(get_Eb()[i].get_Er()[k]->get_position(), rayon_comm, get_Eb()[j].get_Er()[m]->get_position(), rayon_comm)){
						get_Eb()[i].get_Er()[k]->get_voisin().push_back(get_Eb()[j].get_Er()[m]);
					}
				}
			}
		}
	}
}

//Constructeur			
Simulation::Simulation() {setMax(dim_max);}
