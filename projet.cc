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
	}
	
	return 0;
}
