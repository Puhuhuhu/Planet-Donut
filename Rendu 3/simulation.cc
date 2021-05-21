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
#include <cmath>

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
		Point centre(get_Eb()[i]->get_centre());
		double rayon(get_Eb()[i]->get_rayon());
		get_base_infos(centre, rayon, i);
	}
}

void Simulation::draw_gisement()
{
	for (size_t i(0); i<get_Eg().size(); ++i){
		Point centre(get_Eg()[i]->get_centre());
		double rayon(get_Eg()[i]->get_rayon());
		get_gisement_infos(centre, rayon);
	}
}

void Simulation::draw_robotP()
{
	for (size_t i(0); i<get_Eb().size(); ++i){
		for (size_t j(0); j<get_Eb()[i]->get_ErP().size(); ++j){
			Point position(get_Eb()[i]->get_ErP()[j]->get_position());
			get_robotP_infos(position, i);
		}
	}
}

void Simulation::draw_robotF()
{
	for (size_t i(0); i<get_Eb().size(); ++i){
		for (size_t j(0); j<get_Eb()[i]->get_ErF().size(); ++j){
			Point position(get_Eb()[i]->get_ErF()[j]->get_position());
			get_robotF_infos(position, i);
		}
	}
}

void Simulation::draw_robotT()
{
	for (size_t i(0); i<get_Eb().size(); ++i){
		for (size_t j(0); j<get_Eb()[i]->get_ErT().size(); ++j){
			Point position(get_Eb()[i]->get_ErT()[j]->get_position());
			get_robotT_infos(position, i);
		}
	}
}

void Simulation::draw_robotC()
{
	for (size_t i(0); i<get_Eb().size(); ++i){
		for (size_t j(0); j<get_Eb()[i]->get_ErC().size(); ++j){
			Point position(get_Eb()[i]->get_ErC()[j]->get_position());
			get_robotC_infos(position, i);
		}
	}
}

void Simulation::draw_rayon_comm()
{
    for (size_t i(0); i<get_Eb().size(); ++i){
        for (size_t j(0); j<get_Eb()[i]->get_Er().size(); ++j){
            Point position(get_Eb()[i]->get_Er()[j]->get_position());
            get_robot_com_infos(position);
        }
    }
}

/*
void Simulation::update_robot()
{
	for (size_t i(0); i<get_Eb().size(); ++i){
		for(size_t j(0); j<get_Eb()[i]->get_Er().size(); ++j){
			get_Eb()[i]->get_Er()[j]->set_position(get_Eb()[i]->get_Er()[j]->get_position().x + deltaD, get_Eb()[i]->get_Er()[j]->get_position().y);
		}
	}
}
*/

void Simulation::draw_liaison()
{
	for (size_t i(0); i<get_Eb().size(); ++i){
		for (size_t j(0); j<get_Eb()[i]->get_Er().size(); ++j){
			for (size_t k(0); k<get_Eb()[i]->get_Er()[j]->get_voisin().size(); ++k){
				Point position_A(get_Eb()[i]->get_Er()[j]->get_position());
				Point position_B(get_Eb()[i]->get_Er()[j]->get_voisin()[k]->get_position());
				get_robot_positionsAB(position_A, position_B);
			}
		}
	}
}


//recevoir les infos relatives aux bases
int Simulation::compteur_base(){
     return get_Eb().size();
}

int Simulation::compteur_robotP(int base_numero){
    return get_Eb()[base_numero]->get_nbP();
}

int Simulation::compteur_robotF(int base_numero){
    return get_Eb()[base_numero]->get_nbF();
}

int Simulation::compteur_robotC(int base_numero){
    return get_Eb()[base_numero]->get_nbC();
}

int Simulation::compteur_robotT(int base_numero){
    return get_Eb()[base_numero]->get_nbT();
}

double Simulation::compteur_resources(int base_numero){
    return get_Eb()[base_numero]->get_ressources();
}



void Simulation::update_remote()
{
	cout << "update remote" << endl;
	for (size_t i(0); i<get_Eb().size(); ++i){
		for (size_t j(0); j<get_Eb()[i]->get_ErP().size(); ++j){
			if (get_Eb()[i]->get_ErP()[j]->get_connect()){
				update_remote_p(i, j);
			}
		}
		for (size_t j(0); j<get_Eb()[i]->get_ErF().size(); ++j){
			if (get_Eb()[i]->get_ErF()[j]->get_connect()){
				update_remote_f(i, j);
			}
		}
		for (size_t j(0); j<get_Eb()[i]->get_ErT().size(); ++j){
			if (get_Eb()[i]->get_ErT()[j]->get_connect()){
				update_remote_t(i, j);
			}
		}
		for (size_t j(0); j<get_Eb()[i]->get_ErC().size(); ++j){
			if (get_Eb()[i]->get_ErC()[j]->get_connect()){
				update_remote_c(i, j);
			}
		}
	}
}

void Simulation::update_remote_p(size_t i, size_t j)
{
	RobotP* robot(&(*(get_Eb()[i]->get_ErP()[j]))); //creation pointeur
	if (robot->get_dp() > maxD_prosp){}  //si distance max atteinte, ne bouge plus
	else{
		if (robot->get_dp() > (maxD_prosp - dim_max * sqrt(2))){ //condition pour maintenance
			robot->set_rt(true);
		}
		if (robot->get_at()){ //si atteint son but
			trouve_gisement(robot); //trouver gisement
			
			if (!(robot->get_fd())){  //si trouve rien, change son but
				prosp_changement_but(robot);
				
			}else{
				cout << "gisement trouvé" << endl; //recupère données, signal, change de but
				prosp_changement_but(robot);
			}
		}else{ //si pas atteint son but
			trouve_gisement(robot);
			if (robot->get_fd()){ //si trouve 
				cout << "gisement trouvé" << endl; //recupère données, signal, continue vers son but
			}//sinon, continue vers son but
		}
	}
	if (robot->get_rt()){ //si retour = true, position but deviens le centre de la base
		Point but(get_Eb()[i]->get_centre());
		robot->set_position_but(but);
	}	
	move_to_dest(robot);
	if (egalite(robot->get_position(), robot->get_position_but())){
		robot->set_at(true);
	}else{
		robot->set_at(false);
	}
	cout << robot->get_dp() << " " << robot->get_cycle() %4 << " " << robot->get_at() <<  endl;
}
	
void Simulation::update_remote_f(size_t i, size_t j){}
void Simulation::update_remote_t(size_t i, size_t j){}
void Simulation::update_remote_c(size_t i, size_t j){}
	
	
void Simulation::move_to_dest(RobotP* robot)
{
    Vect v = distanceAB(robot->get_position(), robot->get_position_but());
    double x(robot->get_position().x);
    double y(robot->get_position().y);
    if (v.norme < deltaD){
		x = x + v.x;
		y = y + v.y;
	}else{
		x = x + (deltaD*v.x)/v.norme;
		y = y +(deltaD*v.y)/v.norme;
	}
    robot->set_position(x, y);
    if (!(egalite(robot->get_position(), robot->get_position_but()))){
		double dp(robot->get_dp());
		dp = dp + sqrt(pow(((deltaD*v.x)/v.norme), 2) + pow(((deltaD*v.y)/v.norme), 2));
		robot->set_dp(dp);
	}
}

void Simulation::prosp_changement_but(RobotP* robot)
{
	int cycle((robot->get_cycle())%4);
	double x(robot->get_position().x);
	double y(robot->get_position().y);
	switch (cycle)
	{
		case 0:
			robot->set_position_but(x, dim_max-rayon_min);
			break;
		case 1:
			robot->set_position_but(x+2*rayon_min-10, y);
			break;
		case 2:
			robot->set_position_but(x, rayon_min);
			break;
		case 3:
			robot->set_position_but(x+2*rayon_min-10, y);
			break;
	}
	++cycle;
	robot->set_cycle(cycle);
}
	
//fonction qui cherche si un gisement existe en la position du robot

void Simulation::trouve_gisement(RobotP* robot){
    for(size_t g(0); g < get_Eg().size(); ++g){
        if (point_cercle(robot->get_position(),  get_Eg()[g]->get_centre(), get_Eg()[g]->get_rayon())){
            robot->set_fd(true);
            robot->set_position_gisement(get_Eg()[g]->get_centre().x, get_Eg()[g]->get_centre().y);
            robot->set_rayong(get_Eg()[g]->get_rayon());
            robot->set_capaciteg(get_Eg()[g]->get_capacite());
        }
    }
}

void Simulation::signal_gisement(RobotP* robot, size_t i)
{
	size_t tailleF(get_Eb()[i]->get_ErF().size());
	for (int j(0); i<tailleF; ++j){
		RobotF* robotF (&(*(get_Eb()[i]->get_ErF()[j])));
		Vect v(distanceAB(robot->get_position_gisement(), robotF->get_position()));
		if ((v.norme >= (maxD_forage - robotF->get_dp())) and (!(robotF->get_used()))){
			robotF->set_position_but(robot->get_position_gisement());
			robotF->set_used(true);
			break;
		}		
	}
	size_t tailleT(get_Eb()[i]->get_ErT().size());
	for (int j(0); j<tailleT; ++j){
		RobotT* robotT (&(*(get_Eb()[i]->get_ErT()[j])));
		Vect v(distanceAB(robot->get_position_gisement(), robotT->get_position()));
		if ((v.norme >= (maxD_transp - robotT->get_dp())) and (!(robotT->get_used()))){
			robotT->set_position_but(robot->get_position_gisement());
			robotT->set_used(true);
			break;
		}
	}
	robot->set_fd(false);
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
