#ifndef PROJECTPREVIEW_H
#define PROJECTPREVIEW_H

#include <QWidget>
#include <QPalette>
#include <QApplication>
#include <QDebug>
#include "sqilteopreatorprojects.h"

namespace Ui {
class projectPreview;
}

class projectPreview : public QWidget
{
    Q_OBJECT

public:
    explicit projectPreview(int projectID,QWidget *parent = nullptr);
    ~projectPreview();

private:
    Ui::projectPreview *ui;
};

#endif // PROJECTPREVIEW_H
