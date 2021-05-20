#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <QWidget>
#include <QApplication>
#include <QDebug>
#include <QSize>
#include "sqilteopreatorprojects.h"
#include "sqliteoperator.h"
#include "projectpreview.h"
#include <QListWidgetItem>

namespace Ui {
class management;
}

class management : public QWidget
{
    Q_OBJECT

public:
    explicit management(QString userName,QWidget *parent = nullptr);
    ~management();

    void noSearch();
    void discount_push();
    int nowFather;
    void onListItemClicked();
    void enableButton();


    std::vector<int> w_list;

public slots:
    void onListItemClicked(QListWidgetItem *item);

signals:
    void backIDsignalManage(int ID);

private:
    Ui::management *ui;
};

#endif // MANAGEMENT_H
