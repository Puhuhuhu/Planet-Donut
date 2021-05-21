#ifndef SIMULATION_H
#define SIMULATION_H
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "base.h"
#include "gisement.h"
#include <string>
#include <memory>

class Simulation
{
	private :
		double nbG;
		double nbB;
		void decodage(std::string line, std::ifstream &config);
		bool file_opened;
		
	public :
		void lecture(char *nom_config);
		void lecture(std::string nom_config);
		Simulation();
		void update_voisin();
		bool get_file_opened();
		void set_file_opened(bool etat);
		void save(std::string name);
		std::vector<Robot*> parcours_DFS(Robot* depart);
		void rec_DFS(std::vector<Robot*>& result, Robot* next);
		void connexion();
		void verif_connexion();
		void maintenance();
		void update_robot();
		void graphic_robot();
		void draw_base();
		void draw_gisement();
		void draw_robotP();
		void draw_robotF();
		void draw_robotT();
		void draw_robotC();
		void draw_liaison();
		void update_remote();
		void update_remote_p(size_t i, size_t j);
		void update_remote_f(size_t i, size_t j);
		void update_remote_t(size_t i, size_t j);
		void update_remote_c(size_t i, size_t j);
		
        void draw_rayon_comm();
    
        int compteur_base();
        int compteur_robotP(int base_numero);
        int compteur_robotC(int base_numero);
        int compteur_robotT(int base_numero);
        int compteur_robotF(int base_numero);
        double compteur_resources(int base_numero);
        void move_to_dest(Robot* robot);
        void prosp_changement_but(RobotP* robot);   
        void trouve_gisement(RobotP* robot);
        void signal_gisement(RobotP* robot, size_t i);
        void sur_gisement(RobotF* robot);
        void envoyer_robot_transp(RobotF* robot, size_t i);
        void forage(RobotT* robot, RobotF* robotF);
        void donner_ressources(RobotT* robot, size_t i);
};


#endif
