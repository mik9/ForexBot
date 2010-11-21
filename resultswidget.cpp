#include "resultswidget.h"
#include "ui_resultswidget.h"

ResultsWidget::ResultsWidget(QWidget *parent, QVector<Deal *> *d) :
    QDialog(parent),
    ui(new Ui::ResultsWidget)
{
    ui->setupUi(this);
    QStringList l;
    ui->tableWidget->setColumnCount(4);
    l << "Direction";
    l << "Open value";
    l << "Close value";
    l << "Profit";
    ui->tableWidget->setHorizontalHeaderLabels(l);
    if(!d)
        return;
    ui->tableWidget->setRowCount(d->count());
    for(int i=0;i<d->count();i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(d->at(i)==BUY ? "Buy" : "Sell"));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(d->at(i)->open_value())));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(d->at(i)->close_value())));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(d->at(i)->profit())));
    }
}

ResultsWidget::~ResultsWidget()
{
    delete ui;
}
