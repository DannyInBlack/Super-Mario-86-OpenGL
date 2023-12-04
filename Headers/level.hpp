#include <vector>
#include <memory>
#include <iostream>
#include "entity.hpp"
#include "blocks.hpp"
using namespace std;

class Level {
 private:
  vector<unique_ptr<Block>>
      blocks;  // TODO: Implement as grid for constant time complexity when
               // searching for collisions
  vector<unique_ptr<Entity>> entities;
  unique_ptr<Player> player;

 public:
  void add_block(Block *block) { blocks.push_back(unique_ptr<Block>(block)); }

  void add_entity(Entity *entity) {
    entities.push_back(unique_ptr<Entity>(entity));
  }

  bool check_left() {  // O(blocks) time complexity
    for (auto &block : blocks) {
      if (block->left_collision(player->get_right(), player->get_up())) {
        return true;
      }
    }
    return false;
  }

  bool check_right() {  // O(blocks) time complexity
    for (auto &block : blocks) {
      if (block->right_collision(player->get_left(), player->get_up())) {
        return true;
      }
    }
    return false;
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