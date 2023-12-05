#include <vector>
#include <memory>
#include <iostream>
#include "entity.hpp"
#include "blocks.hpp"
using namespace std;


class Level {
 private:
  vector<vector<bool>> taken;
  vector<unique_ptr<Block>>
      blocks;  // TODO: Implement as grid for constant time complexity when
               // searching for collisions
  vector<unique_ptr<Entity>> entities;
  unique_ptr<Player> player;
  int w;
  int h;

 public:
  Level(int w, int h){
    taken = vector<vector<bool>> (w, vector<bool>(h));
    this->w = w;
    this->h = h;
  }

  void add_block(Block *block) {
    blocks.push_back(unique_ptr<Block>(block));

    for(int i = block->getX(); i < block->getX() + 16; i++){
      for(int j = block->getY(); j < block->getY() + 16; j++){
        if(i < w && i >= 0 && j < h && j >= 0 ) taken[i][j] = 1;
      }
    }
  }

  void add_entity(Entity *entity) {
    entities.push_back(unique_ptr<Entity>(entity));
  }

  bool check_left() {
    int x = player->get_right();
    int y1 = player->get_up();
    int y2 = player->get_bottom();

    if(x == 0) return true;

    return taken[x + 1][y1] || taken[x + 1][y2];
  }

  bool check_right() {
    int x = player->get_left();
    int y1 = player->get_up();
    int y2 = player->get_bottom();

    if(x == 0) return true;

    return taken[x - 1][y1] || taken[x - 1][y2];
  }


  void set_player(Player *p) { player = unique_ptr<Player>(p); }

  void clear_entities() {
    entities.clear();
    player.release();
  }

  void edit_player(double x, double y) { player->set_player_xy(x, y); }

  void render() {
    for (unique_ptr<Block> &block : blocks) {
      block->render();
    };
    for (unique_ptr<Entity> &entity : entities) {
      entity->render();
    };
    player->render();
  }
};