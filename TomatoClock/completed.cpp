#include "completed.h"
#include "ui_completed.h"
#include "mainwindow.h"
#include "clock.h"
#include "settings.h"

Completed::Completed(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Completed)
{
    ui->setupUi(this);
}

Completed::~Completed()
{
    delete ui;
}

void Completed::on_pushButton_clicked()
{
    MainWindow*todolist=new MainWindow;
    todolist->show();
    this->hide();
}

void Completed::on_pushButton_2_clicked()
{
    Completed*completed=new Completed;
    completed->show();
    this->hide();
}

void Completed::on_pushButton_3_clicked()
{
    Clock*clock=new Clock;
    clock->show();
    this->hide();
}

void Completed::on_pushButton_4_clicked()
{
    Settings*settings=new Settings;
    settings->show();
    this->hide();
}
