#include "graph.h"

#include <stdio.h>

#include "ui_graph.h"

Graph::Graph(QWidget *parent) : QDialog(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
  setWindowTitle("Graph");
  setFixedSize(width(), height());
}

Graph::~Graph() { delete ui; }

void Graph::paint() {
  double result = 0.0;
  QString result_label;
  h = 0.2;
  int status;

  QByteArray array = ui->labelV->text().toLatin1();
  QString strok = ui->labelV->text();
  char *str = array.data();
  int xmax = ui->lineEditXmax->text().toInt();
  int xmin = ui->lineEditXmin->text().toInt();
  int ymax = ui->lineEditYmax->text().toInt();
  int ymin = ui->lineEditYmin->text().toInt();

  if (xmax > 10000 || xmax < -10000) {
    ui->lineEditXmax->setText("Error Input");
  } else if (xmin > 10000 || xmin < -10000) {
    ui->lineEditXmax->setText("Error Input");
  } else if (ymax > 10000 || ymax < -10000) {
    ui->lineEditXmax->setText("Error Input");
  } else if (ymin > 10000 || ymin < -10000) {
    ui->lineEditXmax->setText("Error Input");
  } else {
    ui->widget->xAxis->setRange(xmin, xmax);
    ui->widget->yAxis->setRange(ymin, ymax);

    for (X = xmin; X <= xmax; X += h) {
      x.push_back(X);
      status = s21_simple_calc(str, &result, X);
      if (status == 2) {
        ui->labelV->setText("Error Input");
      } else if (status == 1) {
        ui->labelV->setText("Error calc");
      } else {
        y.push_back(result);
      }
    }

    ui->widget->addGraph();
    ui->widget->graph()->addData(x, y);
    ui->widget->replot();
  }
}

void Graph::slot(QString str) { ui->labelV->setText(str); }

void Graph::on_pushButton_clicked() { Graph::paint(); }
