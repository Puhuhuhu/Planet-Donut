#include "simulation.h"
#include "constantes.h"
#include "gui.h"
#include <gtkmm.h>

int main (int argc, char *argv[])
{
	int x(1);
	Simulation simulation;
	if (argc == 2){
		simulation.lecture(argv[1]);		
	}
	auto app = Gtk::Application::create(x, argv, "org.gtkmm.projet");
	SimulationWindow win;
	win.set_default_size(10, 10);	
	win.set_resizable(true);
	return app->run(win);
}
