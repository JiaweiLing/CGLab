#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    PaintWidget *paintWidget = new PaintWidget(this);

    connect(this, SIGNAL(Clear_Screen()), paintWidget, SLOT(ClearScreen()));
    connect(this, SIGNAL(Select_Shape(shape::Type)), paintWidget, SLOT(Choose_Current_Shape(shape::Type)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    emit Clear_Screen();
}

void MainWindow::on_pushButton_2_clicked()
{
    emit Select_Shape(shape::line);
}
