#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>

extern "C" {
#include "../Back/s21_calc.h"
}

namespace Ui {
class credit;
}

class credit : public QDialog {
  Q_OBJECT

 public:
  explicit credit(QWidget *parent = nullptr);
  ~credit();

 private slots:
  void on_pushButtonCount_clicked();
  int check();

 private:
  Ui::credit *ui;
};

#endif  // CREDIT_H
