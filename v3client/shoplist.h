#ifndef SHOPLIST_H
#define SHOPLIST_H

#include <QWidget>
#include <QApplication>
#include <QDebug>
#include <QSize>
#include <QListWidgetItem>
#include "sqilteopreatorprojects.h"
#include "sqliteshop.h"
#include "shoplistdetail.h"
#include "shopcarnumber.h"

namespace Ui {
class shopList;
}

class shopList : public QWidget                        //购物车界面
{
    Q_OBJECT

public:
    explicit shopList(QString userName,QWidget *parent = nullptr);
    ~shopList();

    void noSearch();                                   //刷新
    void buy_push();                                   //购买按钮槽
    void onListItemClicked();                         //item点击
    QString nowName;                                  //当前账户名

    std::vector<int> w_list;                         //购物车列表

public slots:
    void onListItemClicked(QListWidgetItem *item);   //item点击

signals:
    void backChangeSignal();                         //界面刷新信号
    void backSendSignal();                           //跳转结算信号

private:
    Ui::shopList *ui;
};

#endif // SHOPLIST_H
