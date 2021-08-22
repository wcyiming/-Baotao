#ifndef SHOPRESULT_H
#define SHOPRESULT_H

#include <QWidget>

namespace Ui {
class shopResult;
}

class shopResult : public QWidget             //购买成功界面
{
    Q_OBJECT

public:
    explicit shopResult(QWidget *parent = nullptr);
    ~shopResult();

private:
    Ui::shopResult *ui;
};

#endif // SHOPRESULT_H
