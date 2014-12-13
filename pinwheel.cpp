//pinwheel.cpp
//pinwheel class implementation.

#include "pinwheel.h"
using namespace std;

Pinwheel::Pinwheel(float start_x, float start_y) : Enemy(start_x, start_y) {
                         
     //set pinwheel enemy constants.
     set_color(1.0f, .7255, 1.0f);
     set_hp(1);
     set_speed(.4);
     set_spin(0.3);
     set_direction();
     set_score(5.0);
}

void Pinwheel::set_direction() {
     //sets random direction.
/*     Object::set_vx(static_cast<float>(2*rand()/RAND_MAX-1));
     Object::set_vx(get_vx()/fabs(get_vx()));
     Object::set_vy(static_cast<float>(2*rand()/RAND_MAX-1));
     Object::set_vy(get_vy()/fabs(get_vy()));*/
     Object::set_direction( static_cast<float>(360.0 * rand()/RAND_MAX) );
}

void Pinwheel::move(float player_x, float player_y, float move_speed) {     
     
     //pinwheel bounces normally.
     float x_incr, y_incr;
/*     x_incr = get_speed() * move_speed * get_vx();
     y_incr = get_speed() * move_speed * get_vy();
     
     if ( fabs(get_x() + x_incr) <= 7.8) {
        Object::set_vx(get_vx()*-1);
     }   
     if ( fabs(get_y() + y_incr) <= 7.0) {
        Object::set_vy(get_vy()*-1);
     }     
     set_x(get_x() + x_incr);
     set_y(get_y() + y_incr);*/

     x_incr = get_speed() * move_speed * cos(get_direction() * PI / 180.0);
     y_incr = get_speed() * move_speed * sin(get_direction() * PI / 180.0);
     
     if ( fabs(get_x() + x_incr) <= 7.8 && fabs(get_y() + y_incr) <= 7.0)
     {
          //move enemy in this direction.
          set_x(get_x() + x_incr);
          set_y(get_y() + y_incr);
     }
     else
     {
          //reverse direction.
          Object::set_direction(get_direction()+(270*fabs(get_direction())/get_direction()));
          while (fabs(get_direction()) > 360)
                Object::set_direction(get_direction()-(fabs(get_direction())/get_direction()*360));
          if (fabs(get_x() + x_incr) > 7.8)
             set_x(get_x() + (-2*fabs(x_incr)*fabs(get_x())/get_x()));
             //set_x(7.78 * fabs(get_x())/get_x());
          else
             set_x(get_x() + (get_speed() * move_speed * cos(get_direction() * PI / 180.0)));
          if (fabs(get_y() + y_incr) > 7.0)
             set_y(get_y() + (-2*fabs(y_incr)*fabs(get_y())/get_y()));
             //set_y(6.98 * fabs(get_y())/get_y());
          else
             set_y(get_y() + (get_speed() * move_speed * sin(get_direction() * PI / 180.0)));
     }
}

void Pinwheel::draw(float window_x, float window_y) {
     float x_mid, x_left, x_right, y_mid, y_top, y_bottom;
     int i;
     double points[10][3];
     extern int ct;
    //draws pinwheel.
    glPushMatrix();
    glColor3f(get_color_red(), get_color_green(), get_color_blue());
    glLineWidth(1.5);

    //define the points of the pinwheel.
    //top left. x = -.15, y = +.15
    points[1][1] = (get_x()-window_x) + (-0.15*cos(ct/(8*3.1415926535878))) - (0.15*sin(ct/(8*3.1415926535878)));
    points[1][2] = (get_y()-window_y) + (-0.15*sin(ct/(8*3.1415926535878))) + (0.15*cos(ct/(8*3.1415926535878)));
    //top middle. x = 0, y = +.15
    points[2][1] = (get_x()-window_x) - (0.15*sin(ct/(8*3.1415926535878)));
    points[2][2] = (get_y()-window_y) + (0.15*cos(ct/(8*3.1415926535878)));
    //top right. x = +.15, y = +.15
    points[3][1] = (get_x()-window_x) + (0.15*cos(ct/(8*3.1415926535878))) - (0.15*sin(ct/(8*3.1415926535878)));
    points[3][2] = (get_y()-window_y) + (0.15*sin(ct/(8*3.1415926535878))) + (0.15*cos(ct/(8*3.1415926535878)));
    //middle left. x = -.15, y = 0
    points[4][1] = (get_x()-window_x) + (-0.15*cos(ct/(8*3.1415926535878)));
    points[4][2] = (get_y()-window_y) + (-0.15*sin(ct/(8*3.1415926535878)));
    //middle. x = 0, y = 0
    points[5][1] = (get_x()-window_x);
    points[5][2] = (get_y()-window_y);
    //middle right. x = +.15, y = 0
    points[6][1] = (get_x()-window_x) + (0.15*cos(ct/(8*3.1415926535878)));
    points[6][2] = (get_y()-window_y) + (0.15*sin(ct/(8*3.1415926535878)));
    //bottom left. x = -.15, y = -.15
    points[7][1] = (get_x()-window_x) + (-0.15*cos(ct/(8*3.1415926535878))) - (-0.15*sin(ct/(8*3.1415926535878)));
    points[7][2] = (get_y()-window_y) + (-0.15*sin(ct/(8*3.1415926535878))) + (-0.15*cos(ct/(8*3.1415926535878)));
    //bottom middle. x = 0, y = -.15
    points[8][1] = (get_x()-window_x) - (-0.15*sin(ct/(8*3.1415926535878)));
    points[8][2] = (get_y()-window_y) + (-0.15*cos(ct/(8*3.1415926535878)));
    //bottom right. x = +.15, y = -.15
    points[9][1] = (get_x()-window_x) + (0.15*cos(ct/(8*3.1415926535878))) - (-0.15*sin(ct/(8*3.1415926535878)));
    points[9][2] = (get_y()-window_y) + (0.15*sin(ct/(8*3.1415926535878))) + (-0.15*cos(ct/(8*3.1415926535878)));

    glBegin(GL_LINE_STRIP);
         //draw lines.
         glVertex3f(points[1][1],points[1][2],0.0f);
         glVertex3f(points[9][1],points[9][2],0.0f);
         glVertex3f(points[8][1],points[8][2],0.0f);
         glVertex3f(points[5][1],points[5][2],0.0f);
         glVertex3f(points[7][1],points[7][2],0.0f);
         glVertex3f(points[4][1],points[4][2],0.0f);
         glVertex3f(points[6][1],points[6][2],0.0f);
         glVertex3f(points[3][1],points[3][2],0.0f);
         glVertex3f(points[5][1],points[5][2],0.0f);
         glVertex3f(points[2][1],points[2][2],0.0f);
         glVertex3f(points[1][1],points[1][2],0.0f);
    glEnd();
    glPopMatrix();
    // WHY THE FUCK CAN'T I GET IT TO ROTATE set_spin(get_spin() + 0.002);
}
