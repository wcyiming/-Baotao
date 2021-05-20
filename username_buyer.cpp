#include "username_buyer.h"
#include "ui_username_buyer.h"

username_buyer::username_buyer(QString userName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::username_buyer)
{
    ui->setupUi(this);
    ui->oldPSLabel->setStyleSheet("QLabel{color:white}");
    ui->newPSLable->setStyleSheet("QLabel{color:white}");
    ui->newPSLable2->setStyleSheet("QLabel{color:white}");
    ui->change->setStyleSheet("QPushButton{color:#A9A9A9}");

    ui->differPS->setStyleSheet("QLabel{color:red}");
    ui->differPS->setVisible(false);
    ui->wrongPS->setStyleSheet("QLabel{color:red}");
    ui->wrongPS->setVisible(false);
    ui->changeSuccess->setStyleSheet("QLabel{color:green}");
    ui->changeSuccess->setVisible(false);
    ui->changeFail->setStyleSheet("QLabel{color:red}");
    ui->changeFail->setVisible(false);
    this ->nowName = userName;

    connect(ui->oldPS, &QLineEdit::textChanged, this , &username_buyer::enableButton);
    connect(ui->newPS, &QLineEdit::textChanged, this , &username_buyer::enableButton);
    connect(ui->newPS2, &QLineEdit::textChanged, this , &username_buyer::enableButton);

    connect(ui->change,&QPushButton::clicked, this , &username_buyer::change_push);
}

void username_buyer::enableButton()
{
    bool useOK,passOK,passOK2;
    useOK = !ui->oldPS->text().isEmpty();
    passOK = !ui->newPS->text().isEmpty();
    passOK2 = !ui->newPS2->text().isEmpty();
    ui->change->setEnabled(useOK && passOK && passOK2);
    if( useOK && passOK && passOK2)
    {
        ui->change->setCursor(QCursor(Qt::PointingHandCursor));
        ui->change->setStyleSheet("QPushButton{color:white ; background-color:rgb(85, 170, 0)}");
    }

    else {
        ui->change->setStyleSheet("QPushButton{color:#A9A9A9; background-color:rgb(40,40,40)}");
        ui->change->setCursor(QCursor(Qt::ArrowCursor));
    }
}

void username_buyer::change_push()
{
    ui->wrongPS->setVisible(false);
    ui->differPS->setVisible(false);
    ui->changeFail->setVisible(false);
    ui->changeSuccess->setVisible(false);
    QString oldstring = ui->oldPS->text();
    QString passwordstring = ui->newPS->text();
    QString passwordstring2 = ui->newPS2->text();
    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    qDebug("nowUser = %s",qPrintable(nowUser.Password));
    qDebug("nowUser = %s",qPrintable(oldstring));
    if(oldstring.compare(nowUser.Password))
    {
        ui->wrongPS->setVisible(true);

    }
    else if(passwordstring.compare(passwordstring2))
    {
        ui->differPS->setVisible(true);
    }
    else
    {
        nowUser.Password = passwordstring;
        bool flag;
        flag = Accountdb.modifyUserData(nowUser);
        if(flag)
        {
            ui->changeFail->setVisible(true);
            ui->changeSuccess->setVisible(false);
        }
        else
        {
            ui->changeFail->setVisible(false);
            ui->changeSuccess->setVisible(true);
        }
    }

}
username_buyer::~username_buyer()
{
    delete ui;
}
