#ifndef BASE_H
#define BASE_H
#include "geomod.h"
#include <string>
#include <vector>
#include "robot.h"

class Base
{
	private :
		Point centre;
		double ressources;
		double rayon;
		int nbP;
		int nbF;
		int nbT;
		int nbC;
		std::vector<Robot> Er;
		
	public :
		Base(double x, double y, double ressources, int nbP, int nbF, int nbT,int nbC);
		Point get_centre();
		double get_ressources();
		double get_rayon();
		int get_nbP();
		int get_nbF();
		int get_nbT();
		int get_nbC();
		std::vector<Robot> get_Er();
		void intersection();
		void test_uid(std::vector<Robot> Er);
		void test_robocom(std::vector<Robot> Er);
		void decodage_robotP(int nbP, std::ifstream &config);
		void decodage_robotF(int nbF, std::ifstream &config);
		void decodage_robotT(int nbT, std::ifstream &config);
		void decodage_robotC(int nbC, std::ifstream &config);
};
		

void lecture_base(std::string line, std::ifstream &config);

void creer_base(double x, double y, double ressources, int nbP, int nbF, int nbT, 
                int nbC, std::ifstream &config);


#endif
