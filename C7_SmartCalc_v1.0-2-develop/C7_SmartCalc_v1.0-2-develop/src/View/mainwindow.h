#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdio.h>

#include <QMainWindow>

#include "credit.h"
#include "graph.h"
#include "qcustomplot.h"

extern "C" {
#include "../Back/s21_calc.h"
}

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

 private:
  Ui::MainWindow *ui;
  Graph *windowGraph;
  credit *windowCredit;

 private slots:
  void digits_numbers();
  void on_pushButtonPoint_clicked();
  void operations();
  void operators();
  void clear();
  void clickGraph();
  double calcX();
  void equal();
  void clickCredit();

 signals:
  void signal(QString);
};
#endif  // MAINWINDOW_H
