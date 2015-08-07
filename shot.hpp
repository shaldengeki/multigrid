//shot.hpp
//shot class declaration.

#ifndef SHOT_HPP
#define SHOT_HPP

#include "object.hpp"
#include "pinwheel.hpp"
#include "diamond.hpp"
#include "greensquare.hpp"
#include "purplesquare.hpp"
#include "purplesquare2.hpp"
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <math.h>
#include <vector>
using namespace std;

class Shot : public Object {
      public:
             Shot(float start_x, float start_y, float start_speed, float start_direction, int new_owner);
             int get_owner();
             void draw(float window_x, float window_y);
             void move(float move_speed);
             void set_owner(int new_owner);
             bool check_black_hole();
             bool check_collisions();
      private:
             int owner;
};

#endif
