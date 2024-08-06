#ifndef PAINTER_H
#define PAINTER_H

#include <QPainter>
#include <QWidget>

#include "../controller.h"

class Painter : public QWidget {
  Q_OBJECT
 public:
  explicit Painter(QWidget *parent = nullptr);
  s21::Controller controller;

 protected:
  void paintEvent(QPaintEvent *event) override;
};

#endif  // PAINTER_H
