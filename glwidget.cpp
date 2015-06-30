#include "glwidget.h"
#include <QMouseEvent>
#include <GL/glut.h>
#include <iostream>
#include <math.h>

GLfloat treeRatio = .5;

static void normalizeAngle(int &angle)
{
  while (angle < 0)
    angle += 360 * 16;
  while (angle > 360)
    angle -= 360 * 16;
}

GLWidget::GLWidget(QWidget *parent) :
  QGLWidget(parent)
{
//  connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
//  timer.start(16);
  toggleWireframeFlag = false;
  xRot = 0;
  yRot = 0;
  zRot = 0;
  zZoom = -2.0;
}

void GLWidget::initializeGL() {
  glClearColor(.2, .2, .2, 1);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

//  static GLfloat lightPosition[4] = { 0, 0, 2, 1.0 };
//  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void GLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//  glRotatef(.5, 1, 1, 1);
  glLoadIdentity();
  //glTranslatef(0.0, 0.0, -2.0);
  glTranslatef(0., 0., zZoom);
  glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
  glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
  glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

  glutSolidTeapot(.6);
}

void GLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, (float)w/h, .01, 100.);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 0, 5,
            0, 0, 0,
            0, 1, 0);
}

void GLWidget::toggleWireframe(bool checked) {
  toggleWireframeFlag = checked;

  if(checked) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    std::cout << "[INFO]: Wireframe ON" << std::endl;
  }
  else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    std::cout << "[INFO]: Wireframe OFF" << std::endl;
  }

  updateGL();
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
//  std::cout << "Mouse pressed\t [" << event->x() << "," << event->y() << "]" << std::endl;
  lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
//  std::cout << "Mouse moved" << std::endl;
  int dx = event->x() - lastPos.x();
  int dy = event->y() - lastPos.y();

  if (event->buttons() & Qt::LeftButton) {
    setXRotation(xRot + 8 * dy);
    setYRotation(yRot + 8 * dx);
  } else if (event->buttons() & Qt::RightButton) {
    setXRotation(xRot + 8 * dy);
    setZRotation(zRot + 8 * dx);
  }

  lastPos = event->pos();
}

void GLWidget::wheelEvent(QWheelEvent *event) {
  int numDegrees = event->delta() / 8;
  int numSteps = numDegrees / 15; // Usually numSteps here is declared outside the function and is used for tracking the number of steps
                                  // the wheel has been rolled. However here we use it only to determine the direction of the scroll of the wheel

  if(numSteps == 1) zZoom += .01;
  else if (numSteps == -1) zZoom -= .01;

  setZoom(numSteps);
}

void GLWidget::setXRotation(int angle)
{
  normalizeAngle(angle);
  if (angle != xRot) {
    xRot = angle;
    emit xRotationChanged(angle);
    updateGL();
  }
}

void GLWidget::setYRotation(int angle)
{
  normalizeAngle(angle);
  if (angle != yRot) {
    yRot = angle;
    emit yRotationChanged(angle);
    updateGL();
  }
}

void GLWidget::setZRotation(int angle)
{
  normalizeAngle(angle);
  if (angle != zRot) {
    zRot = angle;
    emit zRotationChanged(angle);
    updateGL();
  }
}

void GLWidget::setZoom(int zoomDirection) {

  // We increase the Z distance (the axis which points outwards the scene in the direction of the user)
  // based on the direction
  if(zoomDirection == 1) zZoom += .1;
  else if (zoomDirection == -1) zZoom -= .1;

    std::cout << "[INFO] Changing zoom level : " << zZoom << std::endl;

  updateGL();
}

void GLWidget::resetZoom() {
  std::cout << "[INFO] Zoom level reset" << std::endl;
  zZoom = -2.0;
  updateGL();
}
