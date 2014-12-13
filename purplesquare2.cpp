//purplesquare2.cpp
//small purple square class implementation.

#include "purplesquare2.h"
using namespace std;

PurpleSquare2::PurpleSquare2(float start_x, float start_y, float player_x, float player_y) : Enemy(start_x, start_y) {
                         
     //set purple square enemy constants.
     set_color(0.9922,0.7490,0.9451);
     set_hp(1);
     set_speed(.6);
     set_spin(0.0);
     set_direction(90 - (atan2(player_y-start_y, player_x-start_x)*180.0/PI));
     set_score(2.0);
}

void PurpleSquare2::move(float player_x, float player_y, float move_speed) {     
     float x_incr, y_incr, new_direction;
     
     angle_move++;
     
     //update direction.
     new_direction = 90 - (atan2(static_cast<double>(player_y-get_y()), static_cast<double>(player_x-get_x())*180.0/PI));
     set_direction(new_direction);

     x_incr = (get_speed() * move_speed * cos(static_cast<double>(90-get_direction()) * PI / 180.0));
     y_incr = (get_speed() * move_speed * sin(static_cast<double>(90-get_direction()) * PI / 180.0));

     x_incr += sin(static_cast<double>(angle_move) / 10) / 20;
     y_incr += cos(static_cast<double>(angle_move) / 10) / 20;

     //move enemy in this direction.
     set_x(get_x() + x_incr);
     set_y(get_y() + y_incr);
}

void PurpleSquare2::draw(float window_x, float window_y) {
    //draws purple square.
    glPushMatrix();
    glColor3f(get_color_red(), get_color_green(), get_color_blue());
    glLineWidth(1.0);
    glBegin(GL_LINE_STRIP);
         //draw purple square.
         glVertex3f(get_x()-window_x+0.075,get_y()-window_y+0.075,0.0f);   //top right.
         glVertex3f(get_x()-window_x-0.075,get_y()-window_y+0.075,0.0f);   //top left.
         glVertex3f(get_x()-window_x-0.075,get_y()-window_y-0.075,0.0f);   //bottom left.
         glVertex3f(get_x()-window_x+0.075,get_y()-window_y-0.075,0.0f);   //bototm right.
         glVertex3f(get_x()-window_x+0.075,get_y()-window_y+0.075,0.0f);   //top right.
         glVertex3f(get_x()-window_x,get_y()-window_y,0.0f);             //middle.
         glVertex3f(get_x()-window_x-0.075,get_y()-window_y+0.075,0.0f);   //top left.
         glVertex3f(get_x()-window_x-0.075,get_y()-window_y-0.075,0.0f);   //bottom left.
         glVertex3f(get_x()-window_x,get_y()-window_y,0.0f);             //middle.
         glVertex3f(get_x()-window_x+0.075,get_y()-window_y-0.075,0.0f);   //bototm right.
    glEnd();
    glPopMatrix();
}

void PurpleSquare2::kill() {
}
