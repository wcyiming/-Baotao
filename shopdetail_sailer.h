#ifndef SHOPDETAIL_SAILER_H
#define SHOPDETAIL_SAILER_H

#include <QWidget>
#include <QPalette>
#include <QApplication>
#include <QDebug>
#include "sqilteopreatorprojects.h"
#include "sqliteoperator.h"

namespace Ui {
class shopdetail_sailer;
}

class shopdetail_sailer : public QWidget
{
    Q_OBJECT

public:
    explicit shopdetail_sailer(int projectID,QWidget *parent = nullptr);
    ~shopdetail_sailer();
    void changeView(int projectID);

private:
    Ui::shopdetail_sailer *ui;
};

#endif // SHOPDETAIL_SAILER_H
