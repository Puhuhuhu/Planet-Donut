#include "simulation.h"
#include "constantes.h"
#include "gui.h"
#include <gtkmm.h>

int main (int argc, char *argv[])
{
	int arg(1);

	auto app = Gtk::Application::create(arg, argv, "org.gtkmm.projet");
	
	SimulationWindow win(argc, argv);
	
	win.set_default_size(10, 10);	
	
	win.set_resizable(true);
	
	return app->run(win);
}
