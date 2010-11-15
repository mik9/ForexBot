#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QFile>
#include "bid.h"
#include "traidingcycle.h"

namespace Ui {
    class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
    void LoadValues();
    void load();
    QVector<bid*> vector;

    int w1;
    int w2;
    int w3;
    int w4;
    int find_date(QDate);
    int find_first_date(QDate);
    int find_last_date(QDate);

private slots:
    void on_button_trade_clicked();
    void on_button_train_clicked();
};

#endif // MAINWIDGET_H
