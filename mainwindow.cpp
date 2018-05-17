#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    PaintWidget *paintWidget = new PaintWidget(this);
    //connect是QT中的连接函数, 将信号发送者sender对象中的信号signal与接受者receiver中的member槽函数联系起来
    connect(this, SIGNAL(Clear_Screen()), paintWidget, SLOT(ClearScreen()));
    connect(this, SIGNAL(Select_Shape(shape::Type)), paintWidget, SLOT(Choose_Current_Shape(shape::Type)));
    connect(this, SIGNAL(fill()), paintWidget, SLOT(Fill_Polygon()));
    connect(this, SIGNAL(clockwise()), paintWidget, SLOT(Clockwise()));
    connect(this, SIGNAL(counterclockwise()), paintWidget, SLOT(CounterClockwise()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
//将第一个按钮设置为清屏功能
void MainWindow::on_pushButton_clicked()
{
    emit Clear_Screen();
}
//将按钮2设置为画直线功能
void MainWindow::on_pushButton_2_clicked()
{
    emit Select_Shape(shape::line);
}
//将按钮3设置为画圆功能
void MainWindow::on_pushButton_3_clicked()
{
    emit Select_Shape(shape::circle);
}
//将按钮4设置为画椭圆功能
void MainWindow::on_pushButton_4_clicked()
{
    emit Select_Shape(shape::ellipse);
}
void MainWindow::on_pushButton_5_clicked()
{
    emit Select_Shape(shape::polygon);
}
void MainWindow::on_pushButton_6_clicked()
{
    emit fill();
}
void MainWindow::on_pushButton_7_clicked()
{
    emit clockwise();
}
void MainWindow::on_pushButton_8_clicked()
{
    emit counterclockwise();
}
