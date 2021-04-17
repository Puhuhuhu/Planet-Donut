#ifndef ROBOT_H
#define ROBOT_H
#include <string>
#include <vector>
#include "geomod.h"

class Robot
{
    protected :
        int uid;
        double dp;
        Point position;
        Point position_base;
        bool atteint;
        
    public :
        int get_uid();
        Point get_position();
        double get_xb();
        double get_yb();
        bool get_at();
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
        double get_xg();
        double get_yg();
        double get_rg();
        double get_cg();
        RobotP(int uid, double dp, double x, double y, double xb, 
               double yb, bool atteint, double xg, double yg, double rayong, 
               double capaciteg, bool retour, bool found);
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
