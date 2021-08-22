#ifndef SHOPLISTDETAIL_H
#define SHOPLISTDETAIL_H

#include <QWidget>
#include <QPalette>
#include <QApplication>
#include <QDebug>
#include "sqilteopreatorprojects.h"
#include "sqliteshop.h"

namespace Ui {
class shopListDetail;
}

class shopListDetail : public QWidget          //购物车列表元素
{
    Q_OBJECT

public:
    explicit shopListDetail(QString nowName,int nowID,QWidget *parent = nullptr);
    ~shopListDetail();

private:
    Ui::shopListDetail *ui;
};

#endif // SHOPLISTDETAIL_H
