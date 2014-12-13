//blackhole.cpp
//black hole class implementation.

#include "blackhole.h"
using namespace std;

BlackHole::BlackHole(float start_x, float start_y, float start_speed, float start_direction) : Enemy(start_x, start_y) {
                         
     //set blackhole constants.
     set_color(0.0, 0.0, 0.0);
     set_hp(10);
     set_speed(start_speed);
     set_spin(0.0);
     set_direction(start_direction);
     set_active(0);
}

float BlackHole::get_radius() {
      //returns radius of black hole.
      //is dependent on hp which goes from 0 to 60
      //radius goes from .004 to 1.004
      return (get_hp() + .25)/60;
}

float BlackHole::get_active() {
      return active;
}

int BlackHole::get_absorb_count() {
    return absorb_count;
}

void BlackHole::set_active(int new_active_state) {
     active = new_active_state;
}

void BlackHole::set_absorb_count(int new_absorb_count) {
     absorb_count = new_absorb_count;
}

void BlackHole::move(float move_speed) {     
     float x_incr, y_incr;
     
     check_black_hole();
     
     x_incr = (get_speed() * move_speed * cos((90-get_direction()) * PI / 180.0));
     y_incr = (get_speed() * move_speed * sin((90-get_direction()) * PI / 180.0));
     
     //move enemy in this direction.
     set_x(get_x() + x_incr);
     set_y(get_y() + y_incr);
}

void BlackHole::check_black_hole() {
}

void BlackHole::draw(float window_x, float window_y) {
    //draws black hole.
    glPushMatrix();
    glColor3f(get_color_red(), get_color_green(), get_color_blue());
    glLineWidth(1.0);
   glBegin(GL_LINE_LOOP);
        //draw circle.
        for (int i=0; i < 360; i++)
        {
             float degInRad = i*PI / 180;
             glVertex2f(cos(degInRad)*get_radius(),sin(degInRad)*get_radius());
        }
    glEnd();
    glPopMatrix();
}

void BlackHole::grow(float enemy_score) {
     //increases radius of black hole due to swallowed enemy.
     //radius depends only on hp so we increase hp and absorb count.
     set_hp(get_hp() + 1);
     set_absorb_count(get_absorb_count() + 1);
}

void BlackHole::kill() {
}
