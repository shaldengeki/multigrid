//greensquare.hpp
//green square class declaration.

#ifndef GREENSQUARE_HPP
#define GREENSQUARE_HPP

#include "enemy.hpp"
#include "shot.hpp"
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <math.h>
using namespace std;

class GreenSquare : public Enemy {
      public:
             GreenSquare(float start_x, float start_y, float player_x, float player_y);
             void draw(float window_x, float window_y);
             void move(float player_x, float player_y, float move_speed);
};

#endif
