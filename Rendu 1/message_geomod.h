#ifndef MESSAGE_GEOMOD_H_INCLUDED
#define MESSAGE_GEOMOD_H_INCLUDED

namespace message_geomod
{
	// appeler si le nombre d'arguments est incorrect
    void bad_argc();
    
    // scenario 1
    void print_max(double init_max, double max, double epsilon_zero);
    
    // scenario 2
    void print_point(double x_init, double y_init, double x_mod, double y_mod);
    
    // scenario 3
    void print_vect(double norm, double component_x, double component_y);
    
    // scenario 4
    void print_equal_point(bool is_equal, double p1x, double p1y,
                           double p2x, double p2y);

    // scenario 5                           
    void print_include_point(bool is_included, double px, double py,
                             double cx, double cy, double radius);
                             
	// scenario 6							
    void print_intersect(bool is_in_intersect, double cx1, double cy1, double r1,
                         double cx2, double cy2, double r2);
}

#endif // MESSAGE_GEOMOD_H_INCLUDED
