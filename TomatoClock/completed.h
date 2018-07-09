#ifndef COMPLETED_H
#define COMPLETED_H

#include <QDialog>

namespace Ui {
class Completed;
}

class Completed : public QDialog
{
    Q_OBJECT

public:
    explicit Completed(QWidget *parent = 0);
    ~Completed();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Completed *ui;
};

#endif // COMPLETED_H
