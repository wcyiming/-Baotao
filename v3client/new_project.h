#ifndef NEW_PROJECT_H
#define NEW_PROJECT_H

#include <QWidget>
#include <QPalette>
#include <QApplication>
#include <QDebug>
#include "sqilteopreatorprojects.h"
#include "sqliteoperator.h"

namespace Ui {
class new_project;
}

class new_project : public QWidget
{
    Q_OBJECT

public:
    explicit new_project(QString userName,QWidget *parent = nullptr);
    ~new_project();
    QString nowName;                           //当前账户名
    void up_push();                            //提交按钮槽函数
    void enableButton();                       //使能函数

private:
    Ui::new_project *ui;
};

#endif // NEW_PROJECT_H
