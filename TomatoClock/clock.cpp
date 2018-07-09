#include "clock.h"
#include "ui_clock.h"
#include "mainwindow.h"
#include "completed.h"
#include "settings.h"

Clock::Clock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Clock)
{
    ui->setupUi(this);
}

Clock::~Clock()
{
    delete ui;
}

void Clock::on_pushButton_clicked()
{
    MainWindow*todolist=new MainWindow;
    todolist->show();
    this->hide();
}

void Clock::on_pushButton_2_clicked()
{
    Completed*completed=new Completed;
    completed->show();
    this->hide();
}

void Clock::on_pushButton_4_clicked()
{
    Clock*clock=new Clock;
    clock->show();
    this->hide();
}

void Clock::on_pushButton_3_clicked()
{
    Settings*settings=new Settings;
    settings->show();
    this->hide();
}
