//enemy.hpp
//enemy class definition

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "object.hpp"
#include <vector>
#include <cmath>
using namespace std;

class Enemy : public Object {

    public:
        Enemy(float start_x, float start_y);
        double get_score();
        void spawn(float player_x, float player_y);
        void move(float player_x, float player_y, float move_speed);
        void set_score(double new_score);

    private:
        int difficulty;
        int score;
};

#endif
