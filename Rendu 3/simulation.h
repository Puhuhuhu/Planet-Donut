#ifndef SIMULATION_H
#define SIMULATION_H
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "base.h"

class Simulation
{
	private :
		double nbG;
		double nbB;
		void decodage(std::string line, std::ifstream &config);
		
	public :
		void lecture(char *nom_config);
		Simulation();
		void update_voisin();
};

#endif
