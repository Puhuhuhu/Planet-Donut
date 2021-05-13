#ifndef SIMULATION_H
#define SIMULATION_H
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "base.h"
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
		
};

#endif
