#include "Headers/level.hpp"
using namespace std;

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


// Level class defines

Level level1(384, 256);  // First Level

// Drawing of the cloud beginning
void cloud_start(double &x, double y, bool cloud) {
  glColor3ub(BLACK);
  glRectd(x, y + 9, x + 1, y + 11);
  glRectd(x + 1, y + 11, x + 3, y + 12);
  glRectd(x + 1, y + 8, x + 2, y + 9);
  glRectd(x + 2, y + 7, x + 3, y + 8);
  glRectd(x + 3, y + 6, x + 4, y + 7);
  glRectd(x + 4, y + 6, x + 5, y + 4);
  glRectd(x + 5, y + 3, x + 8, y + 4);

  glRectd(x + 3, y + 13, x + 4, y + 14);
  glRectd(x + 4, y + 14, x + 5, y + 15);
  glRectd(x + 5, y + 15, x + 8, y + 16);

  cloud ? glColor3ub(CLOUD_WHITE) : glColor3ub(BUSH_GREEN);
  glRectd(x + 1, y + 9, x + 2, y + 11);
  glRectd(x + 2, y + 8, x + 3, y + 11);
  glRectd(x + 3, y + 7, x + 4, y + 13);
  glRectd(x + 4, y + 6, x + 5, y + 14);
  glRectd(x + 5, y + 4, x + 8, y + 15);

  cloud ? glColor3ub(CLOUD_BLUE) : glColor3ub(BUSH_DARK_GREEN);
  glRectd(x + 5, y + 7, x + 6, y + 8);
  glRectd(x + 6, y + 6, x + 7, y + 7);
  glRectd(x + 7, y + 5, x + 8, y + 6);

  x += 8;
}

// Drawing of the cloud middle part
void cloud_mid(double &x, double y, bool cloud) {
  glColor3ub(BLACK);
  glRectd(x, y + 2, x + 1, y + 3);
  glRectd(x + 1, y + 1, x + 3, y + 2);
  glRectd(x + 3, y, x + 6, y + 1);
  glRectd(x + 6, y + 1, x + 7, y + 2);
  glRectd(x + 7, y + 2, x + 8, y + 3);
  glRectd(x + 8, y + 1, x + 10, y + 2);
  glRectd(x + 10, y, x + 14, y + 1);
  glRectd(x + 14, y + 1, x + 16, y + 2);

  glRectd(x, y + 16, x + 1, y + 17);
  glRectd(x + 1, y + 17, x + 2, y + 18);
  glRectd(x + 2, y + 18, x + 3, y + 21);
  glRectd(x + 3, y + 21, x + 5, y + 22);
  glRectd(x + 5, y + 22, x + 6, y + 23);
  glRectd(x + 6, y + 23, x + 10, y + 24);
  glRectd(x + 10, y + 22, x + 11, y + 23);
  glRectd(x + 11, y + 22, x + 12, y + 20);
  glRectd(x + 12, y + 20, x + 13, y + 19);
  glRectd(x + 13, y + 20, x + 14, y + 21);
  glRectd(x + 14, y + 20, x + 15, y + 19);
  glRectd(x + 15, y + 19, x + 16, y + 16);

  cloud ? glColor3ub(CLOUD_WHITE) : glColor3ub(BUSH_GREEN);
  glRectd(x, y + 3, x + 1, y + 16);
  glRectd(x + 1, y + 2, x + 2, y + 17);
  glRectd(x + 2, y + 2, x + 3, y + 18);
  glRectd(x + 3, y + 1, x + 5, y + 21);
  glRectd(x + 5, y + 1, x + 6, y + 22);
  glRectd(x + 6, y + 2, x + 7, y + 23);
  glRectd(x + 7, y + 3, x + 8, y + 23);
  glRectd(x + 8, y + 2, x + 10, y + 23);
  glRectd(x + 10, y + 1, x + 11, y + 22);
  glRectd(x + 11, y + 1, x + 12, y + 20);
  glRectd(x + 12, y + 1, x + 13, y + 19);
  glRectd(x + 13, y + 1, x + 14, y + 20);
  glRectd(x + 14, y + 2, x + 15, y + 19);
  glRectd(x + 15, y + 2, x + 16, y + 16);

  cloud ? glColor3ub(CLOUD_BLUE) : glColor3ub(BUSH_DARK_GREEN);
  glRectd(x, y + 5, x + 3, y + 6);
  glRectd(x + 1, y + 6, x + 2, y + 7);
  glRectd(x + 2, y + 4, x + 8, y + 5);
  glRectd(x + 4, y + 3, x + 6, y + 4);
  glRectd(x + 6, y + 5, x + 10, y + 6);
  glRectd(x + 8, y + 6, x + 9, y + 7);
  glRectd(x + 9, y + 7, x + 10, y + 8);
  glRectd(x + 9, y + 4, x + 14, y + 5);
  glRectd(x + 10, y + 3, x + 13, y + 5);
  glRectd(x + 14, y + 5, x + 15, y + 6);

  glRectd(x + 4, y + 16, x + 5, y + 17);
  glRectd(x + 5, y + 17, x + 7, y + 18);
  glRectd(x + 9, y + 18, x + 10, y + 19);
  glRectd(x + 10, y + 17, x + 11, y + 18);

  x += 16;
}

// Drawing of the cloud end part
void cloud_end(double x, double y, bool cloud) {
  glColor3ub(BLACK);
  glRectd(x, y + 2, x + 1, y + 3);
  glRectd(x + 1, y + 1, x + 3, y + 2);
  glRectd(x + 3, y + 2, x + 5, y + 3);
  glRectd(x + 5, y + 3, x + 7, y + 4);
  glRectd(x + 7, y + 5, x + 8, y + 6);
  glRectd(x + 6, y + 6, x + 7, y + 7);
  glRectd(x + 5, y + 7, x + 6, y + 8);
  glRectd(x + 6, y + 8, x + 7, y + 9);
  glRectd(x + 7, y + 9, x + 8, y + 12);
  glRectd(x + 6, y + 12, x + 7, y + 13);
  glRectd(x + 5, y + 11, x + 6, y + 12);
  glRectd(x + 4, y + 12, x + 5, y + 15);
  glRectd(x + 3, y + 15, x + 4, y + 16);
  glRectd(x + 2, y + 14, x + 3, y + 15);
  glRectd(x + 1, y + 13, x + 2, y + 14);
  glRectd(x, y + 14, x + 1, y + 16);

  cloud ? glColor3ub(CLOUD_WHITE) : glColor3ub(BUSH_GREEN);
  glRectd(x, y + 3, x + 1, y + 14);
  glRectd(x + 1, y + 2, x + 2, y + 13);
  glRectd(x + 2, y + 2, x + 3, y + 14);
  glRectd(x + 3, y + 3, x + 4, y + 15);
  glRectd(x + 4, y + 3, x + 5, y + 12);
  glRectd(x + 5, y + 4, x + 6, y + 7);
  glRectd(x + 6, y + 4, x + 7, y + 6);
  glRectd(x + 5, y + 8, x + 6, y + 11);
  glRectd(x + 6, y + 9, x + 7, y + 12);
}

// Cloud or Bush, reptitions decide how long the drawing will be
void draw_fuzz(double x, double y, int repitions, bool cloud) {
  cloud_start(x, y, cloud);
  while (repitions--) {
    cloud_mid(x, y, cloud);
  }
  cloud_end(x, y, cloud);
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  // Background done using a rectangle to use HEX colors (The other way doesn't
  // allow for colors)
  glColor3ub(SKY_BLUE);
  glRectd(0, 0, 383, 255);

  // Clouds
  draw_fuzz(cloudA1, 200, 3, true);
  draw_fuzz(cloudA2, 100, 1, true);
  draw_fuzz(cloudA3, 225, 1, true);

  // Bush
  draw_fuzz(9 * B_SIZE, B_SIZE + 8, 3, false);

  // Mushrooms

  level1.render();

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

  cloudA1 < 400 ? cloudA1 += 0.1 : cloudA1 = -100;
  cloudA2 < 400 ? cloudA2 += 0.2 : cloudA2 = -100;
  cloudA3 < 400 ? cloudA3 += 0.1 : cloudA3 = -100;

  if (upPressed && onGround) moveStateY = 10.0;
  offset = playerX;

  playerX += 0.2 * moveStateX;

  level1.edit_player(playerX, playerY);

  if (level1.right_coll()) {
    moveStateX = 0;
    playerX = ceil(playerX);
    level1.edit_player(playerX, playerY);
    printf("RIGHT COLLISION: PLAYER X = %d\n", (int)playerX);

    while (level1.right_coll()) {
      playerX -= 1;
      level1.edit_player(playerX, playerY);
    }
  } else if (level1.left_coll()) {
    moveStateX = 0;
    playerX = floor(playerX);
    level1.edit_player(playerX, playerY);
    printf("LEFT COLLISION: PLAYER X = %d\n", (int)playerX);

    while (level1.left_coll()) {
      playerX += 1;
      level1.edit_player(playerX, playerY);
    }
  }

  if ((!rightPressed && !leftPressed || leftPressed && rightPressed) &&
      moveStateX != 0) {
    moveStateX = moveStateX > 0 ? max(moveStateX - 0.5, 0.0)
                                : min(moveStateX + 0.5, 0.0);
  } else if (rightPressed && !level1.future_right_coll()) {
    moveStateX = min(moveStateX + 0.5, 10.0);
    level1.set_player_state(runRight1);
  } else if (leftPressed && !level1.future_left_coll()) {
    moveStateX = max(moveStateX - 0.6, -10.0);
    level1.set_player_state(runLeft1);
  } else {
    level1.set_player_state(stopped);
  }

  playerY += 0.3 * moveStateY;
  level1.edit_player(playerX, playerY);

  if (level1.ground_coll()) {
    moveStateY = 0;
    onGround = true;
    playerY = ceil(playerY);
    level1.edit_player(playerX, playerY);
    printf("GROUND COLLISION: PLAYER Y = %d\n", (int)playerY);
    while (level1.ground_coll()) {
      playerY += 1;
      level1.edit_player(playerX, playerY);
    }
  } else if (level1.upward_coll()) {
    moveStateY = 0;
    playerY = floor(playerY);
    level1.edit_player(playerX, playerY);
    printf("UP COLLISION: PLAYER Y = %d\n", (int)playerY);
    while (level1.upward_coll()) {
      playerY -= 1;
      level1.edit_player(playerX, playerY);
    }
  }

  if (!level1.future_ground_coll()) {
    onGround = 0;
  }

  if (!onGround) {
    moveStateY = max(moveStateY - 0.2, -10.0);
  }

  centered |= playerX > 186 && playerX < 189;

  if(offset - playerX > 0){
    centered &= level1.check_left_border();
  }
  else{
    centered &= level1.check_right_border();
  }

  if (centered) {
    printf("centered ?\n");
    level1.move_objects(offset - playerX);
    playerX = offset;
    level1.edit_player(playerX, playerY);
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

  for (int i = -8, j = 0; j < 50; i += B_SIZE, j++) {
    level1.add_block(new SurfaceBlock(i, B_SIZE * 0));
    level1.add_block(new SurfaceBlock(i, B_SIZE * 1));
  }

  level1.add_block(new LuckyBlock(10 * B_SIZE - 8, B_SIZE * 5));

  level1.add_block(new SurfacePlatformBlock(18 * B_SIZE - 8, 5 * B_SIZE));
  level1.add_block(new LuckyBlock(19 * B_SIZE - 8, 5 * B_SIZE));
  level1.add_block(new SurfacePlatformBlock(20 * B_SIZE - 8, 5 * B_SIZE));
  level1.add_block(new LuckyBlock(21 * B_SIZE - 8, 5 * B_SIZE));
  level1.add_block(new SurfacePlatformBlock(22 * B_SIZE - 8, 5 * B_SIZE));

  level1.add_block(new LuckyBlock(20 * B_SIZE - 8, 9 * B_SIZE));

  level1.set_player(new Player(playerX, playerY));

  level1.add_scenery(new Star(10 * B_SIZE, 6 * B_SIZE + 8, 3, 0));
  level1.add_bg_scenery(new Hill(21, 2 * B_SIZE));
  level1.add_bg_scenery(new Hill(235, B_SIZE));

  glutMainLoop();

  return 0;
}
