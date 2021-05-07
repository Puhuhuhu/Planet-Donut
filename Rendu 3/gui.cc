#include "gui.h"
#include "simulation.h"
#include "graphic.h"
#include "geomod.h"
#include <gtkmm.h>
#include <cairomm/context.h>
#include <iostream>

using namespace std;

MyArea::MyArea() {}
MyArea::~MyArea() {}

SimulationWindow::~SimulationWindow() {}
SimulationWindow::SimulationWindow() :
	count(0),
	started(0),
	m_box(Gtk::ORIENTATION_VERTICAL, 10),
	m_box_top(Gtk::ORIENTATION_HORIZONTAL, 10),
	m_box_top_left(Gtk::ORIENTATION_VERTICAL, 10),
	m_box_top_right(Gtk::ORIENTATION_VERTICAL, 10),
	m_box_bottom(Gtk::ORIENTATION_VERTICAL, 10),
	m_box_bottom_info(Gtk::ORIENTATION_VERTICAL, 10),
	m_box_bottom_label(Gtk::ORIENTATION_HORIZONTAL, 0),
	m_box_frame_general(Gtk::ORIENTATION_VERTICAL, 10),
	m_box_frame_toggledisplay(Gtk::ORIENTATION_VERTICAL, 10),
	m_button_startstop("start"),
	m_button_step("step"),
	m_button_exit("exit"),
	m_button_open("open"),
	m_button_save("save"),
	m_button_togglelink("toggle link"),
	m_button_togglerange("toggle range"),
	m_label_Uid("Uid"),
	m_label_nbP("nbP"),
	m_label_nbF("nbF"),
	m_label_nbT("nbT"),
	m_label_nbC("nbC"),
	m_label_amountresource("Amount resource"),
	m_label_missioncompleteness("Mission completeness"),
	m_frame_general("General"),
	m_frame_toggledisplay("Toggle display")
	
{
	set_title("Simulation");
	set_border_width(0);
	
	add(m_box);
	m_box.set_border_width(10);
	m_box.pack_start(m_box_top);
	m_box_top.pack_start(m_box_top_left, Gtk::PACK_SHRINK);
	m_box_top.pack_start(m_box_top_right);
	m_box.pack_start(m_box_bottom);
	
	m_area.set_size_request(200, 200);
	m_box_top_right.pack_start(m_area);
	
	m_frame_general.add(m_box_frame_general);
	m_box_frame_general.pack_start(m_button_exit);
	m_box_frame_general.pack_start(m_button_open);
	m_box_frame_general.pack_start(m_button_save);
	m_box_frame_general.pack_start(m_button_startstop);
	m_box_frame_general.pack_start(m_button_step);
	m_box_top_left.pack_start(m_frame_general);
	
	m_frame_toggledisplay.add(m_box_frame_toggledisplay);
	m_box_frame_toggledisplay.pack_start(m_button_togglelink);
	m_box_frame_toggledisplay.pack_start(m_button_togglerange);
	m_box_top_left.pack_start(m_frame_toggledisplay);
	

	m_box_bottom.pack_start(m_box_bottom_label, Gtk::PACK_SHRINK);	
	m_frame_Uid.add(m_label_Uid);
	m_frame_nbP.add(m_label_nbP);
	m_frame_nbF.add(m_label_nbF);
	m_frame_nbT.add(m_label_nbT);
	m_frame_nbC.add(m_label_nbC);
	m_frame_ammountresource.add(m_label_amountresource);
	m_frame_missioncompleteness.add(m_label_missioncompleteness);
	m_box_bottom_label.pack_start(m_frame_Uid);
	m_box_bottom_label.pack_start(m_frame_nbP);
	m_box_bottom_label.pack_start(m_frame_nbF);
	m_box_bottom_label.pack_start(m_frame_nbT);
	m_box_bottom_label.pack_start(m_frame_nbC);
	m_box_bottom_label.pack_start(m_frame_ammountresource);
	m_box_bottom_label.pack_start(m_frame_missioncompleteness);
	
	m_box_bottom.pack_start(m_box_bottom_info);
	
	m_button_exit.signal_clicked().connect(sigc::mem_fun(*this, &SimulationWindow::on_button_clicked_exit));
	m_button_startstop.signal_clicked().connect(sigc::mem_fun(*this, &SimulationWindow::on_button_clicked_startstop));
	m_button_step.signal_clicked().connect(sigc::mem_fun(*this, &SimulationWindow::on_button_clicked_step));
	Glib::signal_idle().connect( sigc::mem_fun(*this, &SimulationWindow::on_idle) );
	
	show_all_children();
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	return true;
}

void SimulationWindow::on_button_clicked_exit()
{
	exit(0);
}

void SimulationWindow::on_button_clicked_startstop()
{
	started = !started;
	if (started == 0){
		m_button_startstop.set_label("start");
	}else{
		m_button_startstop.set_label("stop");
	}
}

void SimulationWindow::on_button_clicked_step()
{
	cout << "mise à jour de la simulation " << ++count << endl;
}

bool SimulationWindow::on_idle()
{
	if (started) {
		cout << "mise à jour de la simulation " << ++count << endl;
	}
	return true;
}
	
