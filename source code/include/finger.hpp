#pragma once

#include <GL/glut.h>
#include <iostream>

#include "material.hpp"
#include "model.hpp"

class Finger {
  public:
  Finger() = default;
  Finger(float* position, float model_size) {
    position_ = position;
    size_ = model_size;
    box_ = Model(size_);
    material_ = Material();
  }

  void setHandBendingAngles(float* flexing_angle) { angle_ = flexing_angle; }

  void drawPalac(void) {
    glPushMatrix();

    glScalef(0.8, 1.47, 0.6);

    glTranslatef(3.8, -1.1, 0);
    glRotatef(-angle_[1], 0, 1, 0);
    glTranslatef(0, 0, angle_[1] * 0.01);
    box_.draw();

    drawJoint(0.1, 0.0, 0.0, 1.0);

    glTranslatef(size_ + 0.18, 0, 0);
    glRotatef(-angle_[1], 0, 1, 0);
    glTranslatef(0, 0, angle_[1] * 0.007);
    box_.draw();

    glPopMatrix();
  }

  void draw(void) {
    if (size_ != 1.0) {
      drawPalac();
      return;
    }

    glPushMatrix();

    glScalef(0.8, 1.47, 0.6);

    glTranslatef(position_[0], position_[1], position_[2]);
    glRotatef(angle_[0], 1, 0, 0);
    glTranslatef(0, angle_[0] * 0.01, angle_[0] * 0.01);
    box_.draw();

    drawJoint(0.0, 0.6, 0.0, 2.0);

    glTranslatef(0, size_ + 0.13, 0);
    glRotatef(angle_[1], 1, 0, 0);
    glTranslatef(0, angle_[1] * 0.005, angle_[1] * 0.007);
    box_.draw();

    drawJoint(0.0, 0.6, 0.0, 2.0);

    glTranslatef(0, size_ + 0.1, 0);
    glRotatef(angle_[2], 1, 0, 0);
    glTranslatef(0, angle_[2] * 0.005, angle_[2] * 0.007);
    box_.draw();

    glPopMatrix();
  }

  private:
  float* angle_;
  float* position_;
  float size_;
  Model box_;
  Material material_;

  void drawJoint(GLfloat dx, GLfloat dy, GLfloat dz, GLfloat sz) {
    material_.setJointMaterial();

    glPushMatrix();
    glScalef(3.5, 1.0, sz);
    glTranslatef(dx, dy, dz);
    glutSolidSphere(0.2, 10, 10);
    glPopMatrix();

    material_.setHandMaterial();
  }
};
