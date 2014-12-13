//enemy.cpp
//enemy class implementation.

#include "enemy.h"
using namespace std;

Enemy::Enemy(float start_x, float start_y) : Object(start_x, start_y) {
     //enemy constructor.
}

void Enemy::spawn(float player_x, float player_y) {
     //spawn enemy in safe, random place
     do {
        set_start();
     } while(get_distance(player_x, player_y) < 1);
}

double Enemy::get_score() {
       return score;
}

void Enemy::set_score(double new_score) {
     score = static_cast<int>(new_score);    
}

void Enemy::move(float player_x, float player_y, float move_speed) {
     //find direction to move toward player.
     set_direction( (atan2( player_y - get_y(), player_x - get_x()) * 180.0 / PI) );
     
     //move enemy in this direction.
     set_x(get_x() + (get_speed() * move_speed * cos(get_direction() * PI / 180.0)));
     set_y(get_y() + (get_speed() * move_speed * sin(get_direction() * PI / 180.0)));
}
/*
void Enemy::check_black_hole() {
     extern vector<BlackHole> blackhole_list;
     extern vector<BlackHole>::iterator blackhole_iter;

     //check surrounding space for black holes.
     for (blackhole_iter = blackhole_list.begin(); blackhole_iter != blackhole_list.end(); blackhole_iter++) {
          if ( sqrt( pow(get_x() - (*blackhole_iter).get_x(), 2) + pow(get_y() - (*blackhole_iter).get_y(), 2) ) < (*blackhole_iter).get_radius()) {
               //move enemy closer to black hole.
          }
     }
}*/
