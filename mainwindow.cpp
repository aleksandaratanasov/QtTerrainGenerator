#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->myGLWidget, SIGNAL(statusChanged(QString)),this, SLOT(setStatus(QString)));
  about.setText("QtTerrainGenerator v0.0.1");
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_actionClose_triggered() {
  this->close();
}

void MainWindow::on_actionAbout_triggered() {
  this->about.exec();
}

void MainWindow::on_actionLoad_terrain_triggered() {
  //emit singal with TERRAIN OBJECT and send it to the GLWidget
  QString terrainFilename = QFileDialog::getOpenFileName(this, tr("Load terrain"), "", tr("Collada (*.dae);;STereoLithography (*.stl);;Wavefront (*.obj);;All supported (*.dae, *.stl, *.obj)"));
  if(terrainFilename.isEmpty()) {
    setStatus("Error opening file");
    return;
  }

  setStatus("Opening file \"" + terrainFilename + "\"...");

  // Parse file in a separate thread!
  // Attach progressbar to statusbar for visualizing the loading and parsing progress

}

void MainWindow::setStatus(QString statusMsg) {
  ui->statusBar->showMessage(statusMsg);
}
