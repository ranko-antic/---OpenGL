#pragma once

#include <GL/glut.h>
#include <iostream>

#include "finger.hpp"
#include "material.hpp"
#include "model.hpp"

class Hand {
  public:
  Hand() { material_ = Material(); }

  void setAngles(float* angles) { angles_ = angles; }
  void setFingers(Finger fingers[5]) { fingers_ = fingers; }
  void setPalm(float size) { palm_ = Model(size); }

  void draw(void) {
    material_.setHandMaterial();
    material_.handTexture();
    drawFingers();
    drawPalm();
  }

  private:
  float* angles_;
  Finger* fingers_;
  Material material_;
  Model palm_;

  void drawFingers(void) {
    for (int i = 0; i < 5; ++i) {
      fingers_[i].setHandBendingAngles(angles_);
      fingers_[i].draw();
    }
  }

  void drawPalm(void) {
    glPushMatrix();
    glScalef(1.0, 1.0, 0.15);
    palm_.draw();
    glPopMatrix();
  }
};

