#ifndef SHOPCARNUMBER_H
#define SHOPCARNUMBER_H

#include <QWidget>
#include <QPalette>
#include <QApplication>
#include <QDebug>
#include "sqilteopreatorprojects.h"
#include "sqliteshop.h"

namespace Ui {
class shopCarNumber;
}

class shopCarNumber : public QWidget                        //购物车商品数量修改窗口
{
    Q_OBJECT

public:
    explicit shopCarNumber(QString roamName,int roamID,QWidget *parent = nullptr);
    ~shopCarNumber();

    void addPush();                                        //+按钮槽函数
    void minusPush();                                     //-按钮槽函数
    void updatePush();                                    //提交按钮槽函数
    void deletePush();                                    //删除按钮槽函数

    QString nowName;                                      //当前用户名
    int nowID;                                            //当前商品id名

signals:
    void backRefreshSignal();                             //刷新信号

private:
    Ui::shopCarNumber *ui;
};

#endif // SHOPCARNUMBER_H
