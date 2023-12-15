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
