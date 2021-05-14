#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <gtkmm.h>

void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr, double height, double width, double xc, double yc);

void graphic_draw_gisement(double x, double y, double rayon, double r, double g, double b);

void graphic_draw_base(double x, double y, double rayon, int i);

void graphic_draw_robot(double x, double y, int i);

#endif
