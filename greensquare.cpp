//greensquare.cpp
//green square enemy class implementation.

#include "greensquare.hpp"
using namespace std;

GreenSquare::GreenSquare(float start_x, float start_y, float player_x, float player_y) : Enemy(start_x, start_y) {
                         
     //set green square enemy constants.
     set_color(0.5647,1.0,0.2314);
     set_hp(1);
     set_speed(.5);
     set_spin(0.0);
     set_direction(90 - (atan2(player_y-start_y, player_x-start_x)*180.0/PI));
     set_score(10.0);
}

void GreenSquare::move(float player_x, float player_y, float move_speed) {     
     float x_incr, y_incr, new_direction, shot_to_square_angle, dodge_mult=1.0;
     float accel_x, accel_y, b_dx, b_dy, distd, distb, new_speed;
     extern vector<Shot> shot_list;
     vector<Shot>::iterator shot_iter;

     //in general, head toward player.     
     new_direction = 90 - (atan2(player_y-get_y(), player_x-get_x())*180.0/PI);

     x_incr = get_speed() * move_speed * cos((90-get_direction()) * PI / 180.0);
     y_incr = get_speed() * move_speed * sin((90-get_direction()) * PI / 180.0);

     b_dx = -x_incr;
     b_dy = -y_incr;
     distb = sqrt( (b_dx * b_dx) + (b_dy * b_dy) ) + 0.001;

     //check if a shot is headed our way.
     for (shot_iter = shot_list.begin(); shot_iter != shot_list.end(); shot_iter++)
     {
          //calculate distance to us in four cycles.
          accel_x = (*shot_iter).get_x() - get_x() + (4.0* x_incr);               
          accel_y = (*shot_iter).get_y() - get_y() + (4.0* y_incr);
          distd = sqrt( (accel_x * accel_x) + (accel_y * accel_y) ) + 0.001;
          if ( distd <= .7 )
          {               
               //dodge the shot.
               accel_x = -accel_x / distd * .05;
               accel_y = -accel_y / distd * .05;
               accel_x += b_dx / distb * .05;
               accel_y += b_dy / distb * .05;
               x_incr += accel_x;
               y_incr += accel_y;
          }          
     } 

     //update direction.
     set_direction(new_direction);

     if (fabs(get_x() + x_incr) >=  7.8)
          set_x(7.7 * fabs(get_x()) / get_x());
     else
          set_x(get_x() + x_incr);
     if (fabs(get_y() + y_incr) >= 7.0)
          set_y(6.9 * fabs(get_y()) / get_y());
     else
          set_y(get_y() + y_incr);
}

void GreenSquare::draw(float window_x, float window_y) {
    //draws green square.
    glPushMatrix();
    glColor3f(get_color_red(), get_color_green(), get_color_blue());
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
         //draw green square.
         glVertex3f(get_x()-window_x+0.15,get_y()-window_y+0.15,0.0f);   //top right.
         glVertex3f(get_x()-window_x-0.15,get_y()-window_y+0.15,0.0f);   //top left.
         glVertex3f(get_x()-window_x-0.15,get_y()-window_y-0.15,0.0f);   //bottom left.
         glVertex3f(get_x()-window_x+0.15,get_y()-window_y-0.15,0.0f);   //bototm right.
         glVertex3f(get_x()-window_x+0.15,get_y()-window_y+0.15,0.0f);   //top right.
         glVertex3f(get_x()-window_x,get_y()-window_y+0.15,0.0f);   //top middle.
         glVertex3f(get_x()-window_x-0.15,get_y()-window_y,0.0f);   //middle left.
         glVertex3f(get_x()-window_x,get_y()-window_y-0.15,0.0f);   //bottom middle.
         glVertex3f(get_x()-window_x+0.15,get_y()-window_y,0.0f);   //middle right.
         glVertex3f(get_x()-window_x,get_y()-window_y+0.15,0.0f);   //top middle.
    glEnd();
    glPopMatrix();
}
