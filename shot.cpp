//shot.cpp
//shot class implementation.

#include "shot.hpp"
using namespace std;

Shot::Shot (float start_x, float start_y, float start_speed, float start_direction, int new_owner) : Object(start_x, start_y) {
     //shot constructor.
     set_color(.988,.988,.745);
     //shots go faster when moving towards an enemy, and slower when moving away.
     set_speed(2 * start_speed);
     set_direction(start_direction);
     set_owner(new_owner);
}
int Shot::get_owner() {
    return owner;   
}
void Shot::draw(float window_x, float window_y) {
    //draws shot.
    glPushMatrix();
    glColor3f(get_color_red(), get_color_green(), get_color_blue());
    glLineWidth(.6);
    
    glBegin(GL_LINE_STRIP);
         //draw a triangle. 24 high, 8 wide in a 32x32px square. .15fx.15f
         glVertex3f(get_x()-window_x, get_y()-window_y+.05625, 0.0f); //top.
         glVertex3f(get_x()-window_x-.01875, get_y()-window_y-.05625, 0.0f); //left.
         glVertex3f(get_x()-window_x+.01875, get_y()-window_y-.05625, 0.0f); //right.    
         glVertex3f(get_x()-window_x, get_y()-window_y+.05625, 0.0f); //top.         
         glEnd();
    glPopMatrix();
}
void Shot::set_owner(int new_owner) {
     owner = new_owner;    
}
bool Shot::check_black_hole() {
     return false;
}
bool Shot::check_collisions() {
     if (fabs(get_x()) > 7.7 || fabs(get_y()) > 7)
        return true;
     
     extern vector<Pinwheel> pinwheel_list;
     extern vector<Pinwheel>::iterator pinwheel_iter;
     extern vector<Diamond> diamond_list;
     extern vector<Diamond>::iterator diamond_iter;     
     extern vector<GreenSquare> greensquare_list;
     extern vector<GreenSquare>::iterator greensquare_iter;     
     extern vector<PurpleSquare> purplesquare_list;
     extern vector<PurpleSquare>::iterator purplesquare_iter;     
     extern vector<PurpleSquare2> purplesquare2_list;
     extern vector<PurpleSquare2>::iterator purplesquare2_iter;    
     extern Player player1;
     extern Player player2;
          
     for (pinwheel_iter = pinwheel_list.begin(); pinwheel_iter != pinwheel_list.end();) {
          if ( fabs(get_x() - (*pinwheel_iter).get_x()) <= .30 && fabs(get_y() - (*pinwheel_iter).get_y()) <= .30) {
               //add score.
               if (owner == 1) {
                  player1.set_score(player1.get_score() + (*pinwheel_iter).get_score());
                  player1.set_multiplier(player1.get_multiplier() + (*pinwheel_iter).get_score()/10.0);
               } else {                    
                  player2.set_score(player2.get_score() + (*pinwheel_iter).get_score());      
                  player2.set_multiplier(player2.get_multiplier() + (*pinwheel_iter).get_score()/10.0);
               }
               //kill pinwheel.
               (*pinwheel_iter).kill();
               pinwheel_iter = pinwheel_list.erase(pinwheel_iter);
               return true;
          } else if (pinwheel_iter != pinwheel_list.end()) {
			  pinwheel_iter++;
		  }
     }
     for (diamond_iter = diamond_list.begin(); diamond_iter != diamond_list.end();) {
          if ( fabs(get_x() - (*diamond_iter).get_x()) <= .30 && fabs(get_y() - (*diamond_iter).get_y()) <= .30) {
               //add score.
               if (owner == 1) {
                  player1.set_score(player1.get_score() + (*diamond_iter).get_score());      
                  player1.set_multiplier(player1.get_multiplier() + (*diamond_iter).get_score()/10.0);
               } else {                    
                  player2.set_score(player2.get_score() + (*diamond_iter).get_score());      
                  player2.set_multiplier(player2.get_multiplier() + (*diamond_iter).get_score()/10.0);
               }
               //kill diamond.
               (*diamond_iter).kill();
               diamond_iter = diamond_list.erase(diamond_iter);
               return true;
          } else if (diamond_iter != diamond_list.end()) {
			  diamond_iter++;
		  }
     }
     for (greensquare_iter = greensquare_list.begin(); greensquare_iter != greensquare_list.end();) {
          if ( fabs(get_x() - (*greensquare_iter).get_x()) <= .30 && fabs(get_y() - (*greensquare_iter).get_y()) <= .30) {
               //add score.
               if (owner == 1) {
                  player1.set_score(player1.get_score() + (*greensquare_iter).get_score());      
                  player1.set_multiplier(player1.get_multiplier() + (*greensquare_iter).get_score()/10.0);
               } else {                    
                  player2.set_score(player2.get_score() + (*greensquare_iter).get_score());      
                  player2.set_multiplier(player2.get_multiplier() + (*greensquare_iter).get_score()/10.0);
               }
               //kill green square.
               (*greensquare_iter).kill();
               greensquare_iter = greensquare_list.erase(greensquare_iter);
               return true;
          } else if (greensquare_iter != greensquare_list.end()) {
			  greensquare_iter++;
		  }
     }
     for (purplesquare_iter = purplesquare_list.begin(); purplesquare_iter != purplesquare_list.end();) {
          if ( fabs(get_x() - (*purplesquare_iter).get_x()) <= .30 && fabs(get_y() - (*purplesquare_iter).get_y()) <= .30) {
               //add score.
               if (owner == 1) {
                  player1.set_score(player1.get_score() + (*purplesquare_iter).get_score());      
                  player1.set_multiplier(player1.get_multiplier() + (*purplesquare_iter).get_score()/10.0);
               } else {                    
                  player2.set_score(player2.get_score() + (*purplesquare_iter).get_score());      
                  player2.set_multiplier(player2.get_multiplier() + (*purplesquare_iter).get_score()/10.0);
               }
               //kill purple square.
               (*purplesquare_iter).kill();
               purplesquare_iter = purplesquare_list.erase(purplesquare_iter);
               return true;
          } else if (purplesquare_iter != purplesquare_list.end()) {
			  purplesquare_iter++;
		  }
     }
     for (purplesquare2_iter = purplesquare2_list.begin(); purplesquare2_iter != purplesquare2_list.end();) {
          if ( fabs(get_x() - (*purplesquare2_iter).get_x()) <= .30 && fabs(get_y() - (*purplesquare2_iter).get_y()) <= .30) {
               //add score.
               if (owner == 1) {
                  player1.set_score(player1.get_score() + (*purplesquare2_iter).get_score());      
                  player1.set_multiplier(player1.get_multiplier() + (*purplesquare2_iter).get_score()/10.0);
               } else {                    
                  player2.set_score(player2.get_score() + (*purplesquare2_iter).get_score());      
                  player2.set_multiplier(player2.get_multiplier() + (*purplesquare2_iter).get_score()/10.0);
               }
               //kill purple square.
               (*purplesquare2_iter).kill();
               purplesquare2_iter = purplesquare2_list.erase(purplesquare2_iter);
               return true;
          } else if (purplesquare2_iter != purplesquare2_list.end()) {
			  purplesquare2_iter++;
		  }
     }
     
     return false;
}
void Shot::move(float move_speed) {
     extern vector<Shot> shot_list;
     extern vector<Shot>::iterator shot_iter;
     float x_incr, y_incr;

     x_incr = (get_speed() * move_speed * cos((90-get_direction()) * PI / 180.0));
     y_incr = (get_speed() * move_speed * sin((90-get_direction()) * PI / 180.0));
     
     if (check_black_hole()) {

     }
     //move shot.
     set_x(get_x() + x_incr);
     set_y(get_y() + y_incr);
}
