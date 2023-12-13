#pragma once

#include "render.hpp"

#define MUD 153, 131, 11
#define PLAYER_RED 248, 71, 29
#define YELLOW 255, 192, 123

class Entity : public Renderable {
 protected:
  double left = 0, right = 0, up = 0, bottom = 0;

 public:
  Entity(double l, double r, double u, double b)
      : left(l), right(r), up(u), bottom(b){};

  double get_right() { return right; }

  double get_left() { return left; }

  double get_up() { return up; }

  double get_bottom() { return bottom; }

  virtual void render(){};
};

enum movement { stopped, runLeft1, runLeft2, runRight1, runRight2 };

class Player : public Entity {
 public:
  movement state = stopped;

  Player(double x, double y) : Entity(x, x + 12, y + 16, y) {}

  void set_player_xy(double posX, double posY) {
    Entity::left = posX;
    Entity::right = posX + 12;
    Entity::bottom = posY;
    Entity::up = posY + 16;
  }

  void set_running_state(movement x) { state = x; }

  void render() {
    switch (state) {
      case stopped:
        // HEAD
        glColor3ub(YELLOW);
        glRectd(left + 3, bottom + 9, right - 3, up - 2);
        glRectd(left + 2, up - 5, left + 3, up - 3);
        glRectd(right - 3, up - 7, right - 2, up - 3);
        glRectd(right - 2, up - 5, right - 1, up - 3);
        glRectd(right - 1, up - 5, right, up - 4);

        glColor3ub(MUD);
        glRectd(left + 1, up - 6, left + 2, up - 3);
        glRectd(left + 2, up - 6, left + 3, up - 5);
        glRectd(left + 2, up - 3, left + 5, up - 2);
        glRectd(left + 3, up - 5, left + 5, up - 4);
        glRectd(left + 3, up - 4, left + 4, up - 3);
        glRectd(right - 5, up - 6, right - 1, up - 5);
        glRectd(right - 4, up - 5, right - 3, up - 4);
        glRectd(right - 5, up - 4, right - 4, up - 2);

        glColor3ub(PLAYER_RED);
        glRectd(left + 2, up - 2, right - 1, up - 1);
        glRectd(left + 3, up - 1, right - 4, up);

        // BODY
        glColor3ub(MUD);
        glRectd(left, bottom, left + 4, bottom + 1);
        glRectd(left + 8, bottom, left + 12, bottom + 1);
        glRectd(left + 1, bottom + 1, left + 4, bottom + 2);
        glRectd(left + 8, bottom + 1, left + 11, bottom + 2);

        glColor3ub(PLAYER_RED);
        glRectd(left + 2, bottom + 2, left + 5, bottom + 3);
        glRectd(left + 7, bottom + 2, left + 10, bottom + 3);
        glRectd(left + 2, bottom + 3, left + 10, bottom + 4);
        glRectd(left + 3, bottom + 4, left + 9, bottom + 5);
        glRectd(left + 3, bottom + 5, left + 4, bottom + 6);
        glRectd(left + 5, bottom + 5, left + 7, bottom + 6);
        glRectd(left + 8, bottom + 5, left + 9, bottom + 6);
        glRectd(left + 4, bottom + 6, left + 8, bottom + 7);
        glRectd(left + 4, bottom + 7, left + 5, bottom + 9);
        glRectd(left + 7, bottom + 7, left + 8, bottom + 8);

        glColor3ub(YELLOW);
        glRectd(left, bottom + 3, left + 2, bottom + 6);
        glRectd(left + 2, bottom + 4, left + 3, bottom + 5);
        glRectd(right - 2, bottom + 3, right, bottom + 6);
        glRectd(right - 3, bottom + 4, right - 2, bottom + 5);
        glRectd(right - 3, bottom + 4, right - 2, bottom + 5);
        glRectd(left + 4, bottom + 5, left + 5, bottom + 6);
        glRectd(left + 7, bottom + 5, left + 8, bottom + 6);

        glColor3ub(MUD);
        glRectd(left + 2, bottom + 5, left + 3, bottom + 6);
        glRectd(right - 3, bottom + 5, right - 2, bottom + 6);
        glRectd(left, bottom + 6, left + 4, bottom + 7);
        glRectd(right - 4, bottom + 6, right, bottom + 7);
        glRectd(left + 1, bottom + 7, left + 4, bottom + 8);
        glRectd(left + 5, bottom + 7, left + 7, bottom + 8);
        glRectd(right - 4, bottom + 7, right - 1, bottom + 8);
        glRectd(left + 2, bottom + 8, left + 4, bottom + 9);
        glRectd(left + 5, bottom + 8, left + 8, bottom + 9);
        break;

      case runRight1:
        // HEAD
        glColor3ub(YELLOW);
        glRectd(left + 3, bottom + 9, right - 3, up - 2);
        glRectd(left + 2, up - 5, left + 3, up - 3);
        glRectd(right - 3, up - 7, right - 2, up - 3);
        glRectd(right - 2, up - 5, right - 1, up - 3);
        glRectd(right - 1, up - 5, right, up - 4);

        glColor3ub(MUD);
        glRectd(left + 1, up - 6, left + 2, up - 3);
        glRectd(left + 2, up - 6, left + 3, up - 5);
        glRectd(left + 2, up - 3, left + 5, up - 2);
        glRectd(left + 3, up - 5, left + 5, up - 4);
        glRectd(left + 3, up - 4, left + 4, up - 3);
        glRectd(right - 5, up - 6, right - 1, up - 5);
        glRectd(right - 4, up - 5, right - 3, up - 4);
        glRectd(right - 5, up - 4, right - 4, up - 2);

        glColor3ub(PLAYER_RED);
        glRectd(left + 2, up - 2, right - 1, up - 1);
        glRectd(left + 3, up - 1, right - 4, up);

        // BODY
        glColor3ub(MUD);
        glRectd(left, bottom, left + 3, bottom + 1);

        glRectd(left - 1, bottom + 1, left + 2, bottom + 2);

        glRectd(left - 1, bottom + 2, left + 1, bottom + 3);
        glColor3ub(PLAYER_RED);
        glRectd(left + 1, bottom + 2, left + 4, bottom + 3);
        glRectd(left + 7, bottom + 2, left + 10, bottom + 3);
        glColor3ub(MUD);
        glRectd(left + 10, bottom + 2, left + 12, bottom + 3);

        glColor3ub(PLAYER_RED);
        glRectd(left, bottom + 3, left + 10, bottom + 4);
        glColor3ub(MUD);
        glRectd(left + 10, bottom + 3, left + 12, bottom + 4);

        glColor3ub(PLAYER_RED);
        glRectd(left + 1, bottom + 4, left + 10, bottom + 5);
        glColor3ub(MUD);
        glRectd(left + 10, bottom + 4, left + 12, bottom + 5);

        glColor3ub(YELLOW);
        glRectd(left - 2, bottom + 5, left, bottom + 6);
        glColor3ub(PLAYER_RED);
        glRectd(left + 2, bottom + 5, left + 9, bottom + 6);
        glColor3ub(MUD);
        glRectd(left + 11, bottom + 5, left + 12, bottom + 6);

        glColor3ub(YELLOW);
        glRectd(left - 2, bottom + 6, left + 1, bottom + 7);
        glColor3ub(MUD);
        glRectd(left + 2, bottom + 6, left + 4, bottom + 7);
        glColor3ub(PLAYER_RED);
        glRectd(left + 4, bottom + 6, left + 5, bottom + 7);
        glColor3ub(YELLOW);
        glRectd(left + 5, bottom + 6, left + 6, bottom + 7);
        glColor3ub(PLAYER_RED);
        glRectd(left + 6, bottom + 6, left + 9, bottom + 7);
        glColor3ub(MUD);
        glRectd(left + 9, bottom + 6, left + 11, bottom + 7);
        glColor3ub(YELLOW);
        glRectd(left + 11, bottom + 6, left + 13, bottom + 7);

        glColor3ub(YELLOW);
        glRectd(left - 2, bottom + 7, left, bottom + 8);
        glColor3ub(MUD);
        glRectd(left, bottom + 7, left + 4, bottom + 8);
        glColor3ub(PLAYER_RED);
        glRectd(left + 4, bottom + 7, left + 7, bottom + 8);
        glColor3ub(MUD);
        glRectd(left + 7, bottom + 7, left + 10, bottom + 8);
        glColor3ub(YELLOW);
        glRectd(left + 10, bottom + 7, left + 13, bottom + 8);

        glColor3ub(MUD);
        glRectd(left, bottom + 8, left + 4, bottom + 9);
        glColor3ub(PLAYER_RED);
        glRectd(left + 4, bottom + 8, left + 6, bottom + 9);
        glColor3ub(MUD);
        glRectd(left + 6, bottom + 8, left + 8, bottom + 9);
        break;

      case runLeft1:
        // HEAD
        glColor3ub(YELLOW);
        glRectd(right - 3, bottom + 9, left + 3, up - 2);
        glRectd(right - 2, up - 5, right - 3, up - 3);
        glRectd(left + 3, up - 7, left + 2, up - 3);
        glRectd(left + 2, up - 5, left + 1, up - 3);
        glRectd(left + 1, up - 5, left, up - 4);

        glColor3ub(MUD);
        glRectd(right - 1, up - 6, right - 2, up - 3);
        glRectd(right - 2, up - 6, right - 3, up - 5);
        glRectd(right - 2, up - 3, right - 5, up - 2);
        glRectd(right - 3, up - 5, right - 5, up - 4);
        glRectd(right - 3, up - 4, right - 4, up - 3);
        glRectd(left + 5, up - 6, left + 1, up - 5);
        glRectd(left + 4, up - 5, left + 3, up - 4);
        glRectd(left + 5, up - 4, left + 4, up - 2);

        glColor3ub(PLAYER_RED);
        glRectd(right - 2, up - 2, left + 1, up - 1);
        glRectd(right - 3, up - 1, left + 4, up);

        // BODY
        glColor3ub(MUD);
        glRectd(right, bottom, right - 3, bottom + 1);

        glRectd(right + 1, bottom + 1, right - 2, bottom + 2);

        glRectd(right + 1, bottom + 2, right - 1, bottom + 3);
        glColor3ub(PLAYER_RED);
        glRectd(right - 1, bottom + 2, right - 4, bottom + 3);
        glRectd(right - 7, bottom + 2, right - 10, bottom + 3);
        glColor3ub(MUD);
        glRectd(right - 10, bottom + 2, right - 12, bottom + 3);

        glColor3ub(PLAYER_RED);
        glRectd(right, bottom + 3, right - 10, bottom + 4);
        glColor3ub(MUD);
        glRectd(right - 10, bottom + 3, right - 12, bottom + 4);

        glColor3ub(PLAYER_RED);
        glRectd(right - 1, bottom + 4, right - 10, bottom + 5);
        glColor3ub(MUD);
        glRectd(right - 10, bottom + 4, right - 12, bottom + 5);

        glColor3ub(YELLOW);
        glRectd(right + 2, bottom + 5, right, bottom + 6);
        glColor3ub(PLAYER_RED);
        glRectd(right - 2, bottom + 5, right - 9, bottom + 6);
        glColor3ub(MUD);
        glRectd(right - 11, bottom + 5, right - 12, bottom + 6);

        glColor3ub(YELLOW);
        glRectd(right + 2, bottom + 6, right - 1, bottom + 7);
        glColor3ub(MUD);
        glRectd(right - 2, bottom + 6, right - 4, bottom + 7);
        glColor3ub(PLAYER_RED);
        glRectd(right - 4, bottom + 6, right - 5, bottom + 7);
        glColor3ub(YELLOW);
        glRectd(right - 5, bottom + 6, right - 6, bottom + 7);
        glColor3ub(PLAYER_RED);
        glRectd(right - 6, bottom + 6, right - 9, bottom + 7);
        glColor3ub(MUD);
        glRectd(right - 9, bottom + 6, right - 11, bottom + 7);
        glColor3ub(YELLOW);
        glRectd(right - 11, bottom + 6, right - 13, bottom + 7);

        glColor3ub(YELLOW);
        glRectd(right + 2, bottom + 7, right, bottom + 8);
        glColor3ub(MUD);
        glRectd(right, bottom + 7, right - 4, bottom + 8);
        glColor3ub(PLAYER_RED);
        glRectd(right - 4, bottom + 7, right - 7, bottom + 8);
        glColor3ub(MUD);
        glRectd(right - 7, bottom + 7, right - 10, bottom + 8);
        glColor3ub(YELLOW);
        glRectd(right - 10, bottom + 7, right - 13, bottom + 8);

        glColor3ub(MUD);
        glRectd(right, bottom + 8, right - 4, bottom + 9);
        glColor3ub(PLAYER_RED);
        glRectd(right - 4, bottom + 8, right - 6, bottom + 9);
        glColor3ub(MUD);
        glRectd(right - 6, bottom + 8, right - 8, bottom + 9);
        break;
    }
  }
};
