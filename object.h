//object.h
//object class declaration.

#ifndef OBJECT_H
#define OBJECT_H

#include <cmath>
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <math.h>
using namespace std;

const float PI = 4.0*atan(1.0);

class Object {
      public:
             Object(float start_x, float start_y);
             int get_hp();
             float get_x();
             float get_y();
             float get_vx();
             float get_vy();
             float get_speed();
             float get_direction();
             float get_color_red();
             float get_color_green();
             float get_color_blue();
             float get_spin();
             float get_distance(float object_x, float object_y);
             void set_hp(int new_hp);
             void set_x(float new_x);
             void set_y(float new_y);
             void set_vx(float new_vx);
             void set_vy(float new_vy);
             void set_speed(float new_speed);
             void set_direction(float new_direction);
             void set_color(float red, float green, float blue);
             void set_spin(float new_spin);
             void set_start();
             void move();
             void kill();
             bool on_screen(float window_x, float window_y);
             bool check_collisions(float player_x, float player_y);
                  
      private:
              float color[3];
              int hp;
              float x, y;
              float v_x, v_y; //can be either -1 or 1
              float speed;
              float direction;
              float spin;
};
#endif
