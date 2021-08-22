#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPalette>
#include <QApplication>
#include "register.h"
#include "mainwindow.h"
#include "mainwindowsailer.h"
#include "mainwindowguest.h"
#include "sqliteoperator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void toRegister();
    void Login();
    void guest_login();
    void enableButton();
    ~Widget();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
