#ifndef USERNAME_BUYER_H
#define USERNAME_BUYER_H

#include <QWidget>
#include <QPalette>
#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "sqliteoperator.h"

namespace Ui {
class username_buyer;
}

class username_buyer : public QWidget
{
    Q_OBJECT

public:
    explicit username_buyer(QString userName, QWidget *parent = nullptr);
    ~username_buyer();
    void change_push();                      //修改按钮槽函数
    void enableButton();                     //按钮使能
    QString nowName;                         //当前账户名


private:
    Ui::username_buyer *ui;
};

#endif // USERNAME_BUYER_H
