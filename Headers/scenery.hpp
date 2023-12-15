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
