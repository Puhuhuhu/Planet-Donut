#ifndef GISEMENT_H
#define GISEMENT_H
#include <string>
#include <vector>
#include "geomod.h"
#include <sstream>
#include <memory>

class Gisement 
{
	private :
		Point centre;
		double rayon;
		double capacite;
		
	public :
		Gisement(double x, double y, double rayon, double capacite);
		double& get_rayon();
		double get_capacite();
		void set_capacite(double c);
		Point& get_centre();
		void intersection();
		
};
		

void lecture_gisement (std::string line);

void creer_gisement(double x, double y, double rayon, double capacite);

void intersection_base_gisement(Point centre, double rayon);

void save_gisement(std::ofstream& sauvegarde);

std::vector<std::unique_ptr<Gisement>>& get_Eg();

#endif
