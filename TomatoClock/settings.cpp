#include "settings.h"
#include "ui_settings.h"
#include "mainwindow.h"
#include "completed.h"
#include "clock.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_pushButton_clicked()
{
    MainWindow*todolist=new MainWindow;
    todolist->show();
    this->hide();
}

void Settings::on_pushButton_2_clicked()
{
    Completed*completed=new Completed;
    completed->show();
    this->hide();
}

void Settings::on_pushButton_3_clicked()
{
    Clock*clock=new Clock;
    clock->show();
    this->hide();
}

void Settings::on_pushButton_4_clicked()
{
    Settings*settings=new Settings;
    settings->show();
    this->hide();
}
