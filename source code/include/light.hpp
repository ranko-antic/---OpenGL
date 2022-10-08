#pragma once

#include <GL/glut.h>
#include <iostream>

class Light {
  public:
  Light(int light) { light_ = light; }

  void setPosition(float* light_position) { position_ = light_position; }
  void setColor(float* diffuseColor, float* specularColor) {
    diffuse_ = diffuseColor;
    specular_ = specularColor;
  }

  void draw(void) {
    glLightfv(light_, GL_POSITION, position_);
    glLightfv(light_, GL_DIFFUSE, diffuse_);
    glLightfv(light_, GL_SPECULAR, specular_);

    glEnable(GL_LIGHTING);
    glEnable(light_);
    glEnable(GL_DEPTH_TEST);
  }

  private:
  int light_;
  float* diffuse_;
  float* position_;
  float* specular_;
};
