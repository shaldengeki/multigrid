// game.hpp
// game class declaration.

#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include "window.hpp"
#include "object.hpp"
#include "player.hpp"

class Game {
  public:
    Game();

    unsigned int get_tick();
    Player get_current_player();

    std::vector<Player*> get_players();
    void add_player(Player* player);
    void remove_player(Player* player);

    std::vector<Object*> get_objects();
    void add_object(Object* object);
    void remove_object(Object* object);

    void update(bool keys[256]);
  private:
    unsigned int tick;
    Player* current_player;
    std::vector<Player*> players;
    std::vector<Object*> objects;
};

#endif