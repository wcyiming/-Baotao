#ifndef SHOPDETAIL_BUYER_H
#define SHOPDETAIL_BUYER_H

#include <QWidget>
#include <QPalette>
#include <QApplication>
#include <QDebug>
#include "sqilteopreatorprojects.h"
#include "sqliteoperator.h"

namespace Ui {
class shopdetail_buyer;
}

class shopdetail_buyer : public QWidget
{
    Q_OBJECT

public:
    explicit shopdetail_buyer(int projectID,QWidget *parent = nullptr);
    ~shopdetail_buyer();
    void changeView(int projectID);

private:
    Ui::shopdetail_buyer *ui;
};

#endif // SHOPDETAIL_BUYER_H
