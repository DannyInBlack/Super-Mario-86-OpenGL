#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#ifdef __linux__
#else
#include <stdlib.h>
#include <windows.h>
#endif

#include <iostream>

#include "render.hpp"

#define BLACK 0, 0, 0
#define WHITE 255, 213, 207
#define BROWN 222, 89, 24
#define YELLOW 255, 192, 123

/**
 * Defines Blocks that have hitbox and are Renderable
 * Each type of block is defined below
 */

class Block : public Renderable {
 protected:
  double x, y;

 public:
  Block(double x, double y) {
    this->x = x;
    this->y = y;
  }
  double getX(){ return x;}

  double getY(){ return y;}

  void move_block(double pos){
    this->x = pos;
    
  }

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
