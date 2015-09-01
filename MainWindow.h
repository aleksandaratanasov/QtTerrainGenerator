#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
  class MainWindow;
  }

  class MainWindow : public QMainWindow
  {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private slots:
    void on_actionClose_triggered();
    void on_actionAbout_triggered();
    void on_actionLoad_terrain_triggered();
    void setStatus(QString statusMsg);

  private:
    Ui::MainWindow *ui;
    QMessageBox about;
};

#endif // MAINWINDOW_H
