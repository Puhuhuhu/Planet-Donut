#include "geomod.h"
#include <iostream>

int main()
{
	double x1, y1, r1, x2, y2, r2;
	setMax(10);
	std::cin >> x1 >>y1>>r1>>x2>>y2>>r2;
	Point p1({x1, y1});
	Point p2({x2, y2});
	std::cout << cercle_cercle(p1, r1, p2, r2) << std::endl;
	Cercle c1({r1, p1});
	Cercle c2({r2, p2});
	std::cout << cercle_cercle(c1, c2) << std::endl;
	return 0;
}
