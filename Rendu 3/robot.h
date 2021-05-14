#ifndef ROBOT_H
#define ROBOT_H
#include <string>
#include <vector>
#include "geomod.h"
#include <memory>
#include <sstream>

class Robot
{
    protected :
        int uid;
        double dp;
        Point position;
        Point position_but;
        bool atteint;
        std::vector<Robot*> voisin;
        bool visited;
        bool connect; //false = autonomous, true = remote
        
    public :
		void set_connect(bool c);
		bool get_connect();
		void set_visited(bool v);
		bool get_visited();
        int get_uid();
        double get_dp();
        void set_dp(double d);
        Point& get_position();
        Point get_position_but();
        bool get_at();
        std::vector<Robot*>& get_voisin();
        Robot(int uid, double dp, double x, double y, double xb, 
              double yb, bool atteint);
        
};

class RobotP : public Robot{
    private:
		Point position_gisement;
        double rayong, capaciteg;
        bool retour, found;
    public:
        bool get_rt();
        bool get_fd();
        Point get_position_gisement();
        double get_rg();
        double get_cg();
        RobotP(int uid, double dp, double x, double y, double xb, 
               double yb, bool atteint, bool retour, bool found, double xg, double yg, double rayong, 
               double capaciteg);
};

class RobotF : public Robot{
    private :
    public:
		RobotF(int uid, double dp, double x, double y, double xb, 
               double yb, bool atteint);
		
};

class RobotT : public Robot{
    private:
        bool retour;
    public:
        bool get_rt();
        RobotT(int uid, double dp, double x, double y, double xb, 
               double yb, bool atteint, bool retour);
};

class RobotC : public Robot{
    private :
    public:
		RobotC(int uid, double dp, double x, double y, double xb, 
               double yb, bool atteint);
};

RobotP creer_robotP(std::string line);

RobotF creer_robotF(std::string line);

RobotT creer_robotT(std::string line);

RobotC creer_robotC(std::string line);

#endif