#ifndef CLOCK_H
#define CLOCK_H

#include <QDialog>

namespace Ui {
class Clock;
}

class Clock : public QDialog
{
    Q_OBJECT

public:
    explicit Clock(QWidget *parent = 0);
    ~Clock();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Clock *ui;
};

#endif // CLOCK_H
