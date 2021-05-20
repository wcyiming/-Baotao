#include "money_sailer.h"
#include "ui_money_sailer.h"

money_sailer::money_sailer(QString userName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::money_sailer)
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

    connect(ui->chongbt,&QPushButton::clicked, this , &money_sailer::chong_number);
    connect(ui->chongbt,&QPushButton::clicked, this , &money_sailer::sendChange);

    connect(ui->chong30_bt,&QPushButton::clicked, this , &money_sailer::chong_30);
    connect(ui->chong30_bt,&QPushButton::clicked, this , &money_sailer::sendChange);

    connect(ui->chong60_bt,&QPushButton::clicked, this , &money_sailer::chong_60);
    connect(ui->chong60_bt,&QPushButton::clicked, this , &money_sailer::sendChange);

    connect(ui->chong150_bt,&QPushButton::clicked, this , &money_sailer::chong_150);
    connect(ui->chong150_bt,&QPushButton::clicked, this , &money_sailer::sendChange);

    connect(ui->chong300_bt,&QPushButton::clicked, this , &money_sailer::chong_300);
    connect(ui->chong300_bt,&QPushButton::clicked, this , &money_sailer::sendChange);

    connect(ui->chong600_bt,&QPushButton::clicked, this , &money_sailer::chong_600);
    connect(ui->chong600_bt,&QPushButton::clicked, this , &money_sailer::sendChange);

    connect(ui->ti_bt,&QPushButton::clicked, this , &money_sailer::ti_number);
    connect(ui->ti_bt,&QPushButton::clicked, this , &money_sailer::sendChange);

    connect(ui->ti30_bt,&QPushButton::clicked, this , &money_sailer::ti_30);
    connect(ui->ti30_bt,&QPushButton::clicked, this , &money_sailer::sendChange);

    connect(ui->ti60_bt,&QPushButton::clicked, this , &money_sailer::ti_60);
    connect(ui->ti60_bt,&QPushButton::clicked, this , &money_sailer::sendChange);

    connect(ui->ti150_bt,&QPushButton::clicked, this , &money_sailer::ti_150);
    connect(ui->ti150_bt,&QPushButton::clicked, this , &money_sailer::sendChange);

    connect(ui->ti300_bt,&QPushButton::clicked, this , &money_sailer::ti_300);
    connect(ui->ti300_bt,&QPushButton::clicked, this , &money_sailer::sendChange);

    connect(ui->ti600_bt,&QPushButton::clicked, this , &money_sailer::ti_600);
    connect(ui->ti600_bt,&QPushButton::clicked, this , &money_sailer::sendChange);



}

void money_sailer::sendChange()
{
    emit backSignal();
}

void money_sailer::chong_number()
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);
    QString moneyString = ui->chongLine->text();
    int newMoney = moneyString.toDouble()*100;

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_sailer nowUser;
    nowUser = Accountdb.searchSailerQuery(nowName);
    nowUser.Purse += newMoney;
    qDebug("nowUser = %d",nowUser.Purse);

    bool flag = Accountdb.modifySailerData(nowUser);
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


void money_sailer::chong_30()
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_sailer nowUser;
    nowUser = Accountdb.searchSailerQuery(nowName);
    nowUser.Purse += 3000;
    bool flag = Accountdb.modifySailerData(nowUser);
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

void money_sailer::chong_60()
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_sailer nowUser;
    nowUser = Accountdb.searchSailerQuery(nowName);
    nowUser.Purse += 6000;
    bool flag = Accountdb.modifySailerData(nowUser);
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

void money_sailer::chong_150()
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_sailer nowUser;
    nowUser = Accountdb.searchSailerQuery(nowName);
    nowUser.Purse += 15000;
    bool flag = Accountdb.modifySailerData(nowUser);
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

void money_sailer::chong_300()
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_sailer nowUser;
    nowUser = Accountdb.searchSailerQuery(nowName);
    nowUser.Purse += 30000;
    bool flag = Accountdb.modifySailerData(nowUser);
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

void money_sailer::chong_600()
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_sailer nowUser;
    nowUser = Accountdb.searchSailerQuery(nowName);
    nowUser.Purse += 60000;
    bool flag = Accountdb.modifySailerData(nowUser);
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
void money_sailer::ti_number()
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);
    QString moneyString = ui->ti_line->text();
    int newMoney = moneyString.toDouble()*100;

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_sailer nowUser;
    nowUser = Accountdb.searchSailerQuery(nowName);
    if(nowUser.Purse < newMoney)
    {
        ui->tiFail->setVisible(true);
        ui->tiSuccess->setVisible(false);
    }
    else
    {

    nowUser.Purse -= newMoney;
    bool flag = Accountdb.modifySailerData(nowUser);
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


void money_sailer::ti_30()
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_sailer nowUser;
    nowUser = Accountdb.searchSailerQuery(nowName);
    if(nowUser.Purse < 3000)
    {
        ui->tiFail->setVisible(true);
        ui->tiSuccess->setVisible(false);
    }
    else
    {
        nowUser.Purse -= 3000;
        bool flag = Accountdb.modifySailerData(nowUser);
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

void money_sailer::ti_60()
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_sailer nowUser;
    nowUser = Accountdb.searchSailerQuery(nowName);
    if(nowUser.Purse < 6000)
    {
        ui->tiFail->setVisible(true);
        ui->tiSuccess->setVisible(false);
    }
    else
    {
        nowUser.Purse -= 6000;
        bool flag = Accountdb.modifySailerData(nowUser);
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

void money_sailer::ti_150()
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_sailer nowUser;
    nowUser = Accountdb.searchSailerQuery(nowName);
    if(nowUser.Purse < 15000)
    {
        ui->tiFail->setVisible(true);
        ui->tiSuccess->setVisible(false);
    }
    else
    {
        nowUser.Purse -= 15000;
        bool flag = Accountdb.modifySailerData(nowUser);
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

void money_sailer::ti_300()
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_sailer nowUser;
    nowUser = Accountdb.searchSailerQuery(nowName);
    if(nowUser.Purse < 30000)
    {
        ui->tiFail->setVisible(true);
        ui->tiSuccess->setVisible(false);
    }
    else
    {
        nowUser.Purse -= 30000;
        bool flag = Accountdb.modifySailerData(nowUser);
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

void money_sailer::ti_600()
{
    ui->chongSuccess->setVisible(false);
    ui->chongFail->setVisible(false);
    ui->tiSuccess->setVisible(false);
    ui->tiFail->setVisible(false);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_sailer nowUser;
    nowUser = Accountdb.searchSailerQuery(nowName);
    if(nowUser.Purse < 60000)
    {
        ui->tiFail->setVisible(true);
        ui->tiSuccess->setVisible(false);
    }
    else
    {
        nowUser.Purse -= 60000;
        bool flag = Accountdb.modifySailerData(nowUser);
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

money_sailer::~money_sailer()
{
    delete ui;
}
