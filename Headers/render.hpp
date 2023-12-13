// Defines the Renderable class that most game entities and blocks are based on
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
#include <cmath>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

class Renderable {
  virtual void render() = 0;
};
