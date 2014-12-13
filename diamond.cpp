//diamond.cpp
//blue diamond enemy class implementation.

#include "diamond.hpp"
using namespace std;

Diamond::Diamond(float start_x, float start_y, float player_x, float player_y) : Enemy(start_x, start_y) {
                         
     //set diamond enemy constants.
     set_color(0.0,0.8314,0.8078);
     set_hp(1);
     set_speed(.5);
     set_spin(0.0);
     set_direction(90 - (atan2(player_y-start_y, player_x-start_x)*180.0/PI));
     set_score(8.0);
}

void Diamond::move(float player_x, float player_y, float move_speed) {     
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

void Diamond::draw(float window_x, float window_y) {
    //draws diamond.
    int points[5][3];
    extern int ct;
    //get points on diamond.
    //top middle. x = 0, y = +0.15
    points[1][1] = (get_x()-window_x);
    points[1][2] = (get_y()-window_y) + (0.15*cos(ct/(8*3.1415926535878)));
    //middle left. x = -.15, y = 0
    points[2][1] = (get_x()-window_x) + (-0.15*sin(ct/(8*3.1415926535878)));
    points[2][2] = (get_y()-window_y);
    //bottom middle. x = 0, y = -.15
    points[3][1] = (get_x()-window_x);
    points[3][2] = (get_y()-window_y) + (-0.15*cos(ct/(8*3.1415926535878)));
    //middle right. x = +.15, y = 0
    points[4][1] = (get_x()-window_x) + (0.15*sin(ct/(8*3.1415926535878)));
    points[4][2] = (get_y()-window_y);
        
    glPushMatrix();
    glColor3f(get_color_red(), get_color_green(), get_color_blue());
    glLineWidth(5.0);
    glBegin(GL_LINE_STRIP);
         //draw quad. 39x39px in a 64x64px square.
         glVertex3f(points[1][1],points[1][2],0.0f);   //top middle.
         glVertex3f(points[2][1],points[2][2],0.0f);   //middle left.
         glVertex3f(points[3][1],points[3][2],0.0f);   //bottom middle.
         glVertex3f(points[4][1],points[4][2],0.0f);   //middle right.
         glVertex3f(points[1][1],points[1][2],0.0f);   //top middle.
/*         
         glVertex3f(get_x()-window_x,get_y()-window_y+0.15,0.0f);   //top middle.
         glVertex3f(get_x()-window_x-0.15,get_y()-window_y,0.0f);   //middle left.
         glVertex3f(get_x()-window_x,get_y()-window_y-0.15,0.0f);   //bottom middle.
         glVertex3f(get_x()-window_x+0.15,get_y()-window_y,0.0f);   //middle right.
         glVertex3f(get_x()-window_x,get_y()-window_y+0.15,0.0f);   //top middle.*/
    glEnd();
    glPopMatrix();
}
