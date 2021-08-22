#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <QWidget>
#include <QApplication>
#include <QDebug>
#include <QSize>
#include "sqilteopreatorprojects.h"
#include "sqliteoperator.h"
#include "projectpreview.h"
#include <QListWidgetItem>

namespace Ui {
class management;
}

class management : public QWidget
{
    Q_OBJECT

public:
    explicit management(QString userName,QWidget *parent = nullptr);
    ~management();

    void noSearch();                           //加载所有商品
    void discount_push();                     //打折按钮槽函数
    int nowFather;                            //当前账户id
    void onListItemClicked();                //点击某个item
    void enableButton();                     //打折按钮使能函数


    std::vector<int> w_list;                //商品id list

public slots:
    void onListItemClicked(QListWidgetItem *item);     //点击某个item槽函数

signals:
    void backIDsignalManage(int ID);                  //商品细节界面信号

private:
    Ui::management *ui;
};

#endif // MANAGEMENT_H
