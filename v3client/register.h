#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QPalette>
#include <QApplication>
#include <fstream>
#include <cstdlib>
#include <QDataStream>
#include <QFile>
#include "widget.h"
#include "mainwindow.h"
#include "mainwindowguest.h"
#include "sqliteoperator.h"

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();
    void tologin();                     //跳转登录
    void Register_push();                //注册按钮槽函数
    void guest_login();                  //游客登录
    void enableButton();                //注册按钮使能函数

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
