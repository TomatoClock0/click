#ifndef MANAGETASKS_H
#define MANAGETASKS_H

#include <QDialog>

namespace Ui {
class managetasks;
}

class managetasks : public QDialog
{
    Q_OBJECT

public:
    explicit managetasks(QWidget *parent = 0);
    ~managetasks();
    void myShow();

private slots:
    //void on_pushButton_clicked();

    void on_m_Cancel_clicked();

private:
    Ui::managetasks *ui;
};

#endif // MANAGETASKS_H
