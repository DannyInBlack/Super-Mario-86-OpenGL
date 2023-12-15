#include "blocks.hpp"
#include "entity.hpp"
#include "scenery.hpp"
using namespace std;

class Level {
 private:
  vector<vector<bool>> taken;
  vector<unique_ptr<Block>>
      blocks;  // TODO: Implement as grid for constant time complexity when
               // searching for collisions
  vector<unique_ptr<Entity>> entities;
  vector<unique_ptr<Scenery>> scenery;
  vector<unique_ptr<Scenery>> bg_scenery;
  unique_ptr<Player> player;
  int w;
  int h;
  double left_border = 0, right_border = 600;

 public:
  Level(int w, int h) {
    taken = vector<vector<bool>>(w, vector<bool>(h));
    this->w = w;
    this->h = h;
  }

  Level(Level &&l) {
    // *this = move(l);
    taken = move(l.taken);
    blocks = move(l.blocks);
    entities = move(l.entities);
    scenery = move(l.scenery);
    bg_scenery = move(l.bg_scenery);
    player = move(l.player);

    w = l.w;
    h = l.h;
    left_border = l.left_border;
    right_border = l.right_border;
  }

  void add_block(Block *block) {
    blocks.push_back(unique_ptr<Block>(block));

    for (int i = block->getX(); i < block->getX() + 16; i++) {
      for (int j = block->getY(); j < block->getY() + 16; j++) {
        if (i < w && i >= 0 && j < h && j >= 0) taken[i][j] = 1;
      }
    }
  }

  void move_objects(double x) {
    taken = vector<vector<bool>>(w, vector<bool>(h));
    left_border += x;
    right_border += x;

    for (auto &block : blocks) {
      // block.get()->move_block(2);
      block->move_block(x + block->getX());
      for (int i = block->getX(); i < block->getX() + 16; i++) {
        for (int j = block->getY(); j < block->getY() + 16; j++) {
          if (i < w && i >= 0 && j < h && j >= 0) taken[i][j] = 1;
        }
      }
    }

    for (auto &scene : scenery) {
      scene->move_scene(x + scene->getX());
    }
  }

  bool check_left_border() { return left_border <= 0; }
  bool check_right_border() { return right_border > 383; }

  void add_entity(Entity *entity) {
    entities.push_back(unique_ptr<Entity>(entity));
  }

  bool right_coll() {
    int x = player->get_right();
    int y1 = player->get_up();
    int y2 = player->get_bottom();

    if (x >= 383) return true;

    return taken[x][y1] || taken[x][y2];
  }

  bool future_right_coll() {
    int x = player->get_right();
    int y1 = player->get_up();
    int y2 = player->get_bottom();

    if (x >= 382) return true;

    return taken[x + 1][y1] || taken[x + 1][y2];
  }

  bool left_coll() {
    int x = player->get_left();
    int y1 = player->get_up();
    int y2 = player->get_bottom();

    if (x <= 0) return true;

    return taken[x][y1] || taken[x][y2];
  }

  bool future_left_coll() {
    int x = player->get_left();
    int y1 = player->get_up();
    int y2 = player->get_bottom();

    if (x - 1 <= 0) return true;

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

  void add_scenery(Scenery *bg) { scenery.push_back(unique_ptr<Scenery>(bg)); }
  void add_bg_scenery(Scenery *bg) {
    bg_scenery.push_back(unique_ptr<Scenery>(bg));
  }

  void render() {
    for (unique_ptr<Scenery> &sc : bg_scenery) {
      sc->render();
    }
    for (unique_ptr<Scenery> &sc : scenery) {
      sc->render();
    }
    for (unique_ptr<Block> &block : blocks) {
      if (block->getX() + 16 >= 0 || block->getX() < 384) block->render();
    };
    for (unique_ptr<Entity> &entity : entities) {
      entity->render();
    };
    player->render();
  }
};