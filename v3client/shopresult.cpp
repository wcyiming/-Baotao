#include "shopresult.h"
#include "ui_shopresult.h"

shopResult::shopResult(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::shopResult)
{
    ui->setupUi(this);
    ui->success_lb->setStyleSheet("QLabel{color:rgb(85, 170, 0)}");
}

shopResult::~shopResult()
{
    delete ui;
}
