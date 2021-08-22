#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPalette>
#include <QApplication>
#include "widget.h"
#include "sqliteoperator.h"
#include "username_buyer.h"
#include "shopmall.h"
#include "money_buyer.h"
#include "sqilteopreatorprojects.h"
#include "shopdetail_buyer.h"
#include "projectpreview.h"
#include "shoplist.h"
#include "balance.h"
#include "shopresult.h"



namespace Ui {
class Mainwindow;
}

class Mainwindow : public QWidget
{
    Q_OBJECT

public:
    explicit Mainwindow(QString username, QWidget *parent = nullptr);
    ~Mainwindow();
    void useredit_push();               //用户信息按钮槽函数
    void tologin();                     //跳转登录窗口槽函数
    void changeMoney_push();            //充值按钮槽函数
    void refreshMoney();                //刷新当前钱数

    void market_push();                //商城按钮槽函数
    void shoplist_push();               //购物车按钮槽函数
    void check();                      //生成订单槽函数
    void checksuccess();               //购买成功槽函数
    void checkfail();                 //删除订单槽函数

    int hasBuy;                       //订单是否完成

    shopdetail_buyer *nowShop;        //通用的商品详细界面类对象
    shopList *nowList;                //通用的购物车类对象
    balance *nowCheck;                 //通用的订单类对象


    QString nowName;                  //当前的用户名
public slots:
        void shopdetail(int ID);     //跳转商品详细界面的槽函数

private:
    Ui::Mainwindow *ui;
};

#endif // MAINWINDOW_H
