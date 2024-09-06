#ifndef WINDOWX_H
#define WINDOWX_H

#include <qcustomplot.h>

#include <QMainWindow>

#include "mainwindow.h"

namespace Ui {
class windowX;
}

class windowX : public QMainWindow {
  Q_OBJECT

 public:
  explicit windowX(QWidget *parent = nullptr);
  ~windowX();

 private:
  Ui::windowX *ui;
};

#endif  // WINDOWX_H
