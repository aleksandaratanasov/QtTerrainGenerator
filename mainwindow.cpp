#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->myGLWidget, SIGNAL(statusChanged(QString)),this, SLOT(setStatus(QString)));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_actionClose_triggered() {
  this->close();
}

void MainWindow::setStatus(QString statusMsg) {
  ui->statusBar->showMessage(statusMsg);
}
