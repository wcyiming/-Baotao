#include "shopmall_sailer.h"
#include "ui_shopmall_sailer.h"

shopmall_sailer::shopmall_sailer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::shopmall_sailer)
{
    ui->setupUi(this);
}

shopmall_sailer::~shopmall_sailer()
{
    delete ui;
}
