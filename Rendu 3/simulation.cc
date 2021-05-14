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

void Simulation::lecture(string nom_config)
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
			if (i==total) {cout << message::success(); 
						   set_file_opened(true);}
			break;
	}
}	


void Simulation::update_voisin()
{
	int Ebsize(get_Eb().size());
	
	for (int b(0); b<Ebsize; ++b){
		int Ersize(get_Eb()[b]->get_Er().size());
		for (int r(0); r<Ersize; ++r){
			get_Eb()[b]->get_Er()[r]->get_voisin().clear();
		}
	}
	
	for (int i(0); i<Ebsize; ++i){
		for(int j(0); j<Ebsize; ++j){
			int s1(get_Eb()[i]->get_Er().size());
			int s2(get_Eb()[j]->get_Er().size());
			for (int k(0); k<s1; ++k){
				for (int m(0); m<s2; ++m){
					Point p1(get_Eb()[i]->get_Er()[k]->get_position());
					Point p2(get_Eb()[j]->get_Er()[m]->get_position());
					if (cercle_cercle(p1, rayon_comm, p2, rayon_comm)){
						get_Eb()[i]->get_Er()[k]->get_voisin().push_back(&(*(get_Eb()[j]->get_Er()[m])));
					}
				}
			}
		}
	}
}


void Simulation::save(string name)
{
	ofstream sauvegarde;
	sauvegarde.open(name);
	if (sauvegarde.fail()) {
		cout <<"Impossible de sauvegarder le fichier" << endl;
	}
	sauvegarde << "# " << name << endl;
	sauvegarde << "#" << endl;
	sauvegarde << "# nb Gisements" << endl;
	sauvegarde << nbG << endl;
	sauvegarde << "# Gisements :" << endl;
	save_gisement(sauvegarde);
	sauvegarde << "# nb Bases" << endl;
	sauvegarde << nbB << endl;
	sauvegarde << "# Bases :" << endl;
	save_base(sauvegarde);
}

vector<Robot*> Simulation::parcours_DFS(Robot* depart)
{
	vector<Robot*> result;
	for(size_t i(0); i<get_Eb().size(); ++i){
		for(size_t j(0); j<get_Eb()[i]->get_Er().size(); ++j){
			get_Eb()[i]->get_Er()[j]->set_visited(false);
			
		}
	}
	
	rec_DFS(result, depart);
	
	return result;
}

void Simulation::rec_DFS(vector<Robot*>& result, Robot* next)
{
	next->set_visited(true);
	result.push_back(next);
	
	for(size_t i(0); i<next->get_voisin().size(); ++i){
		if(!(next->get_voisin()[i]->get_visited())){
			rec_DFS(result, next->get_voisin()[i]);
		}
	}
}	


void Simulation::connexion()
{
	for (size_t i(0); i<get_Eb().size(); ++i){
		for (size_t j(0); j<get_Eb()[i]->get_Er().size(); ++j){
			get_Eb()[i]->get_Er()[j]->set_connect(false);
			Robot* depart = &(*(get_Eb()[i]->get_Er()[j]));
			vector<Robot*> result (parcours_DFS(depart));
			for (size_t k(0) ; k<result.size(); ++k){
				if (egalite(result[k]->get_position(), get_Eb()[i]->get_centre())){
					get_Eb()[i]->get_Er()[j]->set_connect(true);
				}
			}
		}
	}
}

void Simulation::verif_connexion()
{
	for(size_t i(0); i<get_Eb().size(); ++i){
		for (size_t j(0); j<get_Eb()[i]->get_Er().size(); ++j){
			cout << get_Eb()[i]->get_Er()[j]->get_connect() << endl;
		}
	}
}
			
void Simulation::maintenance()
{
	for(size_t i(0); i<get_Eb().size(); ++i){
		for(size_t j(0); j<get_Eb()[i]->get_Er().size(); ++j){
			if  (egalite(get_Eb()[i]->get_Er()[j]->get_position(), get_Eb()[i]->get_centre())){
				double dp(get_Eb()[i]->get_Er()[j]->get_dp());
				double ressources (get_Eb()[i]->get_ressources());
				get_Eb()[i]->set_ressources(ressources - (cost_repair*dp));
				get_Eb()[i]->get_Er()[j]->set_dp(0);
			}
		}
	}
}	

void Simulation::draw_base()
{
	for(size_t i(0); i<get_Eb().size(); ++i){
		cout << "draw base" << endl;
		Point centre(get_Eb()[i]->get_centre());
		double rayon(get_Eb()[i]->get_rayon());
		get_base_infos(centre, rayon, i);
	}
}

void Simulation::draw_gisement()
{
	for (size_t i(0); i<get_Eg().size(); ++i){
		cout << "draw gisement" << endl;
		Point centre(get_Eg()[i]->get_centre());
		double rayon(get_Eg()[i]->get_rayon());
		get_gisement_infos(centre, rayon);
	}
}

void Simulation::draw_robot()
{
	for (size_t i(0); i<get_Eb().size(); ++i){
		for (size_t j(0); j<get_Eb()[i]->get_Er().size(); ++j){
			cout << "draw robot" << endl;
			Point position(get_Eb()[i]->get_Er()[j]->get_position());
			get_robot_infos(position, i);
		}
	}
}
void Simulation::draw_line(){
    for (size_t i(0); i<get_Eb().size(); ++i){
        for (size_t j(0); j<get_Eb()[i]->get_Er().size(); ++j){
            for (size_t k(0); k<get_Eb()[i]->get_Er()[j]->get_voisin().size(); ++k){
                Point position_A(get_Eb()[i]->get_Er()[j]->get_position());
                Point position_B(get_Eb()[i]->get_Er()[j]->get_voisin()[k]->get_position());
                get_robot_positionsAB(position_A,position_B);
            }
        }
    }
}

void Simulation::update_robot()
{
	for (size_t i(0); i<get_Eb().size(); ++i){
		for(size_t j(0); j<get_Eb()[i]->get_Er().size(); ++j){
			get_Eb()[i]->get_Er()[j]->set_position(get_Eb()[i]->get_Er()[j]->get_position().x + deltaD, get_Eb()[i]->get_Er()[j]->get_position().y);
		}
	}
}

//Getter
bool Simulation::get_file_opened() {return file_opened;}

//Setter
void Simulation::set_file_opened(bool etat) {file_opened = etat;}

//Constructeur			
Simulation::Simulation() : file_opened(false)
{
	setMax(dim_max);
}
