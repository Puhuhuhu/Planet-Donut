#include "geomod.h"
#include "message_geomod.h"
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;
using namespace message_geomod;


int main(int argc, char* argv[])
{
	
	int i(0);
	size_t nb(0);
	if (argv[1])
		i = stod(argv[1], &nb);
	
	switch(i)
	{
		case 1:
			if (argc == 3){
				double init_max (stod(argv[2], &nb));
				setMax(init_max);
				print_max(init_max, getMax(), getEpsilon());
			}else{
				bad_argc();
			}
			break;
		case 2:
			if (argc == 5){
				double init_max (stod(argv[2], &nb));
				setMax(init_max);
				double x_init (stod(argv[3], &nb));
				double y_init (stod(argv[4], &nb));
				Point p({x_init, y_init});
				coord_norm(p);
				print_point(x_init, y_init, p.x, p.y);
			}else{
				bad_argc();
			}
		case 3: 
			if (argc == 7){
				double init_max (stod(argv[2], &nb));
				setMax(init_max);
				
				double Ax_init (stod(argv[3], &nb));
				double Ay_init (stod(argv[4], &nb));
				Point A({Ax_init, Ay_init});
				
				double Bx_init (stod(argv[5], &nb));
				double By_init (stod(argv[6], &nb));
				Point B({Bx_init, By_init});
				double petit_norm(getMax()), petit_x, petit_y;
				for(int k = -1; k < 2; k++){
					//faire varier la position de B selon x
					double B_plan_x = B.x + k * 2* getMax();
					double distanceX(abs(A.x - B_plan_x));
					for(int j = -1; j < 2; j++){
						//faire varier la position de B selon y
						double B_plan_y = B.y + j * 2*getMax();
						double distanceY(abs(A.y - B_plan_y));
						double norm( sqrt( distanceX * distanceX + distanceY  * distanceY));
						if(norm < petit_norm){
								petit_norm = norm;
								petit_x = distanceX;
								petit_y = distanceY;
						}
					}
				}
			print_vect(petit_norm, petit_x, petit_y);
	
			}
				else{
				bad_argc();
			}
				
			break;
	}
	
	return 0;
}
