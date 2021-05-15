#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <gtkmm.h>

void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr);

void graphic_draw_gisement(double x, double y, double rayon, double r, double g, double b);

void graphic_draw_base(double x, double y, double rayon, int i);

void graphic_draw_robot(double x, double y, int i);

void graphic_draw_line(double robotA_x, double robotA_y, double robotB_x, double robotB_y);

void graphic_draw_robot_comm(double centre_x, double centre_y);

void graphic_draw_rectangle(double xmin, double xmax, double ymin, double ymax, double dim_max);

#endif
