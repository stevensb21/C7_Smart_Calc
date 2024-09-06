#include "mainwindow.h"

#include <string.h>

#include <iostream>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("Smart Calculator");
  setFixedSize(geometry().width(), geometry().height());

  connect(ui->pushButtonNum0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButtonNum1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButtonNum2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButtonNum3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButtonNum4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButtonNum5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButtonNum6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButtonNum7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButtonNum8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButtonNum9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->pushButtonDivision, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButtonAdd, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButtonMult, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButtonDiff, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButtonMod, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButtonPow, SIGNAL(clicked()), this, SLOT(operators()));

  connect(ui->pushButtonEqual, SIGNAL(clicked()), this, SLOT(equal()));

  connect(ui->pushButtonSign, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButtonClear, SIGNAL(clicked()), this, SLOT(clear()));

  connect(ui->pushButtonSin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButtonCos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButtonTan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButtonAsin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButtonAcos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButtonAtan, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->pushButtonLn, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButtonLog, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButtonSqrt, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->pushButtonOpen, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButtonClose, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButtonX, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->pushButtonGraph, SIGNAL(clicked()), this, SLOT(clickGraph()));
  connect(ui->pushButtonCredit, SIGNAL(clicked()), this, SLOT(clickCredit()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();

  if (ui->label->text() == "0") ui->label->setText("");

  QString num_label;

  num_label = (ui->label->text() + button->text());

  ui->label->setText(num_label);
}

void MainWindow::on_pushButtonPoint_clicked() {
  if (ui->label->text().back() != '.')
    ui->label->setText(ui->label->text() + '.');
}

void MainWindow::clear() {
  ui->lineEditX->setText("");
  ui->label->setText("0");
}

void MainWindow::operations() {
  QPushButton *button = (QPushButton *)sender();

  double num_label;
  QString result_label;

  if (button->text() == "+/-") {
    num_label = (ui->label->text()).toDouble();
    num_label = num_label * -1;
    result_label = QString::number(num_label, 'g', 15);

    ui->label->setText(result_label);
  }
}

void MainWindow::operators() {
  QPushButton *button = (QPushButton *)sender();
  if (ui->label->text() == "0") ui->label->setText("");
  QString result_label;

  result_label = (ui->label->text() + button->text());

  ui->label->setText(result_label);
}

void MainWindow::equal() {
  int status = 0;
  double result = 0.0;
  double x = 0.0;
  QString result_label;

  x = MainWindow::calcX();

  QByteArray array = ui->label->text().toLatin1();
  char *str = array.data();

  status = s21_simple_calc(str, &result, x);
  if (status == 2) {
    ui->label->setText("Error Input");
  } else if (status == 1) {
    ui->label->setText("Error calc");
  } else {
    result_label = QString::number(result, 'g', 15);
    ui->label->setText(result_label);
  }
}

double MainWindow::calcX() {
  int status = 0;
  double x = 0.0;
  QString result_label;
  double result = 0.0;
  QByteArray array = ui->lineEditX->text().toLatin1();
  if (!ui->lineEditX->displayText().isEmpty()) {
    char *str = array.data();
    for (int i = 0; i < (int)strlen(str); i++) {
      if (str[i] == 'x') ui->lineEditX->setText("Error Input");
    }
    status = s21_simple_calc(str, &result, x);
    if (status == 0) {
      result_label = QString::number(result, 'g', 15);

      ui->lineEditX->setText(result_label);
    } else {
      ui->lineEditX->setText("Error Input");
    }
  }

  return result;
}

void MainWindow::clickGraph() {
  windowGraph = new Graph(this);
  windowGraph->show();
  connect(this, &MainWindow::signal, windowGraph, &Graph::slot);
  emit signal(ui->label->text());
}

void MainWindow::clickCredit() {
  windowCredit = new credit(this);
  windowCredit->show();
}
