//diamond.h
//blue diamond enemy class declaration

#ifndef DIAMOND_H
#define DIAMOND_H

#include "enemy.hpp"
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <math.h>
using namespace std;

class Diamond : public Enemy {
      public:
             Diamond(float start_x, float start_y, float player_x, float player_y);
             void draw(float window_x, float window_y);
             void move(float player_x, float player_y, float move_speed);
};

#endif
