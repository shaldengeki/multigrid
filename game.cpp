// game.cpp
// game class implementation.

#include <vector>

#include "window.hpp"
#include "object.hpp"
#include "player.hpp"

Game::Game() {
  tick = 0;
}

unsigned int Game::get_tick() {
  return tick;
}

Player Game::get_current_player() {
  return *current_player;
}

std::vector<Player*> Game::get_players() {
  return players;
}

void Game::add_player(Player* player) {
  players.push_back(player);
}

void Game::remove_player(Player* player) {
  auto find_itr = std::find(players.begin(), players.end(), player);
  if (find_itr != players.end()) {
    players.erase(find_itr);
  }
}

std::vector<Object*> Game::get_objects() {
  return objects;
}

void Game::add_object(Object* object) {
  objects.push_back(object);
}

void Game::remove_object(Object* object) {
  auto find_itr = std::find(objects.begin(), objects.end(), object);
  if (find_itr != objects.end()) {
    objects.erase(find_itr);
  }
}

void Game::update(bool keys[256]) {
  tick++;
  if (tick % 30 == 0) {
    SpawnPinwheels(1);
  }
  if (tick % 60 == 0) {
    SpawnDiamonds(1);       
  }
  if (tick % 90 == 0) {
    SpawnGreenSquares(1);       
  }
  if (tick % 120 == 0) {
    SpawnPurpleSquares(1);       
  }

  // monitor player1 movement.
  if (keys[VK_UP] || keys[VK_DOWN] || keys[VK_LEFT] || keys[VK_RIGHT]) {
    player1.move( static_cast<int>(keys[VK_RIGHT]) - static_cast<int>(keys[VK_LEFT]), static_cast<int>(keys[VK_UP]) - static_cast<int>(keys[VK_DOWN]) );
  }

  // monitor shot keys.
  if (keys['W'] || keys['A'] || keys['S'] || keys['D']) {
    player1.shoot( static_cast<int>(keys['D']) - static_cast<int>(keys['A']), static_cast<int>(keys['W']) - static_cast<int>(keys['S']), 1 );
  }

  // increment shot timer.
  player1.set_shot_timer(player1.get_shot_timer() - 1);

  // recenter window if necessary.
  if ((window.get_x() < player1.get_x() && player1.get_x() <= 5.1) || (window.get_x() > player1.get_x() && player1.get_x() >= -5.1)) {
    window.set_x(player1.get_x());
  }
  if ((window.get_y() < player1.get_y() && player1.get_y() <= 5.1) || (window.get_y() > player1.get_y() && player1.get_y() >= -5.1)) {
    window.set_y(player1.get_y());
  }

  // move pinwheel(s) and check for death.
  for (pinwheel_iter = pinwheel_list.begin(); pinwheel_iter != pinwheel_list.end(); pinwheel_iter++) {
    (*pinwheel_iter).move(player1.get_x(), player1.get_y(), move_speed);
    if ( (*pinwheel_iter).check_collisions(player1.get_x(), player1.get_y()) ) {
      KillPlayer();
      break;
    }
  }
  // move diamond(s) and check for death.
  for (diamond_iter = diamond_list.begin(); diamond_iter != diamond_list.end(); diamond_iter++) {
    (*diamond_iter).move(player1.get_x(), player1.get_y(), move_speed);
    if ( (*diamond_iter).check_collisions(player1.get_x(), player1.get_y()) ) {
      KillPlayer();
      break;
    }
  }
  // move green square(s) and check for death.
  for (greensquare_iter = greensquare_list.begin(); greensquare_iter != greensquare_list.end(); greensquare_iter++) {
    (*greensquare_iter).move(player1.get_x(), player1.get_y(), move_speed);
    if ( (*greensquare_iter).check_collisions(player1.get_x(), player1.get_y()) ) {
      KillPlayer();
      break;
    }
  }
  // move purple square(s) and check for death.
  for (purplesquare_iter = purplesquare_list.begin(); purplesquare_iter != purplesquare_list.end(); purplesquare_iter++) {
    (*purplesquare_iter).move(player1.get_x(), player1.get_y(), move_speed);
    if ( (*purplesquare_iter).check_collisions(player1.get_x(), player1.get_y()) ) {
      KillPlayer();
      break;
    }
  }
  // move small purple square(s) and check for death.
  for (purplesquare2_iter = purplesquare2_list.begin(); purplesquare2_iter != purplesquare2_list.end(); purplesquare2_iter++) {
    (*purplesquare2_iter).move(player1.get_x(), player1.get_y(), move_speed);
    if ( (*purplesquare2_iter).check_collisions(player1.get_x(), player1.get_y()) ) {
        KillPlayer();
        break;
     }
  }
  // move black hole(s) and check for death.
  for (blackhole_iter = blackhole_list.begin(); blackhole_iter != blackhole_list.end(); blackhole_iter++) {
    (*blackhole_iter).move(move_speed);
    if ( (*blackhole_iter).check_collisions(player1.get_x(), player1.get_y()) ) {
      KillPlayer();
      break;
    }
  }

  // move shot(s).
  for (shot_iter = shot_list.begin(); shot_iter != shot_list.end();) {
    (*shot_iter).move(move_speed);
    if ((*shot_iter).check_collisions()) {
      shot_iter = shot_list.erase(shot_iter);     // we kill this shot because it has collided with something.
    } else if(shot_iter != shot_list.end()) {
      shot_iter++;
    }
  }

}