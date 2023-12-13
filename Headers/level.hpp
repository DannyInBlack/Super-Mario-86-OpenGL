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
  double border = 1;

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

  void move_blocks(double x){
    taken = vector<vector<bool>> (w, vector<bool>(h));

    for(auto &block : blocks){
      block->move_block(x + block->getX());
      border += x;
      for(int i = block->getX(); i < block->getX() + 16; i++){
        for(int j = block->getY(); j < block->getY() + 16; j++){
          if(i < w && i >= 0 && j < h && j >= 0 ) taken[i][j] = 1;
        }
      }
    }
  }

  bool check_border(double x){
    printf("%.2lf\n", x);
    return (border + x > -1.0);
  }

  void add_entity(Entity *entity) {
    entities.push_back(unique_ptr<Entity>(entity));
  }

  bool right_coll() {
    int x = player->get_right();
    int y1 = player->get_up();
    int y2 = player->get_bottom();

    if(x >= 383) return true;

    return taken[x][y1] || taken[x][y2];
  }

  bool future_right_coll() {
    int x = player->get_right();
    int y1 = player->get_up();
    int y2 = player->get_bottom();

    if(x >= 382) return true;

    return taken[x + 1][y1] || taken[x + 1][y2];
  }

  bool left_coll() {
    int x = player->get_left();
    int y1 = player->get_up();
    int y2 = player->get_bottom();

    if(x <= 0) return true;

    return taken[x][y1] || taken[x][y2];
  }

  bool future_left_coll() {
    int x = player->get_left();
    int y1 = player->get_up();
    int y2 = player->get_bottom();

    if(x - 1 <= 0) return true;

    return taken[x - 1][y1] || taken[x - 1][y2];
  }

  bool ground_coll() {
    int x1 = player->get_left();
    int x2 = player->get_right();
    int y = player->get_bottom();
    return taken[x1][y] || taken[x2][y];
  }

  bool future_ground_coll() {
    int x1 = player->get_left();
    int x2 = player->get_right();
    int y = player->get_bottom();

    return taken[x1][y - 1] || taken[x2][y - 1];
  }

  bool upward_coll() {
    int x1 = player->get_left();
    int x2 = player->get_right();
    int y = player->get_up();

    return taken[x1][y] || taken[x2][y];
  }

  void set_player_state(movement state) { player->set_running_state(state); }

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