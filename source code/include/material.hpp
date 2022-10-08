#pragma once

#include <GL/glut.h>
#include <iostream>

#include "pinocchio.c"

class Material {
  public:
  void setHandMaterial() {
    GLfloat ambient[] = {1.0, 0.8, 0.5, 1.0};
    GLfloat diffuse[] = {1.0, 0.8, 0.5, 1.0};
    GLfloat specular[] = {1.0, 0.8, 0.5, 1.0};
    GLfloat shininess[] = {100.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  }
  void setJointMaterial() {
    GLfloat diffuse[] = {1.0, 0.4, 0.7, 1.0};
    GLfloat specular[] = {1.0, 0.4, 0.7, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  }

  void handTexture() {
    GLuint texturePot = 0;

    glGenTextures(1, &texturePot);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturePot);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, gimp_image.width, gimp_image.height,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, gimp_image.pixel_data);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  }
};
