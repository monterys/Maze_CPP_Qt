#include "painter.h"

#include <QFileDialog>
#include <QPainter>
#include <iostream>

#include "../maze.h"

Painter::Painter(QWidget *parent) : QWidget{parent} {}

void Painter::paintEvent(QPaintEvent *) {
  setBackgroundRole(QPalette::Dark);
  setAutoFillBackground(true);

  QPainter painter(this);
  if (controller.Rows() && controller.Cols()) {
    setBackgroundRole(QPalette::Highlight);
    QPen penBlack(Qt::black);
    penBlack.setWidth(2);
    painter.setPen(penBlack);
    painter.drawRect(25, 25, 500, 500);

    size_t cell_width = 500 / controller.Cols();
    size_t cell_height = 500 / controller.Rows();

    for (int i = 0; i < controller.Rows(); ++i) {
      for (int j = 0; j < controller.Cols() - 1; ++j) {
        if (controller(s21::Maze::Vh::kVertical, i, j)) {
          size_t x1 = 25 + (j + 1) * cell_width;
          size_t y1 = 25 + i * cell_height;
          size_t x2 = 25 + (j + 1) * cell_width;
          size_t y2 = 25 + (i + 1) * cell_height;
          painter.drawLine(x1, y1, x2, y2);
        }
      }
    }
    for (int i = 0; i < controller.Rows() - 1; ++i) {
      for (int j = 0; j < controller.Cols(); ++j) {
        if (controller(s21::Maze::Vh::kHorizontal, i, j)) {
          size_t x1 = 25 + j * cell_width;
          size_t y1 = 25 + (i + 1) * cell_height;
          size_t x2 = 25 + (j + 1) * cell_width;
          size_t y2 = 25 + (i + 1) * cell_height;
          painter.drawLine(x1, y1, x2, y2);
        }
      }
    }
    std::vector<int> path = controller.GetPath();
    if (!path.empty()) {
      QPen penRed(Qt::red);
      penRed.setWidth(2);
      painter.setPen(penRed);

      for (size_t i = 0; i < path.size() - 2; ++i) {
        int from_col = 25 + (path[i] + 1) * cell_width - cell_width / 2;
        int from_row = 25 + (path[++i] + 1) * cell_height - cell_height / 2;
        int to_col = 25 + (path[i + 1] + 1) * cell_width - cell_width / 2;
        int to_row = 25 + (path[i + 2] + 1) * cell_height - cell_height / 2;
        painter.drawLine(from_col, from_row, to_col, to_row);
      }
    }
  }
}
