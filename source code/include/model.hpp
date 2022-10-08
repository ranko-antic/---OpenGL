#pragma once

#include <GL/glut.h>
#include <iostream>

class Model {
  public:
  Model() = default;
  Model(float size) { size_ = size; }

  void draw(void) { glutSolidCube(size_); }

  private:
  float size_;
};
