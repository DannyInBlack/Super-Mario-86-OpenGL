#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#ifdef __linux__
#else
#include <stdlib.h>
#include <windows.h>
#endif

#include <algorithm>
#include <iostream>
#include <utility>

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

class Player : public Entity {
 public:
  int state = 0;

  Player(double x, double y) : Entity(x, x + 11, y + 15, y) {}

  void set_player_xy(double posX, double posY) {
    Entity::left = posX;
    Entity::right = posX + 11;
    Entity::bottom = posY;
    Entity::up = posY + 15;
  }

  void render() {
    switch (state) {
      case 0:

        // Body

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

        // Head

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
        break;
    }
  }
};
