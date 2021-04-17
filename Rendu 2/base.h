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
		std::vector<Robot*> Er;
		std::vector<RobotP*> ErP;
		std::vector<RobotF*> ErF;
		std::vector<RobotT*> ErT;
		std::vector<RobotC*> ErC;
		
	public :
		Base(double x, double y, double ressources, int nbP, int nbF, int nbT,int nbC);
		Point get_centre();
		double get_ressources();
		double get_rayon();
		std::vector<Robot*> get_Er();
		std::vector<RobotP*> get_ErP();
		std::vector<RobotF*> get_ErF();
		std::vector<RobotT*> get_ErT();
		std::vector<RobotC*> get_ErC();
		void intersection();
		void test_uid();
		void test_robocom();
		void decodage_robotP(int nbP, std::ifstream &config);
		void decodage_robotF(int nbF, std::ifstream &config);
		void decodage_robotT(int nbT, std::ifstream &config);
		void decodage_robotC(int nbC, std::ifstream &config);
};
		

void lecture_base(std::string line, std::ifstream &config);

void creer_base(double x, double y, double ressources, int nbP, int nbF, int nbT, 
                int nbC, std::ifstream &config);


#endif
