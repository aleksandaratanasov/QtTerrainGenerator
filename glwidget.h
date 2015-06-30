#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>

class GLWidget : public QGLWidget
{
  Q_OBJECT

private:
  QTimer timer;

  bool toggleWireframeFlag;

  int xRot;
  int yRot;
  int zRot;
  QPoint lastPos;
  float zZoom;

public:
  explicit GLWidget(QWidget *parent = 0);

  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);

  // Mouse control of the content displayed in the widget
  // http://www.bogotobogo.com/Qt/Qt5_OpenGL_QGLWidget.php
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);

  // Rotate around x, y and z axes using scrollbars
  void setXRotation(int angle);
  void setYRotation(int angle);
  void setZRotation(int angle);
  void setZoom(int zoomDirection);

public slots:
  void toggleWireframe(bool checked);
  void resetZoom();

signals:
  // Rotate around x, y and z axes using mouse
  void xRotationChanged(int angle);
  void yRotationChanged(int angle);
  void zRotationChanged(int angle);
};

#endif // GLWIDGET_H
