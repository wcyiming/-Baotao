#ifndef MAINWINDOWSAILER_H
#define MAINWINDOWSAILER_H

#include <QWidget>
#include "widget.h"
#include "sqliteoperator.h"
#include "username_sailer.h"
#include "shopmall.h"
#include "money_sailer.h"
#include "sqilteopreatorprojects.h"
#include "shopdetail_sailer.h"
#include "projectpreview.h"
#include "management.h"
#include "managementdetail.h"
#include "new_project.h"

namespace Ui {
class mainWindowSailer;
}

class mainWindowSailer : public QWidget
{
    Q_OBJECT

public:
    explicit mainWindowSailer(QString sailerName, QWidget *parent = nullptr);
    ~mainWindowSailer();

    void useredit_push();
    void tologin();
    void changeMoney_push();
    void refreshMoney();
    void market_push();
    void newbt_push();
    void manage_push();


    QString nowName;
    shopdetail_sailer *nowShop;
    managementDetail *nowManagement;

public slots:
        void shopdetail(int ID);
        void managedetail(int ID);

private:
    Ui::mainWindowSailer *ui;
};

#endif // MAINWINDOWSAILER_H
