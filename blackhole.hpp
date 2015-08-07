//blackhole.hpp
//black hole class declaration.

#ifndef BLACKHOLE_HPP
#define BLACKHOLE_HPP

#include "enemy.hpp"
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <cmath>
using namespace std;

class BlackHole : public Enemy {
  public:
    BlackHole(float start_x, float start_y, float start_speed, float start_direction);
    float get_radius();
    float get_active();
    int get_absorb_count();
    void set_active(int new_active_state);
    void set_absorb_count(int new_absorb_count);
    void check_black_hole();
    void draw(float window_x, float window_y);
    void grow(float enemy_score);
    void move(float move_speed);
    void kill();
  private:
    int active;
    int absorb_count;
};

#endif
