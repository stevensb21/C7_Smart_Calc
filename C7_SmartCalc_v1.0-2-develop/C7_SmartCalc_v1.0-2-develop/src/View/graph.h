#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <QVector>
#include <QtMath>

#include "qcustomplot.h"

extern "C" {
#include "../Back/s21_calc.h"
}

namespace Ui {
class Graph;
}

class Graph : public QDialog {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::Graph *ui;
  double xBegin, xEnd, h, X;
  int N;
  void paint();

  QVector<double> x, y;

 public slots:
  void slot(QString str);
};

#endif  // GRAPH_H
