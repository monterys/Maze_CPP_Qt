#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

#include "painter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_open_clicked();

  void on_pushButton_eller_clicked();

  void on_pushButton_path_clicked();

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
