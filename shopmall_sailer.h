#ifndef SHOPMALL_SAILER_H
#define SHOPMALL_SAILER_H

#include <QWidget>

namespace Ui {
class shopmall_sailer;
}

class shopmall_sailer : public QWidget
{
    Q_OBJECT

public:
    explicit shopmall_sailer(QWidget *parent = nullptr);
    ~shopmall_sailer();

private:
    Ui::shopmall_sailer *ui;
};

#endif // SHOPMALL_SAILER_H
