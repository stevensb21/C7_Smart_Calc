#include "credit.h"

#include "ui_credit.h"

credit::credit(QWidget *parent) : QDialog(parent), ui(new Ui::credit) {
  ui->setupUi(this);
  setWindowTitle("Credit calculator");
  setFixedSize(width(), height());
}

credit::~credit() { delete ui; }

void credit::on_pushButtonCount_clicked() {
  double AmoCredit = ui->lineAmount->text().toDouble();
  int Term = ui->lineTerm->text().toInt();
  double Interest = ui->lineRate->text().toDouble();
  double FirstPayments = 0.0;
  double Overpayment = 0.0;
  double Total = 0.0;
  double LastPayments = 0.0;

  if (credit::check() != 2) {
    if (ui->comboTerm->currentIndex() == 0) {
      Term *= 12;
    }

    if (ui->comboType->currentIndex() == 1) {
      credit_dif(AmoCredit, Term, Interest, &FirstPayments, &Overpayment,
                 &Total, &LastPayments);
      ui->labelFirstPay->setText(QString::number(FirstPayments, 'f', 2));
      ui->labelLastPay->setText(QString::number(LastPayments, 'f', 2));
    } else {
      credit_amu(AmoCredit, Term, Interest, &FirstPayments, &Overpayment,
                 &Total);
      ui->labelFirstPay->setText(QString::number(FirstPayments, 'f', 2));
      ui->labelLastPay->setText(QString::number(FirstPayments, 'f', 2));
    }

    ui->labelOver->setText(QString::number(Overpayment, 'f', 2));
    ui->labelTotal->setText(QString::number(Total, 'f', 2));
  } else {
    ui->labelFirstPay->setText("");
    ui->labelLastPay->setText("");
    ui->labelOver->setText("");
    ui->labelTotal->setText("");
  }
}

int credit::check() {
  int status = 0;

  QByteArray arrayAm = ui->lineAmount->text().toLatin1();
  char *strAm = arrayAm.data();
  status = number_check(strAm);
  if (status == 2) ui->lineAmount->setText("Error Input");
  return status;

  QByteArray arrayRa = ui->lineRate->text().toLatin1();
  char *strRa = arrayRa.data();
  status = number_check(strRa);
  if (status == 2) ui->lineRate->setText("Error Input");
  return status;

  QByteArray arrayTe = ui->lineTerm->text().toLatin1();
  char *strTe = arrayTe.data();
  status = int_check(strTe);
  if (status == 2) ui->lineTerm->setText("Error Input");
  return status;

  return status;
}
