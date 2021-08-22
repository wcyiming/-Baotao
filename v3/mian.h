#ifndef MIAN_H
#define MIAN_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class mian; }
QT_END_NAMESPACE

class mian : public QWidget
{
    Q_OBJECT

public:
    mian(QWidget *parent = nullptr);
    ~mian();

private:
    Ui::mian *ui;
};
#endif // MIAN_H
