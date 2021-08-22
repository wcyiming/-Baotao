#include "widget.h"

#include <QApplication>
QString ClientJWT;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
