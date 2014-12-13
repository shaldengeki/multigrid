//player.h
//player class definition

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <cmath>
#include <math.h>
#include "shot.hpp"
using namespace std;

class Player {
      
      public:
             Player();
			 int round(float a);
             double get_x();
             double get_y();
             double get_score();
             double get_shot_speed();
             double get_multiplier();
             int get_lives();
             int get_speed();
             int get_num_shots();
             int get_shot_timer();
             void set_x(double coord);
             void set_y(double coord);
             void set_speed(int new_speed);
             void set_lives(int new_lives);
             void set_score(double new_score);
             void set_multiplier(double new_multiplier);
             void set_num_shots(int new_num_shots);
             void shoot(int shoot_x, int shoot_y, int owner);
             void set_shot_timer(int new_shot_timer);
             void set_shot_speed(double new_shot_speed);
             void draw(float window_x, float window_y);
             void move(int move_x, int move_y);
      
      private:
              string name;
              int lives;
              int bombs;
              int speed;
              int shield;
              int num_shots;
              int shot_timer;
              double x;
              double y;
              double difficulty;
              double multiplier;
              double score;
              double fire_angle;
              double move_angle;
              double shot_speed;
              
};

#endif
