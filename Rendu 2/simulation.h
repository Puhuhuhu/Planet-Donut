#ifndef SIMULATION_H
#define SIMULATION_H
#include <string>

class Simulation
{
	private :
		double nbG;
		double nbB;
		void decodage(std::string line);
		
	public :
		void lecture(char *nom_config);
		Simulation();
};

#endif
