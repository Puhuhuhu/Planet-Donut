
#include "robot.h"
#include "gisement.h"
#include "message.h"
#include "geomod.h"
#include "constantes.h"
#include <string>
#include <iostream>

using namespace std;

void lecture_robotP(string line)
{
    cout << "La fonction lecture_robotP a été appelée ! : " << line << endl;
}
    
void lecture_robotF(string line)
{
    cout << "La fonction lecture_robotF a été appelée ! : " << line << endl;
}

void lecture_robotT(string line)
{
    cout << "La fonction lecture_robotT a été appelée ! : " << line << endl;
}

void lecture_robotC(string line)
{
    cout << "La fonction lecture_robotC a été appelée ! : " << line << endl;
}
int Robot::get_uid(){
    return uid;
    }

double Robot::get_x(){
    return x;
    }
    
double Robot::get_y(){
    return y;
    }
    
double Robot::get_xb(){
    return xb;
    }
    
double Robot::get_yb(){
    return yb;
    }
    
bool Robot::get_at(){
    return atteint;
    }
    
bool Rob_P::get_rt(){
    return retour;
    }
    
bool Rob_P::get_fd(){
    return found;
    }

double Rob_P::get_xg(){
    return xg;
}
double Rob_P::get_yg(){
    return yg;
}

double Rob_P::get_rg(){
    return rayong;
}

double Rob_P::get_cg(){
    return capaciteg;
}

bool Rob_T::get_rt(){
    return retour;
}
