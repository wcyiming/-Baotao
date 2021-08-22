#ifndef MANAGEMENTDETAIL_H
#define MANAGEMENTDETAIL_H

#include <QWidget>
#include <QPalette>
#include <QApplication>
#include <QDebug>
#include "sqilteopreatorprojects.h"
#include "sqliteoperator.h"

namespace Ui {
class managementDetail;
}

class managementDetail : public QWidget
{
    Q_OBJECT

public:
    explicit managementDetail(QWidget *parent = nullptr);
    ~managementDetail();

    int nowID;                                //当前商品id

    void up_push();                           //修改按钮槽函数
    void enableButton();                      //修改按钮使能函数
    void list_push(int passID);              //更新商品详情界面

private:
    Ui::managementDetail *ui;
};

#endif // MANAGEMENTDETAIL_H
