#ifndef MANAGEMENTDETAIL_H
#define MANAGEMENTDETAIL_H

#include <QWidget>
#include <QPalette>
#include <QApplication>
#include <QDebug>
#include "sqilteopreatorprojects.h"
#include "sqliteoperator.h"

namespace Ui {
class managementDetail;
}

class managementDetail : public QWidget
{
    Q_OBJECT

public:
    explicit managementDetail(QWidget *parent = nullptr);
    ~managementDetail();

    int nowID;

    void up_push();
    void enableButton();
    void list_push(int passID);

private:
    Ui::managementDetail *ui;
};

#endif // MANAGEMENTDETAIL_H
