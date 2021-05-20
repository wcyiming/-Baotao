#include "mainwindowsailer.h"
#include "ui_mainwindowsailer.h"

mainWindowSailer::mainWindowSailer(QString sailerName,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainWindowSailer)
{
    ui->setupUi(this);
    ui->logout->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->market->setStyleSheet("QPushButton{border:none;color:white}");
    ui->changeMoney->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->useredit->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->managebt->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->newbt->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->useredit->setText(sailerName);
    nowName = sailerName;

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(sailerName);
    double packetMoney =(nowUser.Purse*1.0) /100;

    QString Moneystring = QString::number(packetMoney, 'f', 2);
    ui->changeMoney->setText(Moneystring);

    QPalette pal(this->palette());
    pal.setColor(QPalette::Window,QColor(20,20,20)); //设置背景黑色
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    //商城
    Shopmall * mall = new Shopmall();
    ui->userWidgets->addWidget(mall);   //0
    connect(ui->market,&QPushButton::clicked, this , &mainWindowSailer::market_push);

    //编辑密码
    username_sailer *nameedit =  new username_sailer(sailerName);
    ui->userWidgets->addWidget(nameedit);   //1
    connect(ui->useredit,&QPushButton::clicked, this , &mainWindowSailer::useredit_push);
    //登出
    connect(ui->logout, &QPushButton::clicked, this, &mainWindowSailer::tologin);
    //充值
    money_buyer *moneyChange =  new money_buyer(sailerName);
    ui->userWidgets->addWidget(moneyChange);     //2
    connect(ui->changeMoney,&QPushButton::clicked, this , &mainWindowSailer::changeMoney_push);
    connect(moneyChange , &money_buyer::backSignal , this , &mainWindowSailer::refreshMoney);

    //新建
    new_project *newProject = new new_project(sailerName);
    ui->userWidgets->addWidget(newProject);     //3
    connect(ui->newbt,&QPushButton::clicked, this , &mainWindowSailer::newbt_push);

    shopdetail_sailer *project_detail = new shopdetail_sailer(1);
    nowShop = project_detail;
    ui->userWidgets->addWidget(project_detail);   //4
    connect(mall,SIGNAL(backIDsignal(int)) , this , SLOT(shopdetail(int)));

    management *nowmanage = new management (sailerName);
    ui->userWidgets->addWidget(nowmanage);     //5
    connect(ui->managebt,&QPushButton::clicked, this , &mainWindowSailer::manage_push);

    managementDetail *manage_detail = new managementDetail();
    nowManagement = manage_detail;
    ui->userWidgets->addWidget(manage_detail);   //6
    connect(nowmanage,SIGNAL(backIDsignalManage(int)) , this , SLOT(managedetail(int)));



}

void mainWindowSailer::managedetail(int ID)
{
    ui->logout->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->market->setStyleSheet("QPushButton{border:none;color:white}");
    ui->changeMoney->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->useredit->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->managebt->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->newbt->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");

     qDebug() << "has change3";
     nowManagement->list_push(ID);
    ui->userWidgets->setCurrentIndex(6);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    double packetMoney = nowUser.Purse*1.0 /100;
    QString Moneystring = QString::number(packetMoney, 'f', 2);
    ui->changeMoney->setText(Moneystring);
}

void mainWindowSailer::manage_push()
{
    ui->logout->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->market->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->changeMoney->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->useredit->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->managebt->setStyleSheet("QPushButton{border:none;color:white}");
    ui->newbt->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->userWidgets->setCurrentIndex(5);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_sailer nowUser;
    nowUser = Accountdb.searchSailerQuery(nowName);
    double packetMoney = nowUser.Purse*1.0 /100;
    QString Moneystring = QString::number(packetMoney, 'f', 2);
    ui->changeMoney->setText(Moneystring);
}


void mainWindowSailer::shopdetail(int ID)
{
    ui->logout->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->market->setStyleSheet("QPushButton{border:none;color:white}");
    ui->changeMoney->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->useredit->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->managebt->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->newbt->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
     nowShop->changeView(ID);
     qDebug() << "has change";
    ui->userWidgets->setCurrentIndex(4);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    double packetMoney = nowUser.Purse*1.0 /100;
    QString Moneystring = QString::number(packetMoney, 'f', 2);
    ui->changeMoney->setText(Moneystring);
}

void mainWindowSailer::market_push()
{
    ui->logout->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->market->setStyleSheet("QPushButton{border:none;color:white}");
    ui->changeMoney->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->useredit->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->managebt->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->newbt->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->userWidgets->setCurrentIndex(0);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_sailer nowUser;
    nowUser = Accountdb.searchSailerQuery(nowName);
    double packetMoney = nowUser.Purse*1.0 /100;
    QString Moneystring = QString::number(packetMoney, 'f', 2);
    ui->changeMoney->setText(Moneystring);
}

void mainWindowSailer::newbt_push()
{
    ui->logout->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->market->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->changeMoney->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->useredit->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->managebt->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->newbt->setStyleSheet("QPushButton{border:none;color:white}");
    ui->userWidgets->setCurrentIndex(3);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_sailer nowUser;
    nowUser = Accountdb.searchSailerQuery(nowName);
    double packetMoney = nowUser.Purse*1.0 /100;
    QString Moneystring = QString::number(packetMoney, 'f', 2);
    ui->changeMoney->setText(Moneystring);
}

void mainWindowSailer::useredit_push()
{
    ui->logout->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->market->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->changeMoney->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->useredit->setStyleSheet("QPushButton{border:none;color:white}");
    ui->managebt->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->newbt->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->userWidgets->setCurrentIndex(1);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_sailer nowUser;
    nowUser = Accountdb.searchSailerQuery(nowName);
    double packetMoney = nowUser.Purse*1.0 /100;
    QString Moneystring = QString::number(packetMoney, 'f', 2);
    ui->changeMoney->setText(Moneystring);
}

void mainWindowSailer::refreshMoney()
{
    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_sailer nowUser;
    nowUser = Accountdb.searchSailerQuery(nowName);
    double packetMoney = nowUser.Purse*1.0 /100;
    QString Moneystring = QString::number(packetMoney, 'f', 2);
    ui->changeMoney->setText(Moneystring);
}

void mainWindowSailer::tologin()
{
    Widget *Loginwindow = new Widget;
    Loginwindow->show();
    this->close();
}

void mainWindowSailer::changeMoney_push()
{
    ui->logout->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->market->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->changeMoney->setStyleSheet("QPushButton{border:none;color:white}");
    ui->useredit->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->managebt->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->newbt->setStyleSheet("QPushButton{border:none;color:#A9A9A9}");
    ui->userWidgets->setCurrentIndex(2);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_sailer nowUser;
    nowUser = Accountdb.searchSailerQuery(nowName);
    double packetMoney = nowUser.Purse*1.0 /100;
    QString Moneystring = QString::number(packetMoney, 'f', 2);
    ui->changeMoney->setText(Moneystring);
}


mainWindowSailer::~mainWindowSailer()
{
    delete ui;
}
