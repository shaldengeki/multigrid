//purplesquare.cpp
//purple square class implementation.

#include "purplesquare.hpp"
using namespace std;

PurpleSquare::PurpleSquare(float start_x, float start_y, float player_x, float player_y) : Enemy(start_x, start_y) {
                         
     //set purple square enemy constants.
     set_color(0.9922,0.7490,0.9451);
     set_hp(1);
     set_speed(.5);
     set_spin(0.0);
     set_direction(90 - (atan2(player_y-start_y, player_x-start_x)*180.0/PI));
     set_score(9.0);
}

void PurpleSquare::move(float player_x, float player_y, float move_speed) {     
     float x_incr, y_incr, new_direction;
     
     //update direction.
     new_direction = 90 - (atan2(player_y-get_y(), player_x-get_x())*180.0/PI);
     set_direction(new_direction);

     x_incr = (get_speed() * move_speed * cos((90-get_direction()) * PI / 180.0));
     y_incr = (get_speed() * move_speed * sin((90-get_direction()) * PI / 180.0));

     //move enemy in this direction.
     set_x(get_x() + x_incr);
     set_y(get_y() + y_incr);
}

void PurpleSquare::draw(float window_x, float window_y) {
    //draws purple square.
    glPushMatrix();
    glColor3f(get_color_red(), get_color_green(), get_color_blue());
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
         //draw purple square.
         glVertex3f(get_x()-window_x+0.15,get_y()-window_y+0.15,0.0f);   //top right.
         glVertex3f(get_x()-window_x-0.15,get_y()-window_y+0.15,0.0f);   //top left.
         glVertex3f(get_x()-window_x-0.15,get_y()-window_y-0.15,0.0f);   //bottom left.
         glVertex3f(get_x()-window_x+0.15,get_y()-window_y-0.15,0.0f);   //bototm right.
         glVertex3f(get_x()-window_x+0.15,get_y()-window_y+0.15,0.0f);   //top right.
         glVertex3f(get_x()-window_x,get_y()-window_y,0.0f);             //middle.
         glVertex3f(get_x()-window_x-0.15,get_y()-window_y+0.15,0.0f);   //top left.
         glVertex3f(get_x()-window_x-0.15,get_y()-window_y-0.15,0.0f);   //bottom left.
         glVertex3f(get_x()-window_x,get_y()-window_y,0.0f);             //middle.
         glVertex3f(get_x()-window_x+0.15,get_y()-window_y-0.15,0.0f);   //bototm right.
    glEnd();
    glPopMatrix();
}

void PurpleSquare::kill() {
     
     //spawn three smaller purple squares.
     extern vector<PurpleSquare2> purplesquare2_list;
     extern vector<PurpleSquare2>::iterator purplesquare2_iter;
     extern Player player1;
     
     PurpleSquare2 purple_square1(get_x(), get_y() + .1, player1.get_x(), player1.get_y());
     PurpleSquare2 purple_square2(get_x() - .1, get_y() - .1, player1.get_x(), player1.get_y());
     PurpleSquare2 purple_square3(get_x() + .1, get_y() - .1, player1.get_x(), player1.get_y());
     
     purplesquare2_list.push_back(purple_square1);
     purplesquare2_list.push_back(purple_square2);
     purplesquare2_list.push_back(purple_square3);
     
     purplesquare2_iter = purplesquare2_list.begin();
}
