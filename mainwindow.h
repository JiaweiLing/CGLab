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
              void fill();
              void clockwise();
              void counterclockwise();
              void up();
              void down();
              void left();
              void right();
private slots:
              void on_pushButton_clicked();
              void on_pushButton_2_clicked();
              void on_pushButton_3_clicked();
              void on_pushButton_4_clicked();
              void on_pushButton_5_clicked();
              void on_pushButton_6_clicked();
              void on_pushButton_7_clicked();
              void on_pushButton_8_clicked();
              void on_pushButton_9_clicked();
              void on_pushButton_10_clicked();
              void on_pushButton_11_clicked();
              void on_pushButton_12_clicked();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
