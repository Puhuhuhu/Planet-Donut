#ifndef BASE_H
#define BASE_H
#include "geomod.h"
#include <string>
#include <vector>
#include "robot.h"
#include <memory>
#include <sstream>

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
		std::vector<std::shared_ptr<Robot>> Er;
		std::vector<std::shared_ptr<RobotP>> ErP;
		std::vector<std::shared_ptr<RobotF>> ErF;
		std::vector<std::shared_ptr<RobotT>> ErT;
		std::vector<std::shared_ptr<RobotC>> ErC;
		int nb_com;
				
	public :
		Base(double x, double y, double ressources, int nbP, int nbF, int nbT,int nbC);
		Point& get_centre();
		double get_ressources();
		void set_ressources(double r);
		double get_rayon();
		int get_nbP();
		int get_nbF();
		int get_nbT();
		int get_nbC();
		void set_nbP(int n);
		void set_nbF(int n);
		void set_nbT(int n);
		void set_nbC(int n);
		std::vector<std::shared_ptr<Robot>>& get_Er();
		std::vector<std::shared_ptr<RobotP>>& get_ErP();
		std::vector<std::shared_ptr<RobotF>>& get_ErF();
		std::vector<std::shared_ptr<RobotT>>& get_ErT();
		std::vector<std::shared_ptr<RobotC>>& get_ErC();
		void intersection();
		void test_uid();
		void test_robocom();
		void decodage_robotP(int nbP, std::ifstream &config);
		void decodage_robotF(int nbF, std::ifstream &config);
		void decodage_robotT(int nbT, std::ifstream &config);
		void decodage_robotC(int nbC, std::ifstream &config);
		int get_nb_com();
		void set_nb_com(int n);
};
		

void lecture_base(std::string line, std::ifstream &config);

void creer_base(double x, double y, double ressources, int nbP, int nbF, int nbT, 
                int nbC, std::ifstream &config);

std::vector<std::unique_ptr<Base>>& get_Eb();

void save_base(std::ofstream& sauvegarde);

void save_robot(std::ofstream& sauvegarde, int j);
void save_robotP(std::ofstream& sauvegarde, int j, int i);
void save_robotF(std::ofstream& sauvegarde, int j, int i);
void save_robotT(std::ofstream& sauvegarde, int j, int i);
void save_robotC(std::ofstream& sauvegarde, int j, int i);

#endif
