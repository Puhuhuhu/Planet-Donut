#ifndef GUI_H
#define GUI_H
#include <gtkmm.h>
#include "simulation.h"
#include "geomod.h"
#include <string>


class MyArea : public Gtk::DrawingArea
{
	public :
		MyArea();
		virtual ~MyArea();
	
	protected :
		bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

};



class SimulationWindow : public Gtk::Window
{
	public:
		SimulationWindow(int argc, char *argv[]);
		virtual ~SimulationWindow();
		
	protected:
		Gtk::Box m_box, m_box_top, m_box_bottom, m_box_bottom_label, m_box_bottom_info, m_box_top_left, m_box_top_right, m_box_frame_general, m_box_frame_toggledisplay;
		Gtk::Button m_button_startstop, m_button_step, m_button_exit, m_button_open, m_button_save, m_button_togglelink, m_button_togglerange;
		Gtk::Label m_label_Uid, m_label_nbP, m_label_nbF, m_label_nbT, m_label_nbC, m_label_amountresource, m_label_missioncompleteness;
		Gtk::Frame m_frame_general, m_frame_toggledisplay, m_frame_Uid, m_frame_nbP, m_frame_nbF, m_frame_nbT, m_frame_nbC, m_frame_ammountresource, m_frame_missioncompleteness;
		MyArea m_area;
		
		void on_button_clicked_startstop();
		void on_button_clicked_step();
		void on_button_clicked_exit();
		void on_button_clicked_open();
		void on_button_clicked_save();
		void on_button_clicked_togglelink();
		void on_button_clicked_togglerange();
		bool on_idle();
		bool on_key_press_event(GdkEventKey * key_event);
		
	private:
		bool started;
		unsigned count;
};

std::string decode_filename(std::string name);

#endif
