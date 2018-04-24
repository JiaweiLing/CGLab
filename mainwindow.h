#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "shape.h"
#include <QMainWindow>
#include "paintwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
              void Select_Shape(shape::Type NewShape);
              void Clear_Screen();
private slots:
              void on_pushButton_clicked();
              void on_pushButton_2_clicked();
              void on_pushButton_3_clicked();
              void on_pushButton_4_clicked();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
