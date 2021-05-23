#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <gtkmm.h>

void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr);

void graphic_draw_gisement(double x, double y, double rayon, double capacite, 
						   double capacite_ini);

void graphic_draw_base(double x, double y, double rayon, int i);

void graphic_draw_robotP(double x, double y, int i);

void graphic_draw_robotF(double x, double y, int i);

void graphic_draw_robotT(double x, double y, int i);

void graphic_draw_robotC(double x, double y, int i);

void graphic_draw_line(double robotA_x, double robotA_y, double robotB_x, 
				       double robotB_y);

void graphic_draw_robot_comm(double centre_x, double centre_y);

void graphic_draw_rectangle(double xmin, double xmax, double ymin, double ymax, 
						    double dim_max);

#endif
