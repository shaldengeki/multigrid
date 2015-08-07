//window.hpp
//window class declaration.

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <ctime>
#include <cstdlib>
#include <cmath>
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
using namespace std;

class Window {
  public:
    Window();
    float get_x();
    float get_y();
    void draw_grid();
    void draw_borders();
    void set_x(float new_x);
    void set_y(float new_y);
         
  private:
    float x, y;
};

#endif
