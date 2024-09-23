// Defines the Renderable class that most game entities and blocks are based on
#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>



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
