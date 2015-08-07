//purplesquare2.hpp
//smallpurple square class declaration.

#ifndef PURPLESQUARE2_HPP
#define PURPLESQUARE2_HPP

#include "enemy.hpp"
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <cmath>
using namespace std;

class PurpleSquare2 : public Enemy {
      public:
             PurpleSquare2(float start_x, float start_y, float player_x, float player_y);
             void draw(float window_x, float window_y);
             void move(float player_x, float player_y, float move_speed);
             void kill();
      private:
             int angle_move;
};

#endif
