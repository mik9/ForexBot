#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QFile>
#include <QFileDialog>
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

    int w1_max,w2_max,w3_max,w4_max;
    double trade_max;

private slots:
    void on_button_trade_clicked();
    void on_button_train_clicked();
    void thread_finished(TradingCycle*);
};

#endif // MAINWIDGET_H
