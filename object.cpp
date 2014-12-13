//object.cpp
//object class implementation.

#include "object.hpp"
using namespace std;

Object::Object(float start_x, float start_y) {
     //object constructor.   
     x = start_x;
     y = start_y;           
}

int Object::get_hp() {
    return hp;
}
float Object::get_x() {
    return x;
}
float Object::get_y() {
     return y;
}
float Object::get_vx() {
     return v_x;
}
float Object::get_vy() {
     return v_y;
}
float Object::get_speed() {
     return speed;
}
float Object::get_direction() {
      return direction;
}
float Object::get_color_red() {
      return color[0];
}
float Object::get_color_green() {
      return color[1];
}
float Object::get_color_blue() {
      return color[2];
}
float Object::get_spin() {
      return spin;
}
float Object::get_distance(float object_x, float object_y) {
      return pow(pow(object_x - x, 2) + pow(object_y-y,2),1/2);      
}
void Object::set_hp(int new_hp) {
     hp = new_hp;
}
void Object::set_x(float new_x) {
     x = new_x;
}
void Object::set_y(float new_y) {
     y = new_y;
}
void Object::set_vx(float new_vx) {
     v_x = new_vx;
}
void Object::set_vy(float new_vy) {
     v_y = new_vy;
}
void Object::set_speed(float new_speed) {
     speed = new_speed;
}
void Object::set_direction(float new_direction) {
     direction = new_direction;
}
void Object::set_color(float red, float green, float blue) {
     color[0] = red;
     color[1] = green;
     color[2] = blue;     
}
void Object::set_spin(float new_spin) {
     spin = new_spin;
}
void Object::set_start() {
     //sets a random location for the object to spawn in.
     x = 15.6 * rand()/RAND_MAX - 7.8;
     y = 14.0 * rand()/RAND_MAX - 7.0;
}
void Object::move() {
     //move object in the current direction.
/*     x += v_x;
     y += v_y;*/
     x = speed * cos(direction * PI / 180);
     y = speed * sin(direction * PI / 180);
}
void Object::kill() {
     //kill function for objects.
     
}
bool Object::on_screen(float window_x, float window_y) {
     if ( fabs(window_x - x) < 10 && fabs(window_y - y) < 10)
        return true;
     else
         return false;
}
bool Object::check_collisions(float player_x, float player_y) {
     if (fabs(get_x() - player_x) <= .30 && fabs(get_y() - player_y) <= .30)
          return true;
     else
          return false;
}
