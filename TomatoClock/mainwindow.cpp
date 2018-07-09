#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "completed.h"
#include "clock.h"
#include "settings.h"
#include "addtasks.h"
#include "managetasks.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    MainWindow*todolist=new MainWindow;
    todolist->show();
    this->hide();
}

void MainWindow::on_pushButton_2_clicked()
{
    Completed *completed=new Completed;
    completed->show();
    this->hide();
}


void MainWindow::on_pushButton_3_clicked()
{
    Clock*clock=new Clock;
    clock->show();
    this->hide();
}

void MainWindow::on_pushButton_4_clicked()
{
    Settings*settings=new Settings;
    settings->show();
    this->hide();
}

void MainWindow::on_pushButton_5_clicked()
{
    AddTasks*addtasks=new AddTasks;
    addtasks->show();
    this->hide();
}

void MainWindow::on_pushButton_6_clicked()
{
    ManageTasks*managetasks=new ManageTasks;
    managetasks->show();
    this->hide();
}
