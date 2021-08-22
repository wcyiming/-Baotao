#include "mian.h"
#include "ui_mian.h"

mian::mian(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mian)
{
    ui->setupUi(this);
}

mian::~mian()
{
    delete ui;
}

