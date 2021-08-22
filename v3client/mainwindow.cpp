#include "mainwindow.h"
#include "ui_mainwindow.h"

Mainwindow::Mainwindow(QString userName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mainwindow)
{
    ui->setupUi(this);
    ui->logout->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->market->setStyleSheet("QPushButton{border:none;color:white}");
    ui->changeMoney->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->useredit->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->shoplist->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->useredit->setText(userName);
    nowName = userName;
    hasBuy = 0;

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(userName);
    double packetMoney =(nowUser.Purse*1.0) /100;

    QString Moneystring = QString::number(packetMoney, 'f', 2);
    ui->changeMoney->setText(Moneystring);

    QPalette pal(this->palette());
    pal.setColor(QPalette::Window,QColor(20,20,20)); //设置背景黑色
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    //商城
    Shopmall * mall = new Shopmall();
    ui->userWidgets->addWidget(mall);
    connect(ui->market,&QPushButton::clicked, this , &Mainwindow::market_push);
    //编辑密码
    username_buyer *nameedit =  new username_buyer(userName);
    ui->userWidgets->addWidget(nameedit);
    connect(ui->useredit,&QPushButton::clicked, this , &Mainwindow::useredit_push);
    //登出
    connect(ui->logout, &QPushButton::clicked, this, &Mainwindow::tologin);
    //充值
    money_buyer *moneyChange =  new money_buyer(userName);
    ui->userWidgets->addWidget(moneyChange);
    connect(ui->changeMoney,&QPushButton::clicked, this , &Mainwindow::changeMoney_push);
    connect(moneyChange , &money_buyer::backSignal , this , &Mainwindow::refreshMoney);
    //具体界面
    shopdetail_buyer *project_detail = new shopdetail_buyer(nowName ,1);
    nowShop = project_detail;
    ui->userWidgets->addWidget(project_detail);
    connect(mall,SIGNAL(backIDsignal(int)) , this , SLOT(shopdetail(int)));
    //  购物车界面
    shopList *now_shoplist = new shopList(nowName);
    nowList = now_shoplist;
    ui->userWidgets->addWidget(now_shoplist);
    connect(ui->shoplist ,&QPushButton::clicked, this , &Mainwindow::shoplist_push);

    //结算界面
    balance *nowBalance = new balance(nowName);
    nowCheck = nowBalance;
    ui->userWidgets->addWidget(nowBalance);
    connect(now_shoplist, &shopList::backSendSignal , this , &Mainwindow::check);

    //结算结果
    shopResult *nowResult = new shopResult();
    ui->userWidgets->addWidget(nowResult);
    connect(nowBalance, &balance::backBuySignal , this , &Mainwindow::checksuccess);
    connect(nowBalance, &balance::backRefreshSignal , this , &Mainwindow::checkfail);

}

void Mainwindow::checkfail()//删除订单
{
    ui->logout->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->market->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->changeMoney->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->useredit->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->shoplist->setStyleSheet("QPushButton{border:none;color:white}");
    ui->userWidgets->setCurrentIndex(4);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    double packetMoney = nowUser.Purse*1.0 /100;
    QString Moneystring = QString::number(packetMoney, 'f', 2);
    ui->changeMoney->setText(Moneystring);
}

void Mainwindow::checksuccess()//购买成功
{
    ui->logout->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->market->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->changeMoney->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->useredit->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->shoplist->setStyleSheet("QPushButton{border:none;color:white}");
    hasBuy = 0;
    ui->userWidgets->setCurrentIndex(6);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    double packetMoney = nowUser.Purse*1.0 /100;
    QString Moneystring = QString::number(packetMoney, 'f', 2);
    ui->changeMoney->setText(Moneystring);
}

void Mainwindow::check()//生成订单
{
    ui->logout->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->market->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->changeMoney->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->useredit->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->shoplist->setStyleSheet("QPushButton{border:none;color:white}");
    hasBuy = 1;
    nowCheck->noSearch();
    ui->userWidgets->setCurrentIndex(5);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    double packetMoney = nowUser.Purse*1.0 /100;
    QString Moneystring = QString::number(packetMoney, 'f', 2);
    ui->changeMoney->setText(Moneystring);
}

void Mainwindow::shoplist_push()//点击购物车
{
    ui->logout->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->market->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->changeMoney->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->useredit->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->shoplist->setStyleSheet("QPushButton{border:none;color:white}");
    if(hasBuy)
    {
        ui->userWidgets->setCurrentIndex(5);
    }
    else
    {
        ui->userWidgets->setCurrentIndex(4);
        nowList->noSearch();
    }
    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    double packetMoney = nowUser.Purse*1.0 /100;
    QString Moneystring = QString::number(packetMoney, 'f', 2);
    ui->changeMoney->setText(Moneystring);
}

void Mainwindow::shopdetail(int ID)//调用具体界面
{
    ui->logout->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->market->setStyleSheet("QPushButton{border:none;color:white}");
    ui->changeMoney->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->useredit->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
     ui->shoplist->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
     qDebug() << "has change";
     nowShop->changeView(ID);
    ui->userWidgets->setCurrentIndex(3);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    double packetMoney = nowUser.Purse*1.0 /100;
    QString Moneystring = QString::number(packetMoney, 'f', 2);
    ui->changeMoney->setText(Moneystring);
}

void Mainwindow::market_push()//点击商城
{
    ui->logout->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->market->setStyleSheet("QPushButton{border:none;color:white}");
    ui->changeMoney->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->useredit->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
     ui->shoplist->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->userWidgets->setCurrentIndex(0);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    double packetMoney = nowUser.Purse*1.0 /100;
    QString Moneystring = QString::number(packetMoney, 'f', 2);
    ui->changeMoney->setText(Moneystring);
}

void Mainwindow::useredit_push()//点击用户编辑
{
    ui->logout->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->market->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->changeMoney->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->useredit->setStyleSheet("QPushButton{border:none;color:white}");
    ui->shoplist->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->userWidgets->setCurrentIndex(1);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    double packetMoney = nowUser.Purse*1.0 /100;
    QString Moneystring = QString::number(packetMoney, 'f', 2);
    ui->changeMoney->setText(Moneystring);
}

void Mainwindow::refreshMoney()//刷新价格
{
    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    double packetMoney = nowUser.Purse*1.0 /100;
    QString Moneystring = QString::number(packetMoney, 'f', 2);
    ui->changeMoney->setText(Moneystring);
}

void Mainwindow::tologin()//登出
{
    Widget *Loginwindow = new Widget;
    Loginwindow->show();
    this->close();
}

void Mainwindow::changeMoney_push()//充值
{
    ui->logout->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->market->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->changeMoney->setStyleSheet("QPushButton{border:none;color:white}");
    ui->useredit->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->shoplist->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->userWidgets->setCurrentIndex(2);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    double packetMoney = nowUser.Purse*1.0 /100;
    QString Moneystring = QString::number(packetMoney, 'f', 2);
    ui->changeMoney->setText(Moneystring);
}

Mainwindow::~Mainwindow()
{
    delete ui;
}
