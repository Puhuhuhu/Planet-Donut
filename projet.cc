#include "geomod.h"
#include "message_geomod.h"
#include <iostream>
#include <cstring>

using namespace std;
using namespace message_geomod;


int main(int argc, char* argv[])
{
	
	int i(0);
	size_t nb(0);
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
			break;
	}
	
	return 0;
}
