#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->usernameLabel->setStyleSheet("QLabel{color:white}");
    ui->passwordLabel->setStyleSheet("QLabel{color:white}");
    ui->log_in->setStyleSheet("QPushButton{color:#A9A9A9}");
    ui->Register->setStyleSheet("QPushButton{border:none;color:white}");
    ui->GUIST->setStyleSheet("QPushButton{border:none;color:white}");
    ui->wronguser->setStyleSheet("QLabel{color:red}");
    ui->wronguser->setVisible(false);
    ui->wrongps->setStyleSheet("QLabel{color:red}");
    ui->wrongps->setVisible(false);
    QPalette pal(this->palette());
    pal.setColor(QPalette::Window,QColor(20,20,20)); //设置背景黑色
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    connect(ui->Register, &QPushButton::clicked, this, &Widget::toRegister);
    connect(ui->GUIST,&QPushButton::clicked, this , &Widget::guest_login);

    connect(ui->username, &QLineEdit::textChanged, this , &Widget::enableButton);
    connect(ui->password, &QLineEdit::textChanged, this , &Widget::enableButton);
    connect(ui->log_in,&QPushButton::clicked, this , &Widget::Login);

}

void Widget::toRegister()
{
    Register *reg = new Register;
    reg->show();
    this->close();
}

void Widget::enableButton()
{
    bool useOK,passOK;
    useOK = !ui->username->text().isEmpty();
    passOK = !ui->password->text().isEmpty();
    ui->log_in->setEnabled(useOK && passOK);
    if( useOK && passOK)
    {
        ui->log_in->setCursor(QCursor(Qt::PointingHandCursor));
        ui->log_in->setStyleSheet("QPushButton{color:white ; background-color:rgb(0,170,255)}");
    }

    else {
        ui->log_in->setStyleSheet("QPushButton{color:#A9A9A9; background-color:rgb(40,40,40)}");
        ui->log_in->setCursor(QCursor(Qt::ArrowCursor));
    }
}

void Widget::guest_login()
{
    mainwindowguest *window = new mainwindowguest();
    window->show();
    this->close();
}

void Widget::Login()
{
    ui->wronguser->setVisible(false);
    ui->wrongps->setVisible(false);
    QString namestring = ui->username->text();
    QString passwordstring = ui->password->text();
    SqliteOperator Accountdb;
    Accountdb.openDb();
    int flag = Accountdb.ifquery(namestring);
    if(!flag)
    {
        ui->wronguser->setVisible(true);
    }
    else
    {
        if (flag == 1)
        {
            Account_user nowUser;
            nowUser = Accountdb.searchUserQuery(namestring);
            if (nowUser.Password.compare(passwordstring))
            {
                ui->wrongps->setVisible(true);
            }
            else
            {
                 Mainwindow *window = new Mainwindow(namestring);
                 window->show();
                 this->close();
            }
        }
        else
        {
            Account_sailer nowSailer;
            nowSailer = Accountdb.searchSailerQuery(namestring);
            if (nowSailer.Password.compare(passwordstring))
            {
                ui->wrongps->setVisible(true);
            }
            else
            {
                 mainWindowSailer *windows = new mainWindowSailer(namestring);
                 windows->show();
                 this->close();
            }
        }
    }

}
Widget::~Widget()
{
    delete ui;
}

