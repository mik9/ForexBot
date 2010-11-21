#ifndef RESULTSWIDGET_H
#define RESULTSWIDGET_H

#include <QWidget>
#include "deal.h"
#include <QVector>
#include <QDialog>
#include <QDebug>

namespace Ui {
    class ResultsWidget;
}

class ResultsWidget : public QDialog
{
    Q_OBJECT

public:
    explicit ResultsWidget(QWidget *parent = 0,QVector<Deal*>* d=NULL);
    ~ResultsWidget();

private:
    Ui::ResultsWidget *ui;
    QVector<Deal*>* d;
};

#endif // RESULTSWIDGET_H
