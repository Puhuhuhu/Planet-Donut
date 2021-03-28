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
	i = stod(argv[1]);
	if (argc < 3) {bad_argc(); exit(0);}
	
	double init_max(stod(argv[2]));
	setMax(init_max);
	
	switch(i)
	{
		case 1:
			if (argc == 3){
				print_max(init_max, getMax(), getEpsilon());
			}else{
				bad_argc();
			}
			break;
			
		case 2:
			if (argc == 5){
				double x_init (stod(argv[3]));
				double y_init (stod(argv[4]));
				Point p({x_init, y_init});
				coord_norm(p);
				print_point(x_init, y_init, p.x, p.y);
			}else{
				bad_argc();
			}
			break;
			
		case 3: 
			if (argc == 7){
				double Ax_init (stod(argv[3]));
				double Ay_init (stod(argv[4]));
				Point A({Ax_init, Ay_init});				
				double Bx_init (stod(argv[5]));
				double By_init (stod(argv[6]));
				Point B({Bx_init, By_init});
				Vect V(distanceAB(A, B));
				print_vect(V.norme, V.x, V.y);
			}
				else{
				bad_argc();
			}	
			break;
		
		case 4:
			if (argc == 7){
				double Ax_init (stod(argv[3]));
				double Ay_init (stod(argv[4]));
				Point A({Ax_init, Ay_init});				
				double Bx_init (stod(argv[5]));
				double By_init (stod(argv[6]));
				Point B({Bx_init, By_init});
				print_equal_point(egalite(A, B), A.x, A.y, B.x, B.y);
			}else{
				bad_argc();
			}
			break;
					
		case 5:
			if (argc == 8){
				double x_init (stod(argv[3]));
				double y_init (stod(argv[4]));
				Point p({x_init, y_init});
				double xc_init (stod(argv[5]));
				double yc_init (stod(argv[6]));
				double r (stod(argv[7]));
				Point centre({xc_init, yc_init});
				coord_norm(centre);
				Cercle c ({r, centre});
				print_include_point(point_cercle(p, c), x_init, y_init, xc_init, yc_init, r);
			}else{
				bad_argc();
			}
			break;
			
		case 6:
			if (argc == 9){
				double xc1_init (stod(argv[3]));
				double yc1_init (stod(argv[4]));
				double r1_init (stod(argv[5]));
				double xc2_init (stod(argv[6]));
				double yc2_init (stod(argv[7]));
				double r2_init (stod(argv[8]));
				Point centre1 ({xc1_init, yc1_init});
				Point centre2 ({xc2_init, yc2_init});
				Cercle c1 ({r1_init, centre1});
				Cercle c2 ({r2_init, centre2});
				print_intersect(cercle_cercle(c1, c2), c1.centre.x, c1.centre.y, c1.rayon, c2.centre.x, c2.centre.y, c2.rayon);
			}else{
				bad_argc();
			}
			break;
	}
	
	return 0;
}
