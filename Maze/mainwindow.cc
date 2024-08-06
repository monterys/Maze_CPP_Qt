#include "mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <iostream>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_open_clicked() {
  //      QString path = QFileDialog::getOpenFileName(this, "Open maze", "",
  //      "*.mz *.txt",0,QFileDialog::DontUseNativeDialog);
  QString path =
      QFileDialog::getOpenFileName(this, "Open maze", "", "*.mz *.txt");
  if (path != nullptr) {
    try {
      ui->widget->controller.ReadMaze(path);

      int rows = ui->widget->controller.Rows();
      int cols = ui->widget->controller.Cols();
      ui->spinBox_from_row->setMaximum(rows);
      ui->spinBox_to_row->setMaximum(rows);
      ui->spinBox_from_col->setMaximum(cols);
      ui->spinBox_to_col->setMaximum(cols);

      ui->pushButton_path->setEnabled(true);
    } catch (const char* s) {
      QMessageBox box(this);
      box.setWindowTitle("Error");
      box.setText(QString::fromLocal8Bit(s));
      box.exec();
    } catch (std::exception e) {
      QMessageBox box(this);
      box.setWindowTitle("Error");
      box.setText("Invalid file format");
      box.exec();
    }
  }
}

void MainWindow::on_pushButton_eller_clicked() {
  int rows = ui->spinBox_rows->value();
  int cols = ui->spinBox_cols->value();
  try {
    ui->widget->controller.Eller(rows, cols);

    rows = ui->widget->controller.Rows();
    cols = ui->widget->controller.Cols();
    ui->spinBox_from_row->setMaximum(rows);
    ui->spinBox_to_row->setMaximum(rows);
    ui->spinBox_from_col->setMaximum(cols);
    ui->spinBox_to_col->setMaximum(cols);

    ui->pushButton_path->setEnabled(true);
  } catch (...) {
    QMessageBox box(this);
    box.setWindowTitle("Error");
    box.setText("Error");
    box.exec();
  }
}

void MainWindow::on_pushButton_path_clicked() {
  int from_row = ui->spinBox_from_row->value();
  int from_col = ui->spinBox_from_col->value();
  int to_row = ui->spinBox_to_row->value();
  int to_col = ui->spinBox_to_col->value();
  std::vector<int> path;
  try {
    ui->widget->controller.GeneratePath(from_col - 1, from_row - 1, to_col - 1,
                                        to_row - 1);
    auto path = ui->widget->controller.GetPath();
  } catch (...) {
    QMessageBox box(this);
    box.setWindowTitle("Error");
    box.setText("Path not found");
    box.exec();
  }
}
