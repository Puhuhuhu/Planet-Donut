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
        bool sorti_de_maintenance;
        Point ancienne_pos;
        bool connect_liaison;
        
    public :
		void set_connect_liaison(bool c);
		bool get_connect_liaison();
		void set_connect(bool c);
		bool get_connect();
		void set_visited(bool v);
		bool get_visited();
        int get_uid();
        double get_dp();
        void set_dp(double d);
        Point& get_position();
        Point& get_position_but();
        void set_position(double x, double y);
        void set_position_but(double x, double y);
        void set_position_but(Point but);
        bool get_at();
        void set_at(bool a);
        
        std::vector<Robot*>& get_voisin();
        Robot(int uid, double dp, double x, double y, double xb, 
              double yb, bool atteint);
        
};

class RobotP : public Robot{
    private:
		Point position_gisement;
        double rayong, capaciteg;
        bool retour, found;
        int cycle;
        bool sorti_de_maintenance;
        bool ancien_connect;
        Point ancienne_pos;
        int domaine; //%2 : 0 = haut, 1 = bas
        
    public:
//    getter
		bool get_ancien_connect();
		void set_ancien_connect(bool a);
		int get_domaine();
		void set_domaine(int d);
    	int get_cycle();
		void set_cycle(int c);
        bool get_rt();
        void set_rt(bool r);
        bool get_fd();
        Point& get_position_gisement();
        double get_rg();
        double get_cg();
        Point& get_ancienne_pos();
        bool get_sorti_de_maintenance();
       
//        setter
    
        void set_ancienne_pos(double x, double y);
        void set_sorti_de_maintenance(bool repation_finie);
        void set_fd(bool fd);
        void set_position_gisement(double x, double y);
        void set_rayong(double r);
        void set_capaciteg(double c);
        RobotP(int uid, double dp, double x, double y, double xb, 
               double yb, bool atteint, bool retour, bool found, double xg, double yg, double rayong, 
               double capaciteg);
};

class RobotF : public Robot{
    private :
		bool used;
		bool transp_envoye;
		double ressources_recup;
		bool gisement_vide;
    public:
		bool get_gisement_vide();
		void set_gisement_vide(bool g);
		bool get_transp_envoye();
		void set_transp_envoye(bool t);
		bool get_used();
        void set_used(bool u);
        void set_ressources_recup(double r);
        double get_ressources_recup();
		RobotF(int uid, double dp, double x, double y, double xb, 
               double yb, bool atteint);
		
};

class RobotT : public Robot{
    private:
        bool retour;
        bool used;
        RobotF* robotF;
        double ressources_transp;
    public:
		RobotF* get_robotF();
		double get_ressources_transp();
		void set_ressources_transp(double r);
		void set_robotF (RobotF* r);
        bool get_rt();
        void set_rt(bool r);
        bool get_used();
        void set_used(bool u);
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
