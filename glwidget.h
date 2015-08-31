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
  QString status; // TODO Display widget status in the statusbar of MainWindow

  bool toggleTerrainF, togglePlantsF, toggleWaterF, toggleLightF;

public:
  explicit GLWidget(QWidget *parent = 0);

private:
  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);

  // Mouse control of the content displayed in the widget: http://www.bogotobogo.com/Qt/Qt5_OpenGL_QGLWidget.php
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);

  // Rotate around x, y and z axes using scrollbars
  void setXRotation(int angle);
  void setYRotation(int angle);
  void setZRotation(int angle);
  void setZoom(int zoomDirection);
//  void setStatus(QString statusMsg);  // moved to public slots

public slots:
  void toggleWireframe(bool checked);
  void resetZoom();
  void zoomIn();
  void zoomOut();
  void setStatus(QString statusMsg);

  // Using the checkboxes in the Display tab of the QTabWidget in MainWindow
  // various parts can be stopped from being rendered and even generated (water, plants)
  void toggleTerrain(bool flag);
  void togglePlants(bool flag);
  void toggleWater(bool flag);
  void toggleLight(bool flag);

signals:
  // Rotate around x, y and z axes using mouse
  void xRotationChanged(int angle);
  void yRotationChanged(int angle);
  void zRotationChanged(int angle);
  void statusChanged(QString statusMsg);
};

#endif // GLWIDGET_H
