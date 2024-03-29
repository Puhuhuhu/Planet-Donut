#ifndef GISEMENT_H
#define GISEMENT_H
#include <string>
#include <vector>
#include "geomod.h"

class Gisement 
{
	private :
		Point centre;
		double rayon;
		double capacite;
		
	public :
		Gisement(double x, double y, double rayon, double capacite);
		double get_rayon();
		double get_capacite();
		Point get_centre();
		void intersection();
		
};
		

void lecture_gisement (std::string line);

void creer_gisement(double x, double y, double rayon, double capacite);

void intersection_base_gisement(Point centre, double rayon);

#endif
