#ifndef XWINDOW_H
#define XWINDOW_H

#include <QMainWindow>

class xwindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit xwindow(QWidget *parent = nullptr);

 signals:
};

#endif  // XWINDOW_H
