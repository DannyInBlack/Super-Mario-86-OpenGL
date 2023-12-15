
// Defines the Renderable class that most game entities and blocks are based on
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <windows.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#define MUD 153, 131, 11
#define PLAYER_RED 248, 71, 29
#define YELLOW 255, 192, 123
#define BLACK 0, 0, 0
#define WHITE 255, 213, 207
#define BROWN 222, 89, 24
#define YELLOW 255, 192, 123
#define SKY_BLUE 161, 173, 255
#define CLOUD_BLUE 40, 217, 255
#define BUSH_GREEN 197, 226, 48
#define BUSH_DARK_GREEN 60, 182, 0
#define CLOUD_WHITE 255, 255, 255

class Renderable {
  virtual void render() = 0;
};

using namespace std;


class Scenery : public Renderable {
 protected:
  double x, y;

 public:
  Scenery(double x, double y) : x(x), y(y){};
  double getX() { return x; }
  void move_scene(double pos) { x = pos; }
  virtual void render(){};
};

class Star : public Scenery {
  double r;
  int sp;

 public:
  Star(double x, double y, double r, int sp)
      : Scenery(x, y),
        r(r),
        sp(sp){
            // printf("hey\n");
        };

  void render() {
    glColor3ub(PLAYER_RED);

    glBegin(GL_POLYGON);
    for (int i = 0, j = sp; i < 5; i++, j += 72) {
      double cx = sin(j * M_PI / 180) * r;
      double cy = cos(j * M_PI / 180) * r;
      glVertex2d(cx + x, cy + y);

      cx = sin((j + 36) * M_PI / 180) * (r + r * 1.5);
      cy = cos((j + 36) * M_PI / 180) * (r + r * 1.5);

      glVertex2d(cx + x, cy + y);
    }
    glEnd();
    int z = r - 1;

    glColor3ub(YELLOW);

    glBegin(GL_POLYGON);
    for (int i = 0, j = sp; i < 5; i++, j += 72) {
      double cx = sin(j * M_PI / 180) * z;
      double cy = cos(j * M_PI / 180) * z;
      glVertex2d(cx + x, cy + y);

      cx = sin((j + 36) * M_PI / 180) * (z + z * 1.5);
      cy = cos((j + 36) * M_PI / 180) * (z + z * 1.5);

      glVertex2d(cx + x, cy + y);
    }
    glEnd();

    sp = (sp + 1) % 360;
  }
};

class Hill : public Scenery {
 public:
  Hill(double x, double y) : Scenery(x, y) {}
  // Hill scenery that (look like) far away trees
  void draw_hill_scenery(int x, int y) {
    glColor3ub(BLACK);
    glRectd(x, y, x + 2, y + 4);
    glRectd(x + 3, y + 3, x + 6, y + 7);
    glRectd(x + 4, y + 2, x + 5, y + 8);
  }

  void render() {
    for (int i = 0; i < 32; i++) {
      glColor3ub(BLACK);
      glRectd(x - 40 + i, y + i, x + 40 - i, y + i + 1);
      glColor3ub(BUSH_DARK_GREEN);
      glRectd(x - 40 + i + 1, y + i, x + 40 - i - 1, y + i + 1);
    }
    glColor3ub(BLACK);
    glRectd(x - 8, y + 32, x - 6, y + 33);
    glRectd(x - 6, y + 33, x - 3, y + 34);
    glRectd(x - 3, y + 34, x + 3, y + 35);
    glRectd(x + 3, y + 33, x + 6, y + 34);
    glRectd(x + 6, y + 32, x + 8, y + 33);

    glColor3ub(BUSH_DARK_GREEN);
    glRectd(x - 6, y + 32, x + 6, y + 33);
    glRectd(x - 3, y + 33, x + 3, y + 34);

    draw_hill_scenery(x - 20, y + 8);
    draw_hill_scenery(x + 10, y + 8);
    draw_hill_scenery(x, y + 25);
  }
};

class Cloud : public Scenery {
 private:
  int rep;
  bool cl;
  double x2, speed;

  void cloud_start() {
    x2 = x;
    glColor3ub(BLACK);
    glRectd(x2, y + 9, x2 + 1, y + 11);
    glRectd(x2 + 1, y + 11, x2 + 3, y + 12);
    glRectd(x2 + 1, y + 8, x2 + 2, y + 9);
    glRectd(x2 + 2, y + 7, x2 + 3, y + 8);
    glRectd(x2 + 3, y + 6, x2 + 4, y + 7);
    glRectd(x2 + 4, y + 6, x2 + 5, y + 4);
    glRectd(x2 + 5, y + 3, x2 + 8, y + 4);

    glRectd(x2 + 3, y + 13, x2 + 4, y + 14);
    glRectd(x2 + 4, y + 14, x2 + 5, y + 15);
    glRectd(x2 + 5, y + 15, x2 + 8, y + 16);

    cl ? glColor3ub(CLOUD_WHITE) : glColor3ub(BUSH_GREEN);
    glRectd(x2 + 1, y + 9, x2 + 2, y + 11);
    glRectd(x2 + 2, y + 8, x2 + 3, y + 11);
    glRectd(x2 + 3, y + 7, x2 + 4, y + 13);
    glRectd(x2 + 4, y + 6, x2 + 5, y + 14);
    glRectd(x2 + 5, y + 4, x2 + 8, y + 15);

    cl ? glColor3ub(CLOUD_BLUE) : glColor3ub(BUSH_DARK_GREEN);
    glRectd(x2 + 5, y + 7, x2 + 6, y + 8);
    glRectd(x2 + 6, y + 6, x2 + 7, y + 7);
    glRectd(x2 + 7, y + 5, x2 + 8, y + 6);

    x2 += 8;
  }

  // Drawing of the cloud middle part
  void cloud_mid() {
    glColor3ub(BLACK);
    glRectd(x2, y + 2, x2 + 1, y + 3);
    glRectd(x2 + 1, y + 1, x2 + 3, y + 2);
    glRectd(x2 + 3, y, x2 + 6, y + 1);
    glRectd(x2 + 6, y + 1, x2 + 7, y + 2);
    glRectd(x2 + 7, y + 2, x2 + 8, y + 3);
    glRectd(x2 + 8, y + 1, x2 + 10, y + 2);
    glRectd(x2 + 10, y, x2 + 14, y + 1);
    glRectd(x2 + 14, y + 1, x2 + 16, y + 2);

    glRectd(x2, y + 16, x2 + 1, y + 17);
    glRectd(x2 + 1, y + 17, x2 + 2, y + 18);
    glRectd(x2 + 2, y + 18, x2 + 3, y + 21);
    glRectd(x2 + 3, y + 21, x2 + 5, y + 22);
    glRectd(x2 + 5, y + 22, x2 + 6, y + 23);
    glRectd(x2 + 6, y + 23, x2 + 10, y + 24);
    glRectd(x2 + 10, y + 22, x2 + 11, y + 23);
    glRectd(x2 + 11, y + 22, x2 + 12, y + 20);
    glRectd(x2 + 12, y + 20, x2 + 13, y + 19);
    glRectd(x2 + 13, y + 20, x2 + 14, y + 21);
    glRectd(x2 + 14, y + 20, x2 + 15, y + 19);
    glRectd(x2 + 15, y + 19, x2 + 16, y + 16);

    cl ? glColor3ub(CLOUD_WHITE) : glColor3ub(BUSH_GREEN);
    glRectd(x2, y + 3, x2 + 1, y + 16);
    glRectd(x2 + 1, y + 2, x2 + 2, y + 17);
    glRectd(x2 + 2, y + 2, x2 + 3, y + 18);
    glRectd(x2 + 3, y + 1, x2 + 5, y + 21);
    glRectd(x2 + 5, y + 1, x2 + 6, y + 22);
    glRectd(x2 + 6, y + 2, x2 + 7, y + 23);
    glRectd(x2 + 7, y + 3, x2 + 8, y + 23);
    glRectd(x2 + 8, y + 2, x2 + 10, y + 23);
    glRectd(x2 + 10, y + 1, x2 + 11, y + 22);
    glRectd(x2 + 11, y + 1, x2 + 12, y + 20);
    glRectd(x2 + 12, y + 1, x2 + 13, y + 19);
    glRectd(x2 + 13, y + 1, x2 + 14, y + 20);
    glRectd(x2 + 14, y + 2, x2 + 15, y + 19);
    glRectd(x2 + 15, y + 2, x2 + 16, y + 16);

    cl ? glColor3ub(CLOUD_BLUE) : glColor3ub(BUSH_DARK_GREEN);
    glRectd(x2, y + 5, x2 + 3, y + 6);
    glRectd(x2 + 1, y + 6, x2 + 2, y + 7);
    glRectd(x2 + 2, y + 4, x2 + 8, y + 5);
    glRectd(x2 + 4, y + 3, x2 + 6, y + 4);
    glRectd(x2 + 6, y + 5, x2 + 10, y + 6);
    glRectd(x2 + 8, y + 6, x2 + 9, y + 7);
    glRectd(x2 + 9, y + 7, x2 + 10, y + 8);
    glRectd(x2 + 9, y + 4, x2 + 14, y + 5);
    glRectd(x2 + 10, y + 3, x2 + 13, y + 5);
    glRectd(x2 + 14, y + 5, x2 + 15, y + 6);

    glRectd(x2 + 4, y + 16, x2 + 5, y + 17);
    glRectd(x2 + 5, y + 17, x2 + 7, y + 18);
    glRectd(x2 + 9, y + 18, x2 + 10, y + 19);
    glRectd(x2 + 10, y + 17, x2 + 11, y + 18);

    x2 += 16;
  }

  // Drawing of the cloud end part
  void cloud_end() {
    glColor3ub(BLACK);
    glRectd(x2, y + 2, x2 + 1, y + 3);
    glRectd(x2 + 1, y + 1, x2 + 3, y + 2);
    glRectd(x2 + 3, y + 2, x2 + 5, y + 3);
    glRectd(x2 + 5, y + 3, x2 + 7, y + 4);
    glRectd(x2 + 7, y + 5, x2 + 8, y + 6);
    glRectd(x2 + 6, y + 6, x2 + 7, y + 7);
    glRectd(x2 + 5, y + 7, x2 + 6, y + 8);
    glRectd(x2 + 6, y + 8, x2 + 7, y + 9);
    glRectd(x2 + 7, y + 9, x2 + 8, y + 12);
    glRectd(x2 + 6, y + 12, x2 + 7, y + 13);
    glRectd(x2 + 5, y + 11, x2 + 6, y + 12);
    glRectd(x2 + 4, y + 12, x2 + 5, y + 15);
    glRectd(x2 + 3, y + 15, x2 + 4, y + 16);
    glRectd(x2 + 2, y + 14, x2 + 3, y + 15);
    glRectd(x2 + 1, y + 13, x2 + 2, y + 14);
    glRectd(x2, y + 14, x2 + 1, y + 16);

    cl ? glColor3ub(CLOUD_WHITE) : glColor3ub(BUSH_GREEN);
    glRectd(x2, y + 3, x2 + 1, y + 14);
    glRectd(x2 + 1, y + 2, x2 + 2, y + 13);
    glRectd(x2 + 2, y + 2, x2 + 3, y + 14);
    glRectd(x2 + 3, y + 3, x2 + 4, y + 15);
    glRectd(x2 + 4, y + 3, x2 + 5, y + 12);
    glRectd(x2 + 5, y + 4, x2 + 6, y + 7);
    glRectd(x2 + 6, y + 4, x2 + 7, y + 6);
    glRectd(x2 + 5, y + 8, x2 + 6, y + 11);
    glRectd(x2 + 6, y + 9, x2 + 7, y + 12);
  }

 public:
  Cloud(double x, double y, double rep, bool cl, double speed) : Scenery(x, y), rep(rep), cl(cl), speed(speed){};

  void render(){
    cloud_start();
    for(int i = 0; i < rep; i++){
      cloud_mid();
    }
    cloud_end();

    x  < 400 ? x += speed : x = -100;
  }

};


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

class Block : public Renderable {
 protected:
  double x, y;

 public:
  Block(double x, double y) {
    this->x = x;
    this->y = y;
  }
  double getX() { return x; }

  double getY() { return y; }

  void move_block(double pos) { this->x = pos; }

  virtual void render() {}

  void print_coordinates() { printf("(%lf, %lf)\n", x, y); }
};

class PlatformBlock : public Block {
 public:
  PlatformBlock(double x, double y) : Block(x, y) {}

  void render() {
    glLineWidth(4);

    glColor3ub(BLACK);
    glRectd(x, y, x + 16, y + 16);

    glColor3ub(BROWN);
    glRectd(x, y + 1, x + 4, y + 4);
    glRectd(x + 5, y + 1, x + 11, y + 4);
    glRectd(x + 12, y + 1, x + 16, y + 4);

    glRectd(x, y + 5, x + 7, y + 8);
    glRectd(x + 8, y + 5, x + 15, y + 8);

    glRectd(x, y + 9, x + 4, y + 12);
    glRectd(x + 5, y + 9, x + 11, y + 12);
    glRectd(x + 12, y + 9, x + 16, y + 12);

    glRectd(x, y + 13, x + 7, y + 16);
    glRectd(x + 8, y + 13, x + 15, y + 16);
  }
};

class SurfacePlatformBlock : public PlatformBlock {
 public:
  SurfacePlatformBlock(double x, double y) : PlatformBlock(x, y) {}

  void render() {
    PlatformBlock::render();
    glColor3ub(WHITE);
    glRectd(x, y + 15, x + 16, y + 16);
  }
};

class SurfaceBlock : public Block {
 public:
  SurfaceBlock(double x, double y) : Block(x, y) {}

  void render() {
    glColor3ub(BROWN);
    glRectd(x, y, x + 16, y + 16);
    glColor3ub(WHITE);
    glRectd(x + 1, y + 4, x + 2, y + 5);
    glRectd(x + 2, y + 3, x + 4, y + 4);
    glRectd(x + 4, y + 2, x + 7, y + 3);
    glRectd(x, y + 1, x + 1, y + 5);
    glRectd(x, y + 6, x + 1, y + 15);
    glRectd(x + 1, y + 15, x + 9, y + 16);
    glRectd(x + 11, y + 15, x + 15, y + 16);
    glRectd(x + 10, y + 15, x + 11, y + 11);
    glRectd(x + 11, y + 9, x + 15, y + 10);
    glRectd(x + 10, y + 10, x + 11, y + 6);
    glRectd(x + 9, y + 6, x + 10, y + 4);
    glRectd(x + 8, y + 4, x + 9, y);
    glColor3ub(BLACK);
    glRectd(x + 1, y, x + 7, y + 1);
    glRectd(x, y + 5, x + 2, y + 6);
    glRectd(x + 2, y + 4, x + 4, y + 5);
    glRectd(x + 4, y + 3, x + 8, y + 4);
    glRectd(x + 7, y + 3, x + 8, y + 1);
    glRectd(x + 8, y + 4, x + 9, y + 6);
    glRectd(x + 9, y + 6, x + 10, y + 16);
    glRectd(x + 9, y, x + 15, y + 1);
    glRectd(x + 14, y + 1, x + 16, y + 2);
    glRectd(x + 15, y + 2, x + 16, y + 10);
    glRectd(x + 15, y + 10, x + 11, y + 11);
    glRectd(x + 15, y + 11, x + 16, y + 15);
    glRectd(x + 11, y + 11, x + 12, y + 12);
  }
};

class LuckyBlock : public Block {
 private:
  void question_mark(const double x, const double y) {
    glRectd(x + 4, y, x + 6, y + 2);
    glRectd(x + 4, y + 3, x + 6, y + 5);
    glRectd(x + 5, y + 5, x + 6, y + 6);
    glRectd(x + 6, y + 5, x + 8, y + 9);
    glRectd(x + 2, y + 9, x + 7, y + 10);
    glRectd(x + 1, y + 6, x + 3, y + 9);
  }

 public:
  LuckyBlock(double x, double y) : Block(x, y) {}

  void render() {
    glColor3ub(BLACK);
    glRectd(x, y, x + 16, y + 1);
    glRectd(x + 15, y, x + 16, y + 15);

    glColor3ub(BROWN);
    glRectd(x, y + 1, x + 1, y + 15);
    glRectd(x + 1, y + 15, x + 15, y + 16);

    glColor3ub(YELLOW);
    glRectd(x + 1, y + 1, x + 15, y + 15);

    glColor3ub(BLACK);
    glRectd(x + 2, y + 2, x + 3, y + 3);
    glRectd(x + 2, y + 13, x + 3, y + 14);
    glRectd(x + 13, y + 2, x + 14, y + 3);
    glRectd(x + 13, y + 13, x + 14, y + 14);

    question_mark(x + 4, y + 2);

    glColor3ub(BROWN);
    question_mark(x + 3, y + 3);
  }
};

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

// 2D Project: Computer Graphics CS352
// Made by: Danial Sabry

// Pos(24 * 16)
#define B_SIZE 16  // Blocks are 16 * 16

// Window parameters
#define WINDOW_SIZE 1200, 800
#define WINDOW_NAME "211010447"
#define WINDOW_POSITION 200, 0

// Variables used for animation
double cloudA1 = 30, cloudA2 = 60, cloudA3 = 345;
double playerX = 6 * B_SIZE + 8, playerY = 2 * B_SIZE;
bool rightPressed = false, leftPressed = false, upPressed = false;
bool onGround = true;
bool paused = false;
bool centered = false;
double moveStateX = 0;  // moving state, represents movement in the x-direction
double moveStateY = 0;  // moving state, represents movement in the y-direction
double offset = 6 * B_SIZE + 8;

// Level level1(384, 256);  // First Level
// Level level2(384, 256);  // Second Level

vector<Level> levels;
int current_level = 0;

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  // Background done using a rectangle to use HEX colors (The other way doesn't
  // allow for colors)
  glColor3ub(SKY_BLUE);
  glRectd(0, 0, 383, 255);

  levels[current_level].render();

  if (paused) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(0, 0, 0, 0.5);
    glRectd(0, 0, 383, 255);

    glColor3ub(CLOUD_WHITE);
    glRectd(160, 80, 160 + 20, 180);
    glRectd(200, 80, 200 + 20, 180);
  }

  glutSwapBuffers();
}

void timer(int) {
  // Clouds move at seperate speeds
  glutPostRedisplay();
  glutTimerFunc(1000 / 60, timer, 0);

  if (paused) return;

  if (upPressed && onGround) moveStateY = 10.0;
  offset = playerX;

  playerX += 0.2 * moveStateX;

  levels[current_level].edit_player(playerX, playerY);

  if (levels[current_level].right_coll()) {
    moveStateX = 0;
    playerX = ceil(playerX);
    levels[current_level].edit_player(playerX, playerY);
    printf("RIGHT COLLISION: PLAYER X = %d\n", (int)playerX);

    while (levels[current_level].right_coll()) {
      playerX -= 1;
      levels[current_level].edit_player(playerX, playerY);
    }
  } else if (levels[current_level].left_coll()) {
    moveStateX = 0;
    playerX = floor(playerX);
    levels[current_level].edit_player(playerX, playerY);
    printf("LEFT COLLISION: PLAYER X = %d\n", (int)playerX);

    while (levels[current_level].left_coll()) {
      playerX += 1;
      levels[current_level].edit_player(playerX, playerY);
    }
  }

  if ((!rightPressed && !leftPressed || leftPressed && rightPressed) &&
      moveStateX != 0) {
    moveStateX = moveStateX > 0 ? max(moveStateX - 0.5, 0.0)
                                : min(moveStateX + 0.5, 0.0);
  } else if (rightPressed && !levels[current_level].future_right_coll()) {
    moveStateX = min(moveStateX + 0.5, 10.0);
    levels[current_level].set_player_state(runRight1);
  } else if (leftPressed && !levels[current_level].future_left_coll()) {
    moveStateX = max(moveStateX - 0.6, -10.0);
    levels[current_level].set_player_state(runLeft1);
  } else {
    levels[current_level].set_player_state(stopped);
  }

  playerY += 0.3 * moveStateY;
  levels[current_level].edit_player(playerX, playerY);

  if (levels[current_level].ground_coll()) {
    moveStateY = 0;
    onGround = true;
    playerY = ceil(playerY);
    levels[current_level].edit_player(playerX, playerY);
    printf("GROUND COLLISION: PLAYER Y = %d\n", (int)playerY);
    while (levels[current_level].ground_coll()) {
      playerY += 1;
      levels[current_level].edit_player(playerX, playerY);
    }
  } else if (levels[current_level].upward_coll()) {
    moveStateY = 0;
    playerY = floor(playerY);
    levels[current_level].edit_player(playerX, playerY);
    printf("UP COLLISION: PLAYER Y = %d\n", (int)playerY);
    while (levels[current_level].upward_coll()) {
      playerY -= 1;
      levels[current_level].edit_player(playerX, playerY);
    }
  }

  if (!levels[current_level].future_ground_coll()) {
    onGround = 0;
  }

  if (!onGround) {
    moveStateY = max(moveStateY - 0.2, -10.0);
  }

  centered |= playerX > 186 && playerX < 189;

  if (offset - playerX > 0) {
    centered &= levels[current_level].check_left_border();
  } else {
    centered &= levels[current_level].check_right_border();
  }

  if (centered) {
    levels[current_level].move_objects(offset - playerX);
    playerX = offset;
    levels[current_level].edit_player(playerX, playerY);
  }

  if (playerX >= 370 && current_level + 1 < levels.size()) {
    playerX = 3;
    current_level++;
  } else if (playerX <= 2 && current_level > 0) {
    playerX = 368;
    current_level--;
  }
}

// Handles reshape of window
void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 383.0, 0.0, 255.0);  // (24 * 16, 16 * 16)
  glMatrixMode(GL_MODELVIEW);
}

// Handles button presses, still needs the up-movement
// Boolean variable used for smooth movement
void handle_movement(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      upPressed = true;
      break;
    case GLUT_KEY_RIGHT:
      rightPressed = true;
      break;
    case GLUT_KEY_LEFT:
      leftPressed = true;
      break;
  }
}

void handle_no_movement(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      upPressed = false;
      break;
    case GLUT_KEY_RIGHT:
      rightPressed = false;
      break;
    case GLUT_KEY_LEFT:
      leftPressed = false;
      break;
  }
}

void keyboard_movement(unsigned char key, int x, int y) {
  switch (key) {
    case 'w':
      upPressed = true;
      break;
    case 'd':
      rightPressed = true;
      break;
    case 'a':
      leftPressed = true;
      break;
  }
}

// Handles buttons releases
void keyboard_no_movement(unsigned char key, int x, int y) {
  switch (key) {
    case 'w':
      upPressed = false;
      break;
    case 'd':
      rightPressed = false;
      break;
    case 'a':
      leftPressed = false;
      break;
  }
}

void on_mouse_click(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    paused = !paused;
  }
}

void first_level() {
  levels.push_back(Level(384, 256));
  for (int i = -8, j = 0; j < 50; i += B_SIZE, j++) {
    levels[0].add_block(new SurfaceBlock(i, B_SIZE * 0));
    levels[0].add_block(new SurfaceBlock(i, B_SIZE * 1));
  }

  levels[0].add_block(new LuckyBlock(10 * B_SIZE - 8, B_SIZE * 5));

  levels[0].add_block(new SurfacePlatformBlock(18 * B_SIZE - 8, 5 * B_SIZE));
  levels[0].add_block(new LuckyBlock(19 * B_SIZE - 8, 5 * B_SIZE));
  levels[0].add_block(new SurfacePlatformBlock(20 * B_SIZE - 8, 5 * B_SIZE));
  levels[0].add_block(new LuckyBlock(21 * B_SIZE - 8, 5 * B_SIZE));
  levels[0].add_block(new SurfacePlatformBlock(22 * B_SIZE - 8, 5 * B_SIZE));

  levels[0].add_block(new LuckyBlock(20 * B_SIZE - 8, 9 * B_SIZE));

  levels[0].set_player(new Player(playerX, playerY));

  levels[0].add_scenery(new Star(10 * B_SIZE, 6 * B_SIZE + 8, 3, 0));
  levels[0].add_scenery(new Cloud(9 * B_SIZE, B_SIZE + 8, 3, false, 0));

  levels[0].add_bg_scenery(new Hill(21, 2 * B_SIZE));
  levels[0].add_bg_scenery(new Hill(235, B_SIZE));
  levels[0].add_bg_scenery(new Cloud(30, 200, 3, true, 0.1));
  levels[0].add_bg_scenery(new Cloud(60, 100, 1, true, 0.2));
  levels[0].add_bg_scenery(new Cloud(345, 225, 1, true, 0.1));
}

void second_level() {
  levels.push_back(Level(384, 256));

  levels[1].set_player(new Player(playerX, playerY));

  for (int i = -8, j = 0; j < 50; i += B_SIZE, j++) {
    levels[1].add_block(new SurfaceBlock(i, B_SIZE * 0));
    levels[1].add_block(new SurfaceBlock(i, B_SIZE * 1));
  }

  levels[1].add_bg_scenery(new Cloud(350, 225, 2, true, 0.5));
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_SINGLE);

  glutInitWindowSize(WINDOW_SIZE);
  glutInitWindowPosition(WINDOW_POSITION);
  glutCreateWindow(WINDOW_NAME);

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutTimerFunc(0, timer, 0);
  glutSpecialFunc(handle_movement);
  glutSpecialUpFunc(handle_no_movement);
  glutKeyboardFunc(keyboard_movement);
  glutKeyboardUpFunc(keyboard_no_movement);
  glutMouseFunc(on_mouse_click);

  // glClearColor(161 / 253, 173 / 253, 255 / 253, 1);

  // Adding the level blocks

  first_level();
  second_level();

  glutMainLoop();

  return 0;
}
