#ifndef TOMATOCLOCK_H
#define TOMATOCLOCK_H

#include <QMainWindow>
#include <QTimer>
#include <QStandardItemModel>
#include "addtasks.h"
#include <QMouseEvent>

namespace Ui {
class TomatoClock;
}

class TomatoClock : public QMainWindow
{
    Q_OBJECT

public:
    void new_Table();
    void tasks_Show();
    //void mousePressEvent(QMouseEvent *);
   // void mouseDoubleClickEvent(QMouseEvent *);

    QTimer *timer;


    explicit TomatoClock(QWidget *parent = 0);
    ~TomatoClock();


private slots:

    void on_Add_clicked();

    void on_Manage_clicked();

    void on_Done_clicked();

    void on_Start_clicked();

    void myslot1();
    void myslot2();
    void showslot();

    void lcdnumberDisplay();

    void on_Stop_clicked();

    void on_Finish_clicked();


    void on_addlabel_clicked(const QModelIndex &);
    void myPress();
    void on_addlabel_doubleClicked(const QModelIndex &);





private:
    Ui::TomatoClock *ui;
    QTimer *timer1;
    QTimer *timer2;
    QTimer *timer3;

    QStandardItemModel *model1;
    QStandardItemModel *model2;

    AddTasks *add_tasks;

};

#endif // TOMATOCLOCK_H
