#include "gisement.h"
#include "message.h"
#include "geomod.h"
#include "constantes.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;



static vector<Gisement> Eg; //Ensemble Eg


//Fonctions
void lecture_gisement (string line)
{
	double x, y, rayon, capacite;
	istringstream data(line);
	if (!(data >> x >> y >> rayon >> capacite)){exit(0);} // verification de la syntaxe 
	else{creer_gisement(x, y, rayon, capacite);}
}



void creer_gisement(double x, double y, double rayon, double capacite)
{
	if ((rayon >= rayon_min) and (rayon <= rayon_max)   //verification des normes
	and (capacite <= 1000*(rayon/rayon_min)*(rayon/rayon_min))){
		coord_norm(x);
		coord_norm(y);
		Gisement g(x, y, rayon, capacite);  //Creation du gisement
		g.intersection(); //Verification des possibles intersections
		Eg.push_back(g);  //ajout du gisement dans l'ensemble Eg
	}else{exit(0);}	
}


void intersection_base_gisement(Point centre, double rayon){
	for(size_t i(0); i<Eg.size(); ++i){
		Point centre2(Eg[i].get_centre());
		double rayon2(Eg[i].get_rayon());
		if (cercle_cercle(centre, rayon, centre2, rayon2)){
			cout << message ::base_field_superposition(centre.x, centre.y,
			centre2.x, centre2.y) << endl;
			exit(0);
		}
	}
}
	

//Methodes
void Gisement::intersection(){
	//parcours de l'ensemble
	for(size_t i(0); i<Eg.size(); ++i){
		Point centre2(Eg[i].get_centre());
		double rayon2(Eg[i].get_rayon());
		//test d'intersection
		if(cercle_cercle(centre, rayon, centre2, rayon2)){
			cout << message::field_superposition(centre.x, centre.y, 
			centre2.x, centre2.y) << endl;
			exit(0); //quitte le programme si il y a une intersection
		}
	}
}
			

//Constructeur
Gisement::Gisement(double x, double y, double rayon, double capacite) 
				 : centre({x, y}), rayon(rayon), capacite(capacite) {}			 

//Getters
double Gisement::get_rayon() {return rayon;}   

double Gisement::get_capacite() {return capacite;}

Point Gisement::get_centre() {return centre;}

