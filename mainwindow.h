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



namespace Ui {
class Mainwindow;
}

class Mainwindow : public QWidget
{
    Q_OBJECT

public:
    explicit Mainwindow(QString username, QWidget *parent = nullptr);
    ~Mainwindow();
    void useredit_push();
    void tologin();
    void changeMoney_push();
    void refreshMoney();

    void market_push();

    shopdetail_buyer *nowShop;


    QString nowName;
public slots:
        void shopdetail(int ID);

private:
    Ui::Mainwindow *ui;
};

#endif // MAINWINDOW_H
