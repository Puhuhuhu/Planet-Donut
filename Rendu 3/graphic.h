#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <gtkmm.h>

void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr);
void drawstroke(double width, double height, double xc, double yc);


#endif
