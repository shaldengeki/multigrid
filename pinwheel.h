//pinwheel.h
//pinwheel enemy class declaration

#ifndef PINWHEEL_H
#define PINWHEEL_H

#include "enemy.h"
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <math.h>
using namespace std;

class Pinwheel : public Enemy {
      public:
             Pinwheel(float start_x, float start_y);
             void draw(float window_x, float window_y);
             void set_direction();
             void move(float player_x, float player_y, float move_speed);
};

#endif
