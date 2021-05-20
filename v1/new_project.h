#ifndef NEW_PROJECT_H
#define NEW_PROJECT_H

#include <QWidget>
#include <QPalette>
#include <QApplication>
#include <QDebug>
#include "sqilteopreatorprojects.h"
#include "sqliteoperator.h"

namespace Ui {
class new_project;
}

class new_project : public QWidget
{
    Q_OBJECT

public:
    explicit new_project(QString userName,QWidget *parent = nullptr);
    ~new_project();
    QString nowName;
    void up_push();
    void enableButton();

private:
    Ui::new_project *ui;
};

#endif // NEW_PROJECT_H
