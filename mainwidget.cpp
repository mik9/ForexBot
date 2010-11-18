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
    QString fileName = QFileDialog::getOpenFileName(this,
         tr("Open File"), ".", "");
    QFile file(fileName);
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
    trade_max=-100500;
    for(int w1=w1_start;w1<w1_to;w1+=w1_step) {
        for(int w2=w2_start;w2<w2_to;w2+=w2_step) {
            for(int w3=w3_start;w3<w3_to;w3+=w3_step) {
                QVector<TradingCycle*> v;
                for(int w4=w4_start;w4<w4_to;w4+=w4_step) {
                    TradingCycle *t=new TradingCycle(&vector,date_start,date_end,w1,w2,w3,w4);
                    connect(t,SIGNAL(my_finished(TradingCycle*)),this,SLOT(thread_finished(TradingCycle*)));
                    t->start();
                    v.append(t);
                }
                for(int i=0;i<v.count();i++) {
                    v.at(i)->wait();
                }
            }
        }
        qDebug() << (double)(w1-w1_start)/(w1_to-w1_start)*100;
    }
}
void MainWidget::thread_finished(TradingCycle* t)
{
    if(t->profit()>trade_max){
        trade_max=t->profit();
        t->get_parameters(&w1_max,&w2_max,&w3_max,&w4_max);

        ui->label_profit->setText(QString::number(trade_max));
        ui->label_w1->setText(QString::number(w1_max));
        ui->label_w2->setText(QString::number(w2_max));
        ui->label_w3->setText(QString::number(w3_max));
        ui->label_w4->setText(QString::number(w4_max));
    }
    delete t;
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
    t.start();
    t.wait();
    qDebug() << t.profit();
    t.view_results();
}
