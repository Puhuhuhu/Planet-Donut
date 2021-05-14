#include "graphic.h"
#include <iostream>

static const Cairo::RefPtr<Cairo::Context>* ptcr(nullptr);

static double height;
static double width;
static double xc;
static double yc;

void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr, double h, double w, double x, double y)
{
	ptcr = &cr;
	height = h;
	width = w;
	xc = x;
	yc = y;
	
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
	
