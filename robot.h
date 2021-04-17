#ifndef ROBOT_H
#define ROBOT_H
#include <string>

class Robot
{
    private :
        int uid;
        double dp;
        double x, y;
        double xb, yb;
        bool atteint;
        
    public :
        int get_uid();
        double get_x();
        double get_y();
        double get_xb();
        double get_yb();
        bool get_at();
        
};

class Rob_P : public Robot{
    private:
        double xg,yg, rayong, capaciteg;
        bool retour, found;
    public:
        bool get_rt();
        bool get_fd();
        double get_xg();
        double get_yg();
        double get_rg();
        double get_cg();
};

class Rob_F : public Robot{
    private :
    public:
};

class Rob_T : public Robot{
    private:
        bool retour;
    public:
        bool get_rt();
};

class Rob_C : public Robot{
    private :
    public:
};

void lecture_robotP(std::string line);

void lecture_robotF(std::string line);

void lecture_robotT(std::string line);

void lecture_robotC(std::string line);

#endif
