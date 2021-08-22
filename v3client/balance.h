#ifndef BALANCE_H
#define BALANCE_H

#include <QWidget>
#include <QApplication>
#include <QDebug>
#include <QSize>
#include <QListWidgetItem>
#include "sqilteopreatorprojects.h"
#include "sqliteshop.h"
#include "shoplistdetail.h"
#include "sqliteoperator.h"

namespace Ui {
class balance;
}

class balance : public QWidget                         //订单界面
{
    Q_OBJECT

public:
    explicit balance(QString userName,QWidget *parent = nullptr);
    ~balance();

    void noSearch();                                //刷新
    void buy_push();                                //提交订单使能
    void delete_push();                            //删除订单使能
    QString nowName;                               //当前用户名

    std::vector<int> w_list;                       //订单列表


signals:
    void backBuySignal();                        //购买信号
    void backRefreshSignal();                    //刷新信号

private:
    Ui::balance *ui;
};

#endif // BALANCE_H
