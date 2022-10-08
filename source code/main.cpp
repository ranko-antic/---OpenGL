#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>

#include "include/camera.hpp"
#include "include/finger.hpp"
#include "include/hand.hpp"
#include "include/light.hpp"
#include "include/model.hpp"

GLint light = 1;
GLint rotation_flag = 0;
GLfloat angle_1 = 0.0f;
GLfloat angle_2 = 0.0f;
GLfloat angle_3 = 0.0f;
GLfloat rotation_angle = 0.0f;

class Animation {
  public:
  void closeHand() {
    if (angle_1 < 75.0) {
      angle_1 += 1.8;
    }
    if (angle_2 < 75.0) {
      angle_2 += 1.3;
    }
    if (angle_3 < 75.0) {
      angle_3 += 1.3;
    }
  }

  void openHand() {
    if (angle_1 > 0.0) {
      angle_1 -= 1.8;
    }
    if (angle_2 > 0.0) {
      angle_2 -= 1.3;
    }
    if (angle_3 > 0.0) {
      angle_3 -= 1.3;
    }
  }

  void toggleRotation() { rotation_flag ^= 1; }
};
Animation angularHandTransformation;

void init(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);

  Camera camera;
  float camera_position[] = {0.0, 0.0, 13.0};
  float camera_target[] = {0.0, 0.0, 0.0};
  camera.setClippingPlanes(-5.0, 5.0, -5.0, 5.0, 5.0, 18.0);
  camera.setPosition(camera_position);
  camera.setTarget(camera_target);
  camera.draw();

  Light light = Light(GL_LIGHT0);
  float light_position[] = {-10.0, -3.0, 3.0, 0.0};
  float diffuseColor[] = {1.0, 1.0, 1.0, 1.0};
  float specularColor[] = {1.0, 0.4, 0.7, 1.0};
  light.setPosition(light_position);
  light.setColor(diffuseColor, specularColor);
  light.draw();

  light = Light(GL_LIGHT1);
  float lightPosition[] = {10.0, 3.0, 3.0, 0.0};
  light.setPosition(lightPosition);
  light.setColor(diffuseColor, specularColor);
  light.draw();
}

void animation(void) {
  if (rotation_flag != 0) {
    rotation_angle = (rotation_angle > 360.0) ? 0.0 : rotation_angle + 0.05;
    glutPostRedisplay();
  }
}

void display() {
  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glRotatef(rotation_angle, 0.0, 1.0, 0.0);

  Hand hand;

  float angles[] = {angle_1, angle_2, angle_3};

  float position_1[] = {-2.5, 2.2, 0.0};
  Finger littleFinger = Finger(position_1, 1.0);
  float position_2[] = {-0.8, 2.2, 0.0};
  Finger ringFinger = Finger(position_2, 1.0);
  float position_3[] = {0.8, 2.2, 0.0};
  Finger middleFinger = Finger(position_3, 1.0);
  float position_4[] = {2.5, 2.2, 0.0};
  Finger indexFinger = Finger(position_4, 1.0);
  float position_5[] = {3.8, -1.2, 0.0};
  Finger Palac = Finger(position_5, 1.1);
  Finger fingers[] = {littleFinger, ringFinger, middleFinger, indexFinger,
                      Palac};

  hand.setFingers(fingers);
  hand.setPalm(5.0);
  hand.setAngles(angles);
  hand.draw();

  glFlush();
}

void keyboard(unsigned char key, int x, int y) {
  std::cout << "Keyboard callback:\n\t"
               "\t1) '13 -> Enter (Carriage return)' == CLOSE Your Hand;\n\t"
               "\t2) '32 -> Space' == CLOSE Your Hand;\n\t"
               "\t3) '8 -> Backspace' == OPEN Your Hand;\n\t"
               "\t4) 'R' == START or STOP Hand Rotation (counterclockwise);\n\t"
               "\t5) 'r' == START or STOP Hand Rotation (counterclockwise);\n\t"
               "\t6) '27 -> Esc' == Window->closed && Process->terminated.\t"
            << std::endl;
  switch (key) {
    case 13:
    case 32:
      angularHandTransformation.closeHand();
      std::cout << "You pressed 'Enter' or 'Space' key to CLOSE Your Hand!"
                << std::endl;
      break;
    case 8:
      angularHandTransformation.openHand();
      std::cout << "You pressed 'Backspace' key to OPEN Your Hand!"
                << std::endl;
      break;
    case 'R':
    case 'r':
      angularHandTransformation.toggleRotation();
      if (rotation_flag == 1) {
        std::cout << "You pressed 'R' or 'r' key to START Hand Rotation "
                     "(counterclockwise)!"
                  << std::endl;
      } else {
        std::cout << "You pressed 'R' or 'r' key to STOP Hand Rotation "
                     "(counterclockwise)!"
                  << std::endl;
      }
      break;
    case 27:
      std::cout << "You pressed 'Esc' key to kill the process!" << std::endl;
      exit(0);
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    light = light % 2;
    if (light != 0) {
      glDisable(GL_LIGHT0);
      glDisable(GL_LIGHT1);
    } else {
      glEnable(GL_LIGHT0);
      glEnable(GL_LIGHT1);
    }
    ++light;
  }
  glutPostRedisplay();
}

void reshape(int width, int height) {
  Camera camera;
  float camera_position[] = {0.0, 0.0, 13.0};
  float camera_target[] = {0.0, 0.0, 0.0};
  camera.setClippingPlanes(-5.0, 5.0, -5.0, 5.0, 5.0, 18.0);
  camera.setPosition(camera_position);
  camera.setTarget(camera_target);
  camera.draw();
}

void specialKeys(int key, int x, int y) {
  std::cout << "Special keyboard callback:\n\t"
               "\t1) 'Left Arrow (Home)' ==  RETURN Your Hand to its initial "
               "Position;\n\t"
               "\t2) 'Right Arrow (End)' == START or STOP Hand Rotation "
               "(counterclockwise);\n\t"
               "\t3) 'Down Arrow (PgDn)' == CLOSE Your Hand;\n\t"
               "\t4) 'Up Arrow (PgUp)' == OPEN Your Hand.\t"
            << std::endl;
  switch (key) {
    case GLUT_KEY_LEFT:
      rotation_angle = (rotation_angle > 360.0) ? rotation_angle - 0.05 : 0.0;
      glutPostRedisplay();
      std::cout << "You pressed 'Left Arrow' key to "
                   "RETURN Your Hand to its initial Position!"
                << std::endl;
      break;
    case GLUT_KEY_RIGHT:
      angularHandTransformation.toggleRotation();
      if (rotation_flag == 1) {
        std::cout << "You pressed 'Right Arrow' key to START Hand Rotation "
                     "(counterclockwise)!"
                  << std::endl;
      } else {
        std::cout << "You pressed 'Right Arrow' key to STOP Hand Rotation "
                     "(counterclockwise)!"
                  << std::endl;
      }
      break;
    case GLUT_KEY_DOWN:
      angularHandTransformation.closeHand();
      std::cout << "You pressed 'Down Arrow' key to "
                   "CLOSE Your Hand!"
                << std::endl;
      break;
    case GLUT_KEY_UP:
      angularHandTransformation.openHand();
      std::cout << "You pressed 'Up Arrow' key to "
                   "OPEN Your Hand!"
                << std::endl;
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(1000, 900);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("Final Project: 3D Joint Object - Hand");

  init();

  glutIdleFunc(animation);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutReshapeFunc(reshape);
  glutSpecialFunc(specialKeys);
  glutMainLoop();

  return 0;
}
