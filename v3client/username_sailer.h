#ifndef USERNAME_SAILER_H
#define USERNAME_SAILER_H

#include <QWidget>
#include <QPalette>
#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "sqliteoperator.h"

namespace Ui {
class username_sailer;
}

class username_sailer : public QWidget
{
    Q_OBJECT

public:
    explicit username_sailer(QString userName,QWidget *parent = nullptr);
    ~username_sailer();
    void change_push();
    void enableButton();
    QString nowName;

private:
    Ui::username_sailer *ui;
};

#endif // USERNAME_SAILER_H
