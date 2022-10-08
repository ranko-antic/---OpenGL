#pragma once

#include <GL/glut.h>
#include <iostream>

class Camera {
  public:
  void setPosition(float* camera_position) { position_ = camera_position; }
  void setTarget(float* camera_target) { target_ = camera_target; }
  void setClippingPlanes(float left, float right, float bottom, float top,
                         float nearVal, float farVal) {
    leftClip_ = left;
    rightClip_ = right;
    bottomClip_ = bottom;
    topClip_ = top;
    nearClip_ = nearVal;
    farClip_ = farVal;
  }

  void draw(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(leftClip_, rightClip_, bottomClip_, topClip_, nearClip_,
              farClip_);
    gluLookAt(*position_, *(position_ + 1), *(position_ + 2), *target_,
              *(target_ + 1), *(target_ + 2), 0, 1, 0);
  }

  private:
  float* position_;
  float* target_;
  float leftClip_, rightClip_, bottomClip_, topClip_, nearClip_, farClip_;
};
