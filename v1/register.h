#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QPalette>
#include <QApplication>
#include <fstream>
#include <cstdlib>
#include <QDataStream>
#include <QFile>
#include "widget.h"
#include "mainwindow.h"
#include "mainwindowguest.h"
#include "sqliteoperator.h"

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();
    void tologin();
    void Register_push();
    void guest_login();
    void enableButton();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
