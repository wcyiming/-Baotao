#ifndef MAINWINDOWGUEST_H
#define MAINWINDOWGUEST_H

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
#include "shopdetail_sailer.h"

namespace Ui {
class mainwindowguest;
}

class mainwindowguest : public QWidget
{
    Q_OBJECT

public:
    explicit mainwindowguest(QWidget *parent = nullptr);
    ~mainwindowguest();

    void tologin();
    void market_push();

    shopdetail_sailer *nowShop;

public slots:
        void shopdetail(int ID);

private:
    Ui::mainwindowguest *ui;
};

#endif // MAINWINDOWGUEST_H
