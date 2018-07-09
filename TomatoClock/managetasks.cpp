#include "managetasks.h"
#include "ui_managetasks.h"
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include <QMessageBox>

managetasks::managetasks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::managetasks)
{
    ui->setupUi(this);
    ui->m_delete->setStyleSheet(tr("background-image: url(images/deletes.jpg);"));
    ui->m_clear->setStyleSheet(tr("background-image: url(images/clears.jpg);"));
    myShow();
}

void managetasks::myShow()
{

    QSqlQuery query;
    bool success = query.exec("select *from information");
    if (success)
    {
        //qDebug()<<"yes";
        query.next();
        while(query.value(3).toString() != '1'){
            if (query.next() == NULL){
                return ;
            }
        }
        ui->lineEdit->setText(query.value(1).toString());
    }
}

managetasks::~managetasks()
{
    delete ui;
}

/*void managetasks::on_pushButton_clicked()
{
    QSqlQuery query;
    QString i = "8";
    QString updated = QString("update information set conditions = 0 where id = ");
    updated += i;
    qDebug()<<updated;
    bool success = query.exec(updated);
    if (success){
        QMessageBox::about(NULL, "Save", "change condition success");
    }
    else {
        QMessageBox::about(NULL, "Save", "error change condition");
    }
}*/

void managetasks::on_m_Cancel_clicked()
{
    this->destroy();
}
