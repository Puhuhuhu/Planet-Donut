#include "graphic.h"

static const Cairo::RefPtr<Cairo::Context>* ptcr(nullptr);

void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr)
{
	ptcr = &cr;
}

void drawstroke(double width, double height, double xc, double yc)
{
	(*ptcr)->set_source_rgb(0.8, 0, 0);
	(*ptcr)->set_line_width(10);
	(*ptcr)->move_to(0, 0);
	(*ptcr)->line_to(xc, yc);
	(*ptcr)->stroke();
}

