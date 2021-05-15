#include "gui.h"
#include "simulation.h"
#include "graphic.h"
#include "geomod.h"
#include <gtkmm.h>
#include <cairomm/context.h>
#include <iostream>
#include "constantes.h"
#include <memory>

using namespace std;

static Simulation simulation;

static bool togglelink(0);
static bool togglerange(0);

static void orthographic_projection(const Cairo::RefPtr<Cairo::Context>& cr, 
									Frame frame)
{
	// déplace l'origine au centre de la fenêtre
	cr->translate(frame.width/2, frame.height/2);
  
	// normalise la largeur et hauteur aux valeurs fournies par le cadrage
	// ET inverse la direction de l'axe Y
	cr->scale(frame.width/(frame.xMax - frame.xMin), 
             -frame.height/(frame.yMax - frame.yMin));
  
	// décalage au centre du cadrage
	cr->translate(-(frame.xMin + frame.xMax)/2, -(frame.yMin + frame.yMax)/2);
}

MyArea::MyArea() {}
MyArea::~MyArea() {}

SimulationWindow::~SimulationWindow() {}
SimulationWindow::SimulationWindow(int argc, char *argv[]) :
	count(0),
	started(0),
	m_box(Gtk::ORIENTATION_VERTICAL, 0),
	m_box_top(Gtk::ORIENTATION_HORIZONTAL, 0),
	m_box_top_left(Gtk::ORIENTATION_VERTICAL, 0),
	m_box_top_right(Gtk::ORIENTATION_VERTICAL, 0),
	m_box_bottom(Gtk::ORIENTATION_VERTICAL, 0),
	m_box_bottom_info(Gtk::ORIENTATION_VERTICAL, 0),
	m_box_bottom_label(Gtk::ORIENTATION_HORIZONTAL, 0),
	m_box_frame_general(Gtk::ORIENTATION_VERTICAL, 0),
	m_box_frame_toggledisplay(Gtk::ORIENTATION_VERTICAL, 0),
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
    m_label_NB("5"),
	m_frame_general("General"),
	m_frame_toggledisplay("Toggle display")
	
{	
	Frame prm;
	prm.xMin = -dim_max;
	prm.xMax = dim_max;
	prm.yMin = -dim_max;
	prm.yMax = dim_max;
	prm.asp = (prm.xMax-prm.xMin) / (prm.yMax-prm.yMin);
	prm.height = 800;
	prm.width = prm.height*prm.asp;
	m_area.setFrame(prm);
	
	set_title("Simulation");
	set_border_width(0);
	add(m_box);
	m_box.set_border_width(10);
	m_box.pack_start(m_box_top);
	m_box_top.pack_start(m_box_top_left, Gtk::PACK_SHRINK);
	m_box_top.pack_start(m_box_top_right);
	m_box.pack_start(m_box_bottom);
	
	m_area.set_size_request(prm.height, prm.width);
	m_box_top_right.add(m_area);
	
	m_frame_general.add(m_box_frame_general);
	m_box_frame_general.pack_start(m_button_exit, false, false);
	m_box_frame_general.pack_start(m_button_open, false, false);
	m_box_frame_general.pack_start(m_button_save, false, false);
	m_box_frame_general.pack_start(m_button_startstop, false, false);
	m_box_frame_general.pack_start(m_button_step, false, false);
	m_box_top_left.pack_start(m_frame_general, false, false);
	
	m_frame_toggledisplay.add(m_box_frame_toggledisplay);
	m_box_frame_toggledisplay.pack_start(m_button_togglelink, false, false);
	m_box_frame_toggledisplay.pack_start(m_button_togglerange, false, false);
	m_box_top_left.pack_start(m_frame_toggledisplay, false, false);
	

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
	//m_box_bottom_info.set_vexpand();
	m_box_bottom.pack_start(m_box_bottom_info, Gtk::PACK_SHRINK);
	
	m_button_exit.signal_clicked().connect(sigc::mem_fun(*this, &SimulationWindow::on_button_clicked_exit));
	m_button_startstop.signal_clicked().connect(sigc::mem_fun(*this, &SimulationWindow::on_button_clicked_startstop));
	m_button_step.signal_clicked().connect(sigc::mem_fun(*this, &SimulationWindow::on_button_clicked_step));
	m_button_open.signal_clicked().connect(sigc::mem_fun(*this, &SimulationWindow::on_button_clicked_open));
	m_button_save.signal_clicked().connect(sigc::mem_fun(*this, &SimulationWindow::on_button_clicked_save));
	m_button_togglelink.signal_clicked().connect(sigc::mem_fun(*this, &SimulationWindow::on_button_clicked_togglelink));
	m_button_togglerange.signal_clicked().connect(sigc::mem_fun(*this, &SimulationWindow::on_button_clicked_togglerange));
	Glib::signal_idle().connect( sigc::mem_fun(*this, &SimulationWindow::on_idle) );
	creation_infos();
	
	show_all_children();
	
	if (argc == 2){
		simulation.lecture(argv[1]);	
		simulation.update_voisin();
		simulation.connexion();
		m_area.refresh();
	}
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	Gtk::Allocation allocation = get_allocation();
	int width = allocation.get_width();
	int height = allocation.get_height();
	
	graphic_set_context(cr);
	
	adjust_frame();
	orthographic_projection(cr, frame);
	
	cr->set_line_width(5);
	cr->set_source_rgb(0.1, 0.1, 0.1);
	cr->move_to(-dim_max, dim_max);
	cr->line_to(dim_max, dim_max);
	cr->line_to(dim_max, -dim_max);
	cr->line_to(-dim_max, -dim_max);
	cr->line_to(-dim_max, dim_max);
	cr->stroke();
	
	simulation.draw_base();
	simulation.draw_robot();
	simulation.draw_gisement();
	if (togglelink){simulation.draw_liaison();}
    if (togglerange) {simulation.draw_rayon_comm();}
    graphic_draw_rectangle(frame.xMin, frame.xMax, frame.yMin, frame.yMax, dim_max);
    
	return true;
}

void MyArea::refresh()
{
	auto win = get_window();
    if(win)
    {
        Gdk::Rectangle r(0,0, get_allocation().get_width(), 
                              get_allocation().get_height());

        win->invalidate_rect(r,false);
    }
}

void MyArea::setFrame(Frame x)
{
	frame_ref = x;
	frame = frame_ref;
}

void MyArea::adjust_frame()
{
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();
	
	frame.width = width;
	frame.height = height;
	
	double new_aspect_ratio((double)width/height);
	if(new_aspect_ratio > frame_ref.asp){
		frame.yMax = frame_ref.yMax;
		frame.yMin = frame_ref.yMin;
		double delta(frame_ref.xMax - frame_ref.xMin);
		double mid((frame_ref.xMax + frame_ref.xMin)/2);
	    frame.xMax = mid + 0.5*(new_aspect_ratio/frame_ref.asp)*delta ;
	    frame.xMin = mid - 0.5*(new_aspect_ratio/frame_ref.asp)*delta ;		  	  
    }
    else
    {
	    frame.xMax = frame_ref.xMax ;
	    frame.xMin = frame_ref.xMin ;
	  	  
 	    double delta(frame_ref.yMax - frame_ref.yMin);
	    double mid((frame_ref.yMax + frame_ref.yMin)/2);
	    frame.yMax = mid + 0.5*(frame_ref.asp/new_aspect_ratio)*delta ;
	    frame.yMin = mid - 0.5*(frame_ref.asp/new_aspect_ratio)*delta ;		  	  
    }
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
	simulation.update_voisin();
	simulation.connexion();
	simulation.update_robot();
	m_area.refresh();
	cout << "mise à jour de la simulation " << ++count << endl;
}


void SimulationWindow::on_button_clicked_open()
{
	Gtk::FileChooserDialog dialog("Open File", Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_transient_for(*this);
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Open", Gtk::RESPONSE_OK);
	
	int result = dialog.run();
	
	switch(result)
	{
		case (Gtk::RESPONSE_OK):
			if (!(simulation.get_file_opened())){
				cout << "fichier ouvert :" << decode_filename(dialog.get_filename()) << endl;
				simulation.lecture(decode_filename(dialog.get_filename()));
				simulation.update_voisin();
				simulation.connexion();
				m_area.refresh();
			}else{
				cout << "un fichier est déjà ouvert" << endl;
			}
			break;
		
		case (Gtk::RESPONSE_CANCEL):
			cout << "cancel clicked" << endl;
			break;
		
		default :
			cout << "unexpected button clicked" << endl;
			break;
	}
}

void SimulationWindow::on_button_clicked_save()
{
	Gtk::FileChooserDialog dialog("Save File", Gtk::FILE_CHOOSER_ACTION_SAVE);
	dialog.set_transient_for(*this);
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Save", Gtk::RESPONSE_OK);
	
	int result = dialog.run();
	
	switch(result)
	{
		case (Gtk::RESPONSE_OK):
			cout << "sauvegarde : " << decode_filename(dialog.get_filename()) << endl;
			simulation.save(decode_filename(dialog.get_filename()));
			break;
		
		case (Gtk::RESPONSE_CANCEL):
			cout << "cancel clicked" << endl;
			break;
		
		default:
			cout << "unexpected button clicked" << endl;
			break;
	}
}

void SimulationWindow::on_button_clicked_togglelink()
{
	togglelink = !togglelink;
	m_area.refresh();
}
	
void SimulationWindow::on_button_clicked_togglerange()
{
	togglerange = !togglerange;
	m_area.refresh();
}


bool SimulationWindow::on_key_press_event(GdkEventKey * key_event)
{
	if(key_event->type == GDK_KEY_PRESS)
	{
		switch(gdk_keyval_to_unicode(key_event->keyval))
		{
			case ('s') :
				on_button_clicked_startstop();
				break;
			
			case ('1') :
				on_button_clicked_step();
				break;
		}
	}
}

bool SimulationWindow::on_idle()
{
	if (started) {
		cout << "mise à jour de la simulation " << ++count << endl;
	}
	return true;
}
	
string decode_filename(string name)
{
	string newname;
	for (int i(name.size()-1) ; i>=0; --i){
		if (name[i] == '/') {break;}
		newname = name[i] + newname;
	}
	return newname;
}


void SimulationWindow::creation_infos()
{
	for (int i(0) ; i < 3; ++i){
		numero_base.push_back(unique_ptr<Gtk::Box> (new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0)));
		numero_base[i]->pack_start(*(new Gtk::Label("oui")));
		numero_base[i]->pack_start(*(new Gtk::Label("oui")));
		numero_base[i]->pack_start(*(new Gtk::Label("oui")));
		numero_base[i]->pack_start(*(new Gtk::Label("oui")));
		numero_base[i]->pack_start(*(new Gtk::Label("oui")));
		numero_base[i]->pack_start(*(new Gtk::Label("oui")));
		numero_base[i]->pack_start(*(new Gtk::Label("oui")));
		m_box_bottom_info.pack_start(*(numero_base[i]));
	}
}
