#include "mainwindowguest.h"
#include "ui_mainwindowguest.h"

mainwindowguest::mainwindowguest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainwindowguest)
{
    ui->setupUi(this);
    ui->logout->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->market->setStyleSheet("QPushButton{border:none;color:white}");


    QPalette pal(this->palette());
    pal.setColor(QPalette::Window,QColor(20,20,20)); //设置背景黑色
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    //商城
    Shopmall * mall = new Shopmall();
    ui->userWidgets->addWidget(mall);
    connect(ui->market,&QPushButton::clicked, this , &mainwindowguest::market_push);
    //登出
    connect(ui->logout, &QPushButton::clicked, this, &mainwindowguest::tologin);

    shopdetail_sailer *project_detail = new shopdetail_sailer(1);
    nowShop = project_detail;
    ui->userWidgets->addWidget(project_detail);
    connect(mall,SIGNAL(backIDsignal(int)) , this , SLOT(shopdetail(int)));
}

void mainwindowguest::shopdetail(int ID)//商品详细信息
{
    nowShop->changeView(ID);
    ui->userWidgets->setCurrentIndex(1);
}

void mainwindowguest::market_push()//商城点击
{
    ui->userWidgets->setCurrentIndex(0);
}

void mainwindowguest::tologin()//去登录
{
    Widget *Loginwindow = new Widget;
    Loginwindow->show();
    this->close();
}
mainwindowguest::~mainwindowguest()
{
    delete ui;
}
