#include "windowx.h"

#include <qcustomplot.h>

#include "ui_windowx.h"

windowX::windowX(QWidget *parent) : QMainWindow(parent), ui(new Ui::windowX) {
  ui->setupUi(this);
}

windowX::~windowX() { delete ui; }
