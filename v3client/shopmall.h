#ifndef SHOPMALL_H
#define SHOPMALL_H

#include <QWidget>
#include <QApplication>
#include <QDebug>
#include <QSize>
#include "sqilteopreatorprojects.h"
#include "projectpreview.h"
#include <QListWidgetItem>

namespace Ui {
class Shopmall;
}

class Shopmall : public QWidget
{
    Q_OBJECT

public:
    explicit Shopmall(QWidget *parent = nullptr);
    ~Shopmall();
    void noSearch();                            //没有搜索的默认全部商品情况
    void search_push();                         //搜索按钮槽函数
    void onListItemClicked();                   //项目被点击

    std::vector<int> w_list;                   //项目的vector

public slots:
    void onListItemClicked(QListWidgetItem *item);      //项目被点击槽函数

signals:
    void backIDsignal(int ID);                          //项目被点击信号

private:
    Ui::Shopmall *ui;
};

#endif // SHOPMALL_H
