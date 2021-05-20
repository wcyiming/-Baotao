#ifndef MONEY_BUYER_H
#define MONEY_BUYER_H

#include <QWidget>
#include <QDoubleValidator>
#include "sqliteoperator.h"

namespace Ui {
class money_buyer;
}

class money_buyer : public QWidget
{
    Q_OBJECT

public:
    explicit money_buyer(QString userName,QWidget *parent = nullptr);
    ~money_buyer();
    QString nowName;
    void chong_number();
    void chong_30();
    void chong_60();
    void chong_150();
    void chong_300();
    void chong_600();
    void ti_number();
    void ti_30();
    void ti_60();
    void ti_150();
    void ti_300();
    void ti_600();
    void sendChange();
signals:
    void backSignal();

private:
    Ui::money_buyer *ui;
};

#endif // MONEY_BUYER_H
