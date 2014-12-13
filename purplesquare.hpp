//purplesquare.h
//purple square class declaration.

#ifndef PURPLESQUARE_H
#define PURPLESQUARE_H

#include "enemy.hpp"
#include "purplesquare2.hpp"
#include "player.hpp"
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <math.h>
using namespace std;

class PurpleSquare : public Enemy {
      public:
             PurpleSquare(float start_x, float start_y, float player_x, float player_y);
             void draw(float window_x, float window_y);
             void move(float player_x, float player_y, float move_speed);
             void kill();
};

#endif
