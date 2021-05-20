#ifndef SHOPMALL_H
#define SHOPMALL_H

#include <QWidget>
#include <QApplication>
#include <QDebug>
#include <QSize>
#include "sqilteopreatorprojects.h"
#include "projectpreview.h"
#include <QListWidgetItem>

namespace Ui {
class Shopmall;
}

class Shopmall : public QWidget
{
    Q_OBJECT

public:
    explicit Shopmall(QWidget *parent = nullptr);
    ~Shopmall();
    void noSearch();
    void search_push();
    int nowFather;
    void onListItemClicked();

    std::vector<int> w_list;

public slots:
    void onListItemClicked(QListWidgetItem *item);

signals:
    void backIDsignal(int ID);

private:
    Ui::Shopmall *ui;
};

#endif // SHOPMALL_H
