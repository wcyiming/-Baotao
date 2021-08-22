#ifndef MAINWINDOWSAILER_H
#define MAINWINDOWSAILER_H

#include <QWidget>
#include "widget.h"
#include "sqliteoperator.h"
#include "username_sailer.h"
#include "shopmall.h"
#include "money_sailer.h"
#include "sqilteopreatorprojects.h"
#include "shopdetail_sailer.h"
#include "projectpreview.h"
#include "management.h"
#include "managementdetail.h"
#include "new_project.h"

namespace Ui {
class mainWindowSailer;
}

class mainWindowSailer : public QWidget
{
    Q_OBJECT

public:
    explicit mainWindowSailer(QString sailerName, QWidget *parent = nullptr);
    ~mainWindowSailer();

    void useredit_push();                              //用户信息按钮槽函数
    void tologin();                                    //登出槽函数
    void changeMoney_push();                           //余额管理按钮槽函数
    void refreshMoney();                               //刷新余额
    void market_push();                                //商城按钮槽函数
    void newbt_push();                                 //新建商品按钮槽函数
    void manage_push();                                //管理商品按钮槽函数


    QString nowName;                                   //商户名
    shopdetail_sailer *nowShop;                        //固定的商品细节界面
    managementDetail *nowManagement;                   //固定的商品管理细节界面

public slots:
        void shopdetail(int ID);                      //跳转商品细槽
        void managedetail(int ID);                    //跳转商品管理细节界面槽函数
private:
    Ui::mainWindowSailer *ui;
};

#endif // MAINWINDOWSAILER_H
