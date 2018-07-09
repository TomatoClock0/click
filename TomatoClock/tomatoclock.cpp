#include "tomatoclock.h"
#include "ui_tomatoclock.h"
#include "addtasks.h"
#include "managetasks.h"
#include "qstring.h"
#include <QTimer>
#include <QMessageBox>
#include <QtCore>
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include <QStandardItemModel>
#include <QMouseEvent>
static int workTime = 3;
static int relaxTime = 3;
static int restofTime=0;

int clock_status = 0;//0--not working
                     //1--working
                     //2--relaxing
                     //3--stopping


TomatoClock::TomatoClock(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::TomatoClock)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentWidget(ui->Todolist);

    timer1 = new QTimer(this);
    connect(timer1, SIGNAL(timeout()), this, SLOT(myslot1()));
    timer2 = timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(myslot2()));
    timer3=new QTimer(this);
    connect(timer3,SIGNAL(timeout()), this, SLOT(lcdnumberDisplay()));
    add_tasks=new AddTasks;
    connect(add_tasks,SIGNAL(inputCompleted()),this,SLOT(showslot()));


    ui->Start->setStyleSheet(tr("background-image: url(images/plays.jpg);"));
    ui->Stop->setStyleSheet(tr("background-image: url(images/stops.jpg);"));
    ui->Finish->setStyleSheet(tr("background-image: url(images/oks.jpg);"));
    ui->Delete->setStyleSheet(tr("background-image: url(images/deletes.jpg);"));
    ui->Clear->setStyleSheet(tr("background-image: url(images/clears.jpg);"));
    ui->Add->setStyleSheet(tr("background-image: url(images/add.jpg);"));
    ui->Done->setStyleSheet(tr("background-image: url(images/oks.jpg);"));
    ui->Manage->setStyleSheet(tr("background-image: url(images/manages.jpg);"));
    QFont ft;
    ft.setPointSize(12);
    ui->label->setFont(ft);
    ui->label_2->setFont(ft);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    ui->label->setPalette(pa);
    ui->label_2->setPalette(pa);
    QPalette palette;
    palette.setBrush(QPalette::Text,Qt::red);
    ui->addlabel->setPalette(palette);
    ui->tasksdetail->setFont(QFont("Timers",20,QFont::Bold));
    new_Table();
    tasks_Show();

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(myPress()));

}

TomatoClock::~TomatoClock()
{
    delete ui;
}


//add tasks
void TomatoClock::on_Add_clicked()
{
    add_tasks->show();
}

//manage tasks
void TomatoClock::on_Manage_clicked()
{
    managetasks *manage = new managetasks;
    manage->show();
}

//the work/relax time has been setted already
void TomatoClock::on_Done_clicked()
{
    const int w = ui->work_time->text().toInt();
    const int r=ui->relax_time->text().toInt();
    workTime = w ;
    relaxTime = r ;
}


//**************clock**************
//show the warning
void TomatoClock::myslot1()
{
    lcdnumberDisplay();
    timer1->stop();
    QMessageBox message(QMessageBox::NoIcon,"TomatoClock","Time's up!");
    message.setIconPixmap(QPixmap("iccccon.PNG"));
    message.exec();
    timer2->start(relaxTime*60000);
}
void TomatoClock::myslot2()
{
    QMessageBox message(QMessageBox::NoIcon,"TomatoClock","Work!");
    message.setIconPixmap(QPixmap("iccccon.PNG"));
    message.exec();
    timer2->stop();
    timer1->start(workTime*60000);
}
void TomatoClock::showslot()
{
    tasks_Show();
}


//start to time
void TomatoClock::on_Start_clicked()
{
    if(clock_status==0)
    {
        clock_status = 1;
        restofTime=workTime*60;//单位为s
        timer1->start(workTime*60000);
        timer3->start(1000);
    }
    else {}
}

void TomatoClock::on_Stop_clicked()
{
    if(clock_status==1){
    timer3->stop();
    timer1->stop();
    clock_status=3;
    }
    else if(clock_status==2){
        timer3->stop();
        timer1->stop();
        clock_status=3;
        }
    else if(clock_status==3){
        timer3->start(1000);
        timer1->start(restofTime*1000);
        clock_status=1;
    }
}
void TomatoClock::on_Finish_clicked()
{
    clock_status = 0;
    timer1->stop();
    timer2->stop();
    timer3->stop();
    QMessageBox message(QMessageBox::NoIcon,"TomatoClock","Congratulations");
    message.setIconPixmap(QPixmap("iccccon.PNG"));
    message.exec();

}
void TomatoClock:: lcdnumberDisplay()
{

    ui->minute_clock->display(restofTime/60);
    ui->second_clock->display(restofTime%60);
    restofTime--;
   if(clock_status==1&&restofTime==0){
        restofTime=relaxTime*60;
    }
   if(clock_status==2&&restofTime==0){
        restofTime=workTime*60;
    }
}


void TomatoClock::new_Table()
{
    model1=new QStandardItemModel();
    model2 =new QStandardItemModel();

    model1->setColumnCount(1);
    model1->setHeaderData(0,Qt::Horizontal,QStringLiteral("UNIFINISHED TASKS"));
    ui->addlabel->setModel(model1);
    ui->addlabel->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->addlabel->setColumnWidth(0,800);

    model2->setColumnCount(1);
    model2->setHeaderData(0,Qt::Horizontal,QStringLiteral("FINISHED TASKS"));
    ui->completedlabel->setModel(model2);
    ui->completedlabel->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->completedlabel->setColumnWidth(0,800);
}


void TomatoClock::tasks_Show()
{
    if(model1->rowCount()!=0)
    {
        model1->removeRows(0,model1->rowCount());
    }
    if(model2->rowCount()!=0)
    {
        model2->removeRows(0,model2->rowCount());
    }
    QSqlQuery query;
    bool success = query.exec("select *from information");
    if (success)
    {
        int i=0;
        int j=0;
        while(query.next())
        {
            if(query.value(3).toString() == '0')//completed job
            {
                model2->setItem(j,new QStandardItem(query.value(1).toString()));
                j++;
            }
            else if(query.value(3).toString() == '1')//unfinished job
            {
                model1->setItem(i,new QStandardItem(query.value(1).toString()));
                i++;
            }
        }
    }
}


void TomatoClock::on_addlabel_clicked(const QModelIndex &)
{
    //QTimer sdclicked=new Qtimer(this);



    timer->start(400);

}


/*void TomatoClock::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        timer->start(800);
    }

}*/

void TomatoClock::myPress()
{
    timer->stop();
    int row = ui-> addlabel ->currentIndex().row();
    qDebug()<<row;
    QString str = model1->data(model1->index(row,0)).toString();//第row行第1列的内容
    qDebug()<<str;
    ui->tabWidget->setCurrentWidget(ui->Clock);
    ui->clock_tasksname->setText(str);
}

void TomatoClock::on_addlabel_doubleClicked(const QModelIndex &index)
{

    timer->stop();
    int row = ui-> addlabel ->currentIndex().row();
    QSqlQuery query;
    bool success = query.exec("select *from information");
    if(success)
    {
        while(row>=0&&query.next())
        {
            if(query.value(3).toString() == '1')
                row--;
            if(row==-1)
            {
                QString str=query.value(2).toString();
                QMessageBox message(QMessageBox::NoIcon,"Detail",str);
                message.exec();
            }
        }
    }
}


