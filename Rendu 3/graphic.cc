#include "graphic.h"
#include <iostream>
#include "constantes.h"

static const Cairo::RefPtr<Cairo::Context>* ptcr(nullptr);

void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr)
{
	ptcr = &cr;
}

void graphic_draw_gisement(double x, double y, double rayon, double r, double g, double b)
{
	(*ptcr)->set_source_rgb(r, g, b);
	(*ptcr)->arc(x, y, rayon, 0, 2*M_PI);
	(*ptcr)->stroke();
}

void graphic_draw_base(double x, double y, double rayon, int i)
{
	switch (i){
		case 0:
			(*ptcr)->set_source_rgb(1, 0, 0);
			break;
		
		case 1:
			(*ptcr)->set_source_rgb(0, 1, 0);
			break;
		
		case 2:
			(*ptcr)->set_source_rgb(0, 0, 1);
			break;
			
		case 3:
			(*ptcr)->set_source_rgb(1, 1, 0);
			break;
			
		case 4:
			(*ptcr)->set_source_rgb(1, 0, 1);
			break;
			
		case 5:
			(*ptcr)->set_source_rgb(0, 1, 1);
			break;
		}
			
	(*ptcr)->arc(x, y, 10*rayon, 0, 2*M_PI);
	(*ptcr)->stroke();
}

void graphic_draw_robot(double x, double y, int i)
{
	switch (i){
		case 0:
			(*ptcr)->set_source_rgb(1, 0, 0);
			break;
		
		case 1:
			(*ptcr)->set_source_rgb(0, 1, 0);
			break;
		
		case 2:
			(*ptcr)->set_source_rgb(0, 0, 1);
			break;
			
		case 3:
			(*ptcr)->set_source_rgb(1, 1, 0);
			break;
			
		case 4:
			(*ptcr)->set_source_rgb(1, 0, 1);
			break;
			
		case 5:
			(*ptcr)->set_source_rgb(0, 1, 1);
			break;
		}
	(*ptcr)->set_line_width(10.0);
	(*ptcr)->arc(x, y, 1, 0, 2*M_PI);
	(*ptcr)->stroke();
}

void graphic_draw_line(double robotA_x, double robotA_y, double robotB_x, double robotB_y){
    (*ptcr)->set_line_width(2.0);
    (*ptcr)->set_source_rgb(0.8, 0, 1);
    (*ptcr)->move_to(robotA_x,robotA_y);
    (*ptcr)->line_to(robotB_x, robotB_y);
    (*ptcr)->stroke();
}

//dessine le perimetre de communication des robots
void graphic_draw_robot_comm(double centre_x, double centre_y){
    (*ptcr)->set_line_width(2.0);
    (*ptcr)->set_source_rgb(0.6,0.6,0.6); // choisir la nouvelle couleur
    (*ptcr)->arc(centre_x, centre_y, rayon_comm, 0, 2*M_PI);
    (*ptcr)->stroke();
}

void graphic_draw_rectangle(double xmin, double xmax, double ymin, double ymax, double dim_max)
{
	(*ptcr)->set_source_rgb(0.94, 0.94, 0.94);
	(*ptcr)->set_line_width(1);
	(*ptcr)->move_to(xmin, ymin);
	(*ptcr)->line_to(xmin, ymax);
	(*ptcr)->line_to(-dim_max, ymax);
	(*ptcr)->line_to(-dim_max, ymin);
	(*ptcr)->line_to(xmin, ymin);
	(*ptcr)->fill_preserve();
	
	(*ptcr)->move_to(xmax, ymax);
	(*ptcr)->line_to(dim_max, ymax);
	(*ptcr)->line_to(dim_max, ymin);
	(*ptcr)->line_to(xmax, ymin);
	(*ptcr)->line_to(xmax, ymax);
	(*ptcr)->fill_preserve();
	
	(*ptcr)->stroke();
}
	
	


