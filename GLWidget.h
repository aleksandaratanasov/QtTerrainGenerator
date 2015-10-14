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

  bool toggleTranslation;
  int xRot;
  int yRot;
  int zRot;
  QPoint lastPos;
  float xTrans;
  float yTrans;
  float zZoom;  // zTrans
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

  // Rotation
  void setXRotation(int angle);
  void setYRotation(int angle);
  void setZRotation(int angle);

  // Translation
  void setVerticalTranslation(int speed);   // Up/Down
  void setHorizontalTranslation(int speed); // Left/Right
  void setZoom(int zoomDirection);          // Nearer/Closer to viewer
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
  // Translate along x, y and z (zoom) axes using the mouse
  void xTranslationChanged(int x);
  void yTranslationChanged(int y);
  void zTranslationChanged(float z);
  // Statusbar updates
  void statusChanged(QString statusMsg);
};

#endif // GLWIDGET_H
