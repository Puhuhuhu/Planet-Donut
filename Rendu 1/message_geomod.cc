#include "message_geomod.h"

#include <iostream>
#include <string>

using namespace std;

void message_geomod::bad_argc()
{
    cout << "Bad argc, please check handout" << endl;
}

void message_geomod::print_max(double init_max, double max, double epsilon_zero)
{
    cout << "init_max: " << init_max << " max: " << max << " epsilon_zero: "
         << epsilon_zero << endl;
}

void message_geomod::print_point(double x_init, double y_init, double x_mod,
                                 double y_mod)
{
    cout << "x_init: " << x_init << " y_init: " << y_init
         << " x_mod: " << x_mod << " y_mod: " << y_mod << endl;
}

void message_geomod::print_vect(double norm, double component_x, double component_y)   
{
    cout << "vec norm: " << norm
         << " component_x: " << component_x << " component_y: " << component_y << endl;
}

void message_geomod::print_equal_point(bool is_equal, double p1x, double p1y,
                                       double p2x, double p2y)
{
    if(is_equal)
        cout << "Point are equal" << endl;
    else
        cout << "Point are NOT equal" << endl;

    cout << "p1x: " << p1x << " p1y: " << p1y
         << " p2x: " << p2x << " p2y: " << p2y << endl;
}

void message_geomod::print_include_point(bool is_included, double px, double py,
                                         double cx, double cy, double radius)
{
    if(is_included)
        cout << "The point is included in the circle" << endl;
    else
        cout << "The point is NOT included in the circle" << endl;

    cout << "px: " << px << " py: " << py << " cx: " << cx << " cy: " << cy
         << " radius: " << radius << endl;
}

void message_geomod::print_intersect(bool is_in_intersect,
                                     double cx1, double cy1, double r1,
                                     double cx2, double cy2, double r2)
{
    if(is_in_intersect)
        cout << "The two circles are in intersection" << endl;
    else
        cout << "The two circles are NOT in intersection" << endl;

    cout << "cx1: " << cx1 << " cy1: " << cy1 << " radius1: " << r1
         << " cx2: " << cx2 << " cy2: " << cy2 << " radius2: " << r2 << endl;
}
