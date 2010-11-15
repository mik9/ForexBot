#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    load();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::load()
{
    QFile file(tr("EURUSD60.csv"));
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << tr("Open file error.");
        return;
    }

    while(!file.atEnd()) {
        vector.append(new bid(file.readLine()));
    }
}

int MainWidget::find_date(QDate date) {

    /* TODO: fix search if selected date not in vector */

    int t=vector.count()/2;
    int f=t;
    QDate _date;
    while(vector[f]->date() != date && !(t==2 && vector[f]->date() > date)) {
        t=t/2+1;
        if(vector[f]->date()<date)
            f+=t;
        else if(vector[f]->date()>date)
            f-=t;
        _date=vector[f]->date();
    }
    return f;
}

int MainWidget::find_first_date(QDate date) {
    int f=find_date(date);
    while(vector[f]->date() == date)
        f--;
    return ++f;
}
int MainWidget::find_last_date(QDate date) {
    int f=find_date(date);
    while(vector[f]->date() == date)
        f++;
    return --f;
}

void MainWidget::on_button_train_clicked()
{
    //qDebug() << "Train button clicked.";
    int w1_start=ui->w1_from->value();
    int w2_start=ui->w2_from->value();
    int w3_start=ui->w3_from->value();
    int w4_start=ui->w4_from->value();

    int w1_step=ui->w1_step->value();
    int w2_step=ui->w2_step->value();
    int w3_step=ui->w3_step->value();
    int w4_step=ui->w4_step->value();

    int w1_to=ui->w1_to->value();
    int w2_to=ui->w2_to->value();
    int w3_to=ui->w3_to->value();
    int w4_to=ui->w4_to->value();

    long date_start=find_first_date(ui->date_from->date());
    long date_end=find_last_date(ui->date_to->date());

//    qDebug() << date_start << date_end;

    int w1_max,w2_max,w3_max,w4_max;
    double trade_max=-100;
    for(int w1=w1_start;w1<w1_to;w1+=w1_step) {
        for(int w2=w2_start;w2<w2_to;w2+=w2_step) {
            for(int w3=w3_start;w3<w3_to;w3+=w3_step) {
                for(int w4=w4_start;w4<w4_to;w4+=w4_step) {
                    TradingCycle t(&vector,date_start,date_end,w1,w2,w3,w4);
                    t.trade();
                    double profit=t.profit();
                    if(profit>trade_max) {
                        trade_max=profit;
                        w1_max=w1;
                        w2_max=w2;
                        w3_max=w3;
                        w4_max=w4;
                    }
                }
            }
        }
        qDebug() << (double)(w1-w1_start)/(w1_to-w1_start)*100;
    }
    //qDebug() << count;
    qDebug() << trade_max;
    qDebug("%d %d %d %d",w1_max,w2_max,w3_max,w4_max);
}

void MainWidget::on_button_trade_clicked()
{
    int w1=ui->w1->value();
    int w2=ui->w2->value();
    int w3=ui->w3->value();
    int w4=ui->w4->value();
    long date_start=find_first_date(ui->trade_from->date());
    long date_end=find_last_date(ui->trade_to->date());
    TradingCycle t(&vector,date_start,date_end,w1,w2,w3,w4);
    t.trade();
    qDebug() << t.profit();
}
