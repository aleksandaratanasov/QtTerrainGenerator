#include "GLWidget.h"
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

  toggleTranslation = false;

  xRot = 0;
  yRot = 0;
  zRot = 0;

  xTrans = 0.0;
  yTrans = 0.0;
  zZoom = -2.0;

  status = "Initialization done";
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
  glTranslatef(xTrans, yTrans, zZoom);
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
    setStatus("Wireframe on");
  }
  else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    setStatus("Wireframe off");
  }
  updateGL();
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
//  std::cout << "Mouse pressed\t [" << event->x() << "," << event->y() << "]" << std::endl;
  lastPos = event->pos();

  if(event->buttons() & Qt::MiddleButton) {
    toggleTranslation = true;
  }
  else
    toggleTranslation = false;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
//  std::cout << "Mouse moved" << std::endl;
  // Size of dx and dy represent the speed of movement along the respective axis
  int dx = event->x() - lastPos.x();
  int dy = event->y() - lastPos.y();

  if(event->buttons() & Qt::LeftButton) {
    setXRotation(xRot + 8 * dy);
    setYRotation(yRot + 8 * dx);
  }
  else if (event->buttons() & Qt::RightButton) {
    setXRotation(xRot + 8 * dy);
    setZRotation(zRot + 8 * dx);
  }

  lastPos = event->pos();

  if(toggleTranslation) {
    // Translate camera horizontally and vertically here
    std::cout << "Translation activated: moving camera..." << std::endl;
    std::cout << "X: " << dx << " | Y: " << dy << std::endl;
    setVerticalTranslation(dy);
    setHorizontalTranslation(dx);
  }
}

void GLWidget::wheelEvent(QWheelEvent *event) {
  int numDegrees = event->delta() / 8;
  int numSteps = numDegrees / 15; // Usually numSteps here is declared outside the function and is used for tracking the number of steps
                                  // the wheel has been rolled. However here we use it only to determine the direction of the scroll of the wheel

  if(numSteps == 1) zZoom += .01;
  else if (numSteps == -1) zZoom -= .01;

  setZoom(numSteps);

  if((event->buttons() & Qt::MiddleButton) != 0) {
    std::cout << "MouseWheelEven: wheel pressed" << std::endl;
  }
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

void GLWidget::setVerticalTranslation(int y)
{
  // Covers both positive and negative values for y
  // The multiplication with -1 inverts the movement so that moving the mouse cursor upwards translates upwards
  // The factor .01 seems to offer very smooth yet fast enough movement
  yTrans += .01 * y * (-1);
  setStatus("Translation along y axis with " + QString::number(yTrans, 'g', 3));
  emit yTranslationChanged(yTrans);
  updateGL();
}

void GLWidget::setHorizontalTranslation(int x)
{
  // Covers both positive and negative values for x
  // The factor .01 seems to offer very smooth yet fast enough movement
  xTrans += .01 * x;
  setStatus("Translation along x axis with " + QString::number(xTrans, 'g', 3));
  emit xTranslationChanged(xTrans);
  updateGL();
}

void GLWidget::setZoom(int zoomDirection) {
  // We increase the Z distance (the axis which points outwards the scene in the direction of the user)
  // based on the direction
  if(zoomDirection == 1) zoomIn();
  else if (zoomDirection == -1) zoomOut();
}

void GLWidget::zoomIn() {
  zZoom += .1;
  setStatus("Zoom in to " + QString::number(zZoom, 'g', 3));
  emit zTranslationChanged(zZoom);
  updateGL();
}

void GLWidget::zoomOut() {
  zZoom -= .1;
  setStatus("Zoom out to " + QString::number(zZoom, 'g', 3));
  emit zTranslationChanged(zZoom);
  updateGL();
}

void GLWidget::resetZoom() {
  zZoom = -2.0;
  setStatus("Zoom level reset to " + QString::number(zZoom, 'g', 3));
  updateGL();
}

void GLWidget::setStatus(QString statusMsg) {
  status = statusMsg;
  emit statusChanged(status);
}

void GLWidget::toggleTerrain(bool flag) {
  toggleTerrainF = flag;
}

void GLWidget::togglePlants(bool flag) {
  togglePlantsF = flag;
  //setStatus("Rendering plants is " + (QString)(flag ? "on" : "off"));
}

void GLWidget::toggleWater(bool flag) {
  toggleWaterF = flag;
  //setStatus("Rendering water is " + (QString)(flag ? "on" : "off"));
}

void GLWidget::toggleLight(bool flag) {
  toggleLightF = flag;
  //setStatus("Rendering complex light is " + (QString)(flag ? "on" : "off"));
}
