#ifndef SIMULATION_H
#define SIMULATION_H
#include <string>
#include <sstream>
#include <fstream>

class Simulation
{
	private :
		double nbG;
		double nbB;
		void decodage(std::string line, std::ifstream &config);
		
	public :
		void lecture(char *nom_config);
		Simulation();
};

#endif
