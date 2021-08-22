#ifndef MONEY_SAILER_H
#define MONEY_SAILER_H

#include <QWidget>
#include <QDoubleValidator>
#include "sqliteoperator.h"

namespace Ui {
class money_sailer;
}

class money_sailer : public QWidget
{
    Q_OBJECT

public:
    explicit money_sailer(QString userName, QWidget *parent = nullptr);
    ~money_sailer();
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
    Ui::money_sailer *ui;
};

#endif // MONEY_SAILER_H
