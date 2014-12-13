//implementation for player class.

#include "player.hpp"
using namespace std;

Player::Player() {
     //constructor for player. called upon game start.
     lives = 3;
     bombs = 3;
     x = 0;
     y = 0;
     speed = 0;
     score = 0;
     fire_angle = 0;
     move_angle = 0;
     shield = 0;
     num_shots = 4;
     shot_timer = 0;
     shot_speed = 1;
}
int Player::round(float a) {
    return int(a + 0.5);
}
double Player::get_x() {
       return x;       
}
double Player::get_y() {
       return y;       
}
double Player::get_score() {
       return score;      
}
double Player::get_multiplier() {
       return multiplier;      
}
int Player::get_lives() {
    return lives;
}
int Player::get_speed() {
    return speed;
}
int Player::get_num_shots() {
    return num_shots;
}
int Player::get_shot_timer() {
    return shot_timer;
}
double Player::get_shot_speed() {
    return shot_speed;
}
void Player::set_x(double coord) {
       x = coord;
}
void Player::set_y(double coord) {
       y = coord;
}
void Player::set_lives(int new_lives) {
    lives = new_lives;
}
void Player::set_score(double new_score) {
    score = new_score;    
}
void Player::set_multiplier(double new_multiplier) {
     multiplier = new_multiplier;    
}
void Player::set_speed(int new_speed) {
     speed = new_speed;
}
void Player::set_num_shots(int new_num_shots) {
     num_shots = new_num_shots;
}
void Player::set_shot_timer(int new_shot_timer) {
     shot_timer = new_shot_timer;
}
void Player::set_shot_speed(double new_shot_speed) {
     shot_speed = new_shot_speed;
}
void Player::draw(float window_x, float window_y) {
    //draws player.
/*    float points[8][2];
    //define the points of the player ship.
    //top middle. x = 0, y = +0.157
    points[1][1] = (get_x()-window_x) - (0.157*sin(move_angle*3.1415926535878/180));
    points[1][2] = (get_y()-window_y) + (0.157*cos(move_angle*3.1415926535878/180));
    //middle right. x = +0.15, y = +0.065
    points[2][1] = (get_x()-window_x) + (0.15*cos(move_angle*3.1415926535878/180)) - (0.065*sin(move_angle*3.1415926535878/180));
    points[2][2] = (get_y()-window_y) + (0.15*sin(move_angle*3.1415926535878/180)) + (0.065*cos(move_angle*3.1415926535878/180));
    //bottom right. x = +0.063, y = -0.125
    points[3][1] = (get_x()-window_x) + (0.063*cos(move_angle*3.1415926535878/180)) - (-0.125*sin(move_angle*3.1415926535878/180));
    points[3][2] = (get_y()-window_y) + (0.063*sin(move_angle*3.1415926535878/180)) + (-0.125*cos(move_angle*3.1415926535878/180));
    //lower-middle right. x = +0.063, y = 0
    points[4][1] = (get_x()-window_x) + (0.063*cos(move_angle*3.1415926535878/180));
    points[4][2] = (get_y()-window_y) + (0.063*sin(move_angle*3.1415926535878/180));
    //middle. x = 0, y = +0.033
    points[5][1] = (get_x()-window_x) - (0.033*sin(move_angle*3.1415926535878/180));
    points[5][2] = (get_y()-window_y) + (0.033*cos(move_angle*3.1415926535878/180));
    //lower-middle left. x = -0.063, y = 0
    points[6][1] = (get_x()-window_x) + (-0.063*cos(move_angle*3.1415926535878/180));
    points[6][2] = (get_y()-window_y) + (-0.063*sin(move_angle*3.1415926535878/180));
    //bottom left. x = -0.063, y = -0.125
    points[7][1] = (get_x()-window_x) + (-0.063*cos(move_angle*3.1415926535878/180)) - (-0.125*sin(move_angle*3.1415926535878/180));
    points[7][2] = (get_y()-window_y) + (-0.063*sin(move_angle*3.1415926535878/180)) + (-0.125*cos(move_angle*3.1415926535878/180));
    //middle left. x = -0.15, y = +0.065
    points[8][1] = (get_x()-window_x) + (-0.15*cos(move_angle*3.1415926535878/180)) - (0.065*sin(move_angle*3.1415926535878/180));
    points[8][2] = (get_y()-window_y) + (-0.15*sin(move_angle*3.1415926535878/180)) + (0.065*cos(move_angle*3.1415926535878/180));
*/
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-6.0f);
    glColor3f(1.0f,1.0f,1.0f);
    glLineWidth(1.5);
    glBegin(GL_LINE_STRIP);
         //draw lines.
/*         glVertex3f(points[1][1],points[1][2],0.0f);          
         glVertex3f(points[2][1],points[2][2],0.0f);          
         glVertex3f(points[3][1],points[3][2],0.0f);          
         glVertex3f(points[4][1],points[4][2],0.0f);          
         glVertex3f(points[5][1],points[5][2],0.0f);          
         glVertex3f(points[6][1],points[6][2],0.0f);          
         glVertex3f(points[7][1],points[7][2],0.0f);          
         glVertex3f(points[8][1],points[8][2],0.0f);          
         glVertex3f(points[1][1],points[1][2],0.0f);          */
         glVertex3f(get_x()-window_x,get_y()-window_y+0.157,0.0f);          //top point.
         glVertex3f(get_x()-window_x+0.15,get_y()-window_y+.065,0.0f);     //d+r
         glVertex3f(get_x()-window_x+0.063,get_y()-window_y-0.125,0.0f);     //d+l
         glVertex3f(get_x()-window_x+0.063,get_y()-window_y,0.0f);          //up
         glVertex3f(get_x()-window_x,get_y()-window_y+0.033,0.0f);          //u+l
         glVertex3f(get_x()-window_x-0.063,get_y()-window_y,0.0f);          //d+l
         glVertex3f(get_x()-window_x-0.063,get_y()-window_y-0.125,0.0f);    //down
         glVertex3f(get_x()-window_x-0.15,get_y()-window_y+0.065,0.0f);    //u+l
         glVertex3f(get_x()-window_x,get_y()-window_y+0.157,0.0f);          //top point.
    glEnd();
}
void Player::shoot(int shoot_x, int shoot_y, int owner) {
     extern vector<Shot> shot_list;
     float shot_angle_start, shot_angle_incr, shot_angle;
     int shot_num;
     Shot shot(0.0, 0.0, 0.0, 0.0, owner);

     //delay shots based on how many shots the player fires.
     if (get_shot_timer() < 0)
     {
          set_shot_timer(static_cast<int>(6 + floor(static_cast<double>(get_num_shots()) / 2)));
          if (get_num_shots() == 2)
          {
               shot_angle_start = 3;
               shot_angle_incr = -6;
          }
          if (get_num_shots() == 3)
          {
               shot_angle_start = 5;
               shot_angle_incr = -6;
          }
          if (get_num_shots() == 4)
          {
               shot_angle_start = 6;
               shot_angle_incr = -6;
          }
          for (shot_num = 0; shot_num < get_num_shots(); shot_num++)
          {
               shot_angle = shot_angle_start + (shot_angle_incr * shot_num) + 90 - (atan2(static_cast<double>(shoot_y), static_cast<double>(shoot_x)) * 180 / PI);
               shot = Shot(get_x(), get_y(), shot_speed, shot_angle, owner);
               shot_list.push_back( shot );
          }
     }                    
}
void Player::move(int move_x, int move_y) {
     float hyp_mult = round(sqrt(2.0)* 5)/10;
     extern double move_speed;

     if (move_x != 0 && fabs(get_x() + (move_x * move_speed * hyp_mult)) < 7.7)
          set_x(get_x() + (move_x * move_speed * hyp_mult));
     if (move_y != 0 && fabs(get_y() + (move_y * move_speed * hyp_mult)) < 7.0)        
          set_y(get_y() + (move_y * move_speed * hyp_mult));
     if (move_x != 0 || move_y != 0)
          set_speed(1);
     else
          set_speed(0);
}