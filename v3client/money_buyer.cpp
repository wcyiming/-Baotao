#include "money_buyer.h"
#include "ui_money_buyer.h"

money_buyer::money_buyer(QString userName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::money_buyer)
{
    ui->setupUi(this);
    nowName = userName;

    ui->chongSuccess->setStyleSheet("QLabel{color:green}");
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setStyleSheet("QLabel{color:red}");
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setStyleSheet("QLabel{color:green}");
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setStyleSheet("QLabel{color:red}");
    ui->tiFail->setVisible(false);

    ui->chonglb->setStyleSheet("QLabel{color:white}");
    ui->chongbt->setStyleSheet("QPushButton{color:white;background-color:rgb(85, 170, 0)}");
    ui->chongLine->setValidator(new QDoubleValidator(0,99999,2,this));

    ui->ti_lb->setStyleSheet("QLabel{color:white}");
    ui->ti_bt->setStyleSheet("QPushButton{color:white;background-color:rgb(85, 170, 0)}");
    ui->ti_line->setValidator(new QDoubleValidator(0,99999,2,this));

    ui->chong30_lb1->setStyleSheet("QLabel{color:white}");
    ui->chong30_lb2->setStyleSheet("QLabel{color:white}");
    ui->chong30_bt->setStyleSheet("QPushButton{color:white;background-color:rgb(85, 170, 0)}");

    ui->chong60_lb1->setStyleSheet("QLabel{color:white}");
    ui->chong60_lb2->setStyleSheet("QLabel{color:white}");
    ui->chong60_bt->setStyleSheet("QPushButton{color:white;background-color:rgb(85, 170, 0)}");

    ui->chong150_lb1->setStyleSheet("QLabel{color:white}");
    ui->chong150_lb2->setStyleSheet("QLabel{color:white}");
    ui->chong150_bt->setStyleSheet("QPushButton{color:white;background-color:rgb(85, 170, 0)}");

    ui->chong300_lb1->setStyleSheet("QLabel{color:white}");
    ui->chong300_lb2->setStyleSheet("QLabel{color:white}");
    ui->chong300_bt->setStyleSheet("QPushButton{color:white;background-color:rgb(85, 170, 0)}");

    ui->chong600_lb1->setStyleSheet("QLabel{color:white}");
    ui->chong600_lb2->setStyleSheet("QLabel{color:white}");
    ui->chong600_bt->setStyleSheet("QPushButton{color:white;background-color:rgb(85, 170, 0)}");

    ui->ti30_lb1->setStyleSheet("QLabel{color:white}");
    ui->ti30_lb2->setStyleSheet("QLabel{color:white}");
    ui->ti30_bt->setStyleSheet("QPushButton{color:white;background-color:rgb(85, 170, 0)}");

    ui->ti60_lb1->setStyleSheet("QLabel{color:white}");
    ui->ti60_lb2->setStyleSheet("QLabel{color:white}");
    ui->ti60_bt->setStyleSheet("QPushButton{color:white;background-color:rgb(85, 170, 0)}");

    ui->ti150_lb1->setStyleSheet("QLabel{color:white}");
    ui->ti150_lb2->setStyleSheet("QLabel{color:white}");
    ui->ti150_bt->setStyleSheet("QPushButton{color:white;background-color:rgb(85, 170, 0)}");

    ui->ti300_lb1->setStyleSheet("QLabel{color:white}");
    ui->ti300_lb2->setStyleSheet("QLabel{color:white}");
    ui->ti300_bt->setStyleSheet("QPushButton{color:white;background-color:rgb(85, 170, 0)}");

    ui->ti600_lb1->setStyleSheet("QLabel{color:white}");
    ui->ti600_lb2->setStyleSheet("QLabel{color:white}");
    ui->ti600_bt->setStyleSheet("QPushButton{color:white;background-color:rgb(85, 170, 0)}");

    connect(ui->chongbt,&QPushButton::clicked, this , &money_buyer::chong_number);
    connect(ui->chongbt,&QPushButton::clicked, this , &money_buyer::sendChange);

    connect(ui->chong30_bt,&QPushButton::clicked, this , &money_buyer::chong_30);
    connect(ui->chong30_bt,&QPushButton::clicked, this , &money_buyer::sendChange);

    connect(ui->chong60_bt,&QPushButton::clicked, this , &money_buyer::chong_60);
    connect(ui->chong60_bt,&QPushButton::clicked, this , &money_buyer::sendChange);

    connect(ui->chong150_bt,&QPushButton::clicked, this , &money_buyer::chong_150);
    connect(ui->chong150_bt,&QPushButton::clicked, this , &money_buyer::sendChange);

    connect(ui->chong300_bt,&QPushButton::clicked, this , &money_buyer::chong_300);
    connect(ui->chong300_bt,&QPushButton::clicked, this , &money_buyer::sendChange);

    connect(ui->chong600_bt,&QPushButton::clicked, this , &money_buyer::chong_600);
    connect(ui->chong600_bt,&QPushButton::clicked, this , &money_buyer::sendChange);

    connect(ui->ti_bt,&QPushButton::clicked, this , &money_buyer::ti_number);
    connect(ui->ti_bt,&QPushButton::clicked, this , &money_buyer::sendChange);

    connect(ui->ti30_bt,&QPushButton::clicked, this , &money_buyer::ti_30);
    connect(ui->ti30_bt,&QPushButton::clicked, this , &money_buyer::sendChange);

    connect(ui->ti60_bt,&QPushButton::clicked, this , &money_buyer::ti_60);
    connect(ui->ti60_bt,&QPushButton::clicked, this , &money_buyer::sendChange);

    connect(ui->ti150_bt,&QPushButton::clicked, this , &money_buyer::ti_150);
    connect(ui->ti150_bt,&QPushButton::clicked, this , &money_buyer::sendChange);

    connect(ui->ti300_bt,&QPushButton::clicked, this , &money_buyer::ti_300);
    connect(ui->ti300_bt,&QPushButton::clicked, this , &money_buyer::sendChange);

    connect(ui->ti600_bt,&QPushButton::clicked, this , &money_buyer::ti_600);
    connect(ui->ti600_bt,&QPushButton::clicked, this , &money_buyer::sendChange);



}

void money_buyer::sendChange() //每次更新主界面的用户价钱
{
    emit backSignal();
}

void money_buyer::chong_number()  //冲指定价格
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);
    QString moneyString = ui->chongLine->text();
    int newMoney = moneyString.toDouble()*100;

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    nowUser.Purse += newMoney;
    qDebug("nowUser = %d",nowUser.Purse);

    bool flag = Accountdb.modifyUserData(nowUser);
    if (!flag)
    {
        ui->chongSuccess->setVisible(true);
        ui->chongFail->setVisible(false);
    }
    else
    {
        ui->chongFail->setVisible(true);
        ui->chongSuccess->setVisible(false);
    }
}


void money_buyer::chong_30()
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    nowUser.Purse += 3000;
    bool flag = Accountdb.modifyUserData(nowUser);
    if (!flag)
    {
        ui->chongSuccess->setVisible(true);
        ui->chongFail->setVisible(false);
    }
    else
    {
        ui->chongFail->setVisible(true);
        ui->chongSuccess->setVisible(false);
    }
}

void money_buyer::chong_60()
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    nowUser.Purse += 6000;
    bool flag = Accountdb.modifyUserData(nowUser);
    if (!flag)
    {
        ui->chongSuccess->setVisible(true);
        ui->chongFail->setVisible(false);
    }
    else
    {
        ui->chongFail->setVisible(true);
        ui->chongSuccess->setVisible(false);
    }
}

void money_buyer::chong_150()
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    nowUser.Purse += 15000;
    bool flag = Accountdb.modifyUserData(nowUser);
    if (!flag)
    {
        ui->chongSuccess->setVisible(true);
        ui->chongFail->setVisible(false);
    }
    else
    {
        ui->chongFail->setVisible(true);
        ui->chongSuccess->setVisible(false);
    }
}

void money_buyer::chong_300()
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    nowUser.Purse += 30000;
    bool flag = Accountdb.modifyUserData(nowUser);
    if (!flag)
    {
        ui->chongSuccess->setVisible(true);
        ui->chongFail->setVisible(false);
    }
    else
    {
        ui->chongFail->setVisible(true);
        ui->chongSuccess->setVisible(false);
    }
}

void money_buyer::chong_600()
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    nowUser.Purse += 60000;
    bool flag = Accountdb.modifyUserData(nowUser);
    if (!flag)
    {
        ui->chongSuccess->setVisible(true);
        ui->chongFail->setVisible(false);
    }
    else
    {
        ui->chongFail->setVisible(true);
        ui->chongSuccess->setVisible(false);
    }
}
void money_buyer::ti_number()  //提现指定数字
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);
    QString moneyString = ui->ti_line->text();
    int newMoney = moneyString.toDouble()*100;

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    if(nowUser.Purse < newMoney)
    {
        ui->tiFail->setVisible(true);
        ui->tiSuccess->setVisible(false);
    }
    else
    {
    nowUser.Purse -= newMoney;
    bool flag = Accountdb.modifyUserData(nowUser);
    if (!flag)
    {
        ui->tiSuccess->setVisible(true);
        ui->tiFail->setVisible(false);
    }
    else
    {
        ui->tiFail->setVisible(true);
        ui->tiSuccess->setVisible(false);
    }
    }
}


void money_buyer::ti_30()
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    if(nowUser.Purse < 3000)
    {
        ui->tiFail->setVisible(true);
        ui->tiSuccess->setVisible(false);
    }
    else
    {
        nowUser.Purse -= 3000;
        bool flag = Accountdb.modifyUserData(nowUser);
        if (!flag)
        {
            ui->tiSuccess->setVisible(true);
            ui->tiFail->setVisible(false);
        }
        else
        {
            ui->tiFail->setVisible(true);
            ui->tiSuccess->setVisible(false);
        }
    }
}

void money_buyer::ti_60()
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    if(nowUser.Purse < 6000)
    {
        ui->tiFail->setVisible(true);
    }
    else
    {
        nowUser.Purse -= 6000;
        bool flag = Accountdb.modifyUserData(nowUser);
        if (!flag)
        {
            ui->tiSuccess->setVisible(true);
            ui->tiFail->setVisible(false);
        }
        else
        {
            ui->tiFail->setVisible(true);
            ui->tiSuccess->setVisible(false);
        }
    }
}

void money_buyer::ti_150()
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    if(nowUser.Purse < 15000)
    {
        ui->tiFail->setVisible(true);
    }
    else
    {
        nowUser.Purse -= 15000;
        bool flag = Accountdb.modifyUserData(nowUser);
        if (!flag)
        {
            ui->tiSuccess->setVisible(true);
            ui->tiFail->setVisible(false);
        }
        else
        {
            ui->tiFail->setVisible(true);
            ui->tiSuccess->setVisible(false);
        }
    }
}

void money_buyer::ti_300()
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    if(nowUser.Purse < 30000)
    {
        ui->tiFail->setVisible(true);
    }
    else
    {
        nowUser.Purse -= 30000;
        bool flag = Accountdb.modifyUserData(nowUser);
        if (!flag)
        {
            ui->tiSuccess->setVisible(true);
            ui->tiFail->setVisible(false);
        }
        else
        {
            ui->tiFail->setVisible(true);
            ui->tiSuccess->setVisible(false);
        }
    }
}

void money_buyer::ti_600()
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    if(nowUser.Purse < 60000)
    {
        ui->tiFail->setVisible(true);
        ui->tiSuccess->setVisible(false);
    }
    else
    {
        nowUser.Purse -= 60000;
        bool flag = Accountdb.modifyUserData(nowUser);
        if (!flag)
        {
            ui->tiSuccess->setVisible(true);
            ui->tiFail->setVisible(false);
        }
        else
        {
            ui->tiFail->setVisible(true);
            ui->tiSuccess->setVisible(false);
        }
    }
}
money_buyer::~money_buyer()
{
    delete ui;
}
