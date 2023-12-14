#include "render.hpp"
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
