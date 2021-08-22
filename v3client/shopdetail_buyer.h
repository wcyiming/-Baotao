#ifndef SHOPDETAIL_BUYER_H
#define SHOPDETAIL_BUYER_H

#include <QWidget>
#include <QPalette>
#include <QApplication>
#include <QDebug>
#include "sqilteopreatorprojects.h"
#include "sqliteoperator.h"
#include "sqliteshop.h"

namespace Ui {
class shopdetail_buyer;
}

class shopdetail_buyer : public QWidget
{
    Q_OBJECT

public:
    explicit shopdetail_buyer(QString roamName,int projectID,QWidget *parent = nullptr);
    ~shopdetail_buyer();
    void changeView(int projectID);                      //改变当前状态
    QString nowName;                                     //当前账户的名字
    int nowID;                                           //当前商品的id
    void buy_push();                                     //购买按钮槽函数

private:
    Ui::shopdetail_buyer *ui;
};

#endif // SHOPDETAIL_BUYER_H
