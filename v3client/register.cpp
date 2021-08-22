#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    ui->usernameLabel->setStyleSheet("QLabel{color:white}");
    ui->passwordLabel->setStyleSheet("QLabel{color:white}");
    ui->passwordLabel_2->setStyleSheet("QLabel{color:white}");
    ui->typeLabel->setStyleSheet("QLabel{color:white}");
    ui->Register_2->setStyleSheet("QPushButton{color:#A9A9A9}");
    ui->login->setStyleSheet("QPushButton{border:none;color:white}");
    ui->GUIST->setStyleSheet("QPushButton{border:none;color:white}");

    ui->difpass->setStyleSheet("QLabel{color:red}");
    ui->difpass->setVisible(false);
    ui->hasuser->setStyleSheet("QLabel{color:red}");
    ui->hasuser->setVisible(false);
    ui->regSuccess->setStyleSheet("QLabel{color:green}");
    ui->regSuccess->setVisible(false);
    ui->regFail->setStyleSheet("QLabel{color:red}");
    ui->regFail->setVisible(false);

    QPalette pal(this->palette());
    pal.setColor(QPalette::Window,QColor(20,20,20)); //设置背景黑色
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    connect(ui->login, &QPushButton::clicked, this, &Register::tologin);
    connect(ui->GUIST,&QPushButton::clicked, this , &Register::guest_login);

    connect(ui->username, &QLineEdit::textChanged, this , &Register::enableButton);
    connect(ui->password, &QLineEdit::textChanged, this , &Register::enableButton);
    connect(ui->password_2, &QLineEdit::textChanged, this , &Register::enableButton);

    connect(ui->Register_2,&QPushButton::clicked, this , &Register::Register_push);
}

void Register::tologin()  //前往登录
{
    Widget *Loginwindow = new Widget;
    Loginwindow->show();
    this->close();
}

void Register::enableButton()  //注册使能
{
    bool useOK,passOK,passOK2;
    useOK = !ui->username->text().isEmpty();
    passOK = !ui->password->text().isEmpty();
    passOK2 = !ui->password_2->text().isEmpty();
    ui->Register_2->setEnabled(useOK && passOK && passOK2);
    if( useOK && passOK && passOK2)
    {
        ui->Register_2->setCursor(QCursor(Qt::PointingHandCursor));
        ui->Register_2->setStyleSheet("QPushButton{color:white ; background-color:rgb(0,170,255)}");
    }

    else {
        ui->Register_2->setStyleSheet("QPushButton{color:#A9A9A9; background-color:rgb(40,40,40)}");
        ui->Register_2->setCursor(QCursor(Qt::ArrowCursor));
    }
}

void Register::guest_login()  //游客登录
{
    mainwindowguest *window = new mainwindowguest();
    window->show();
    this->close();
}

void Register::Register_push()   //点击后提交槽
{
    ui->hasuser->setVisible(false);
    ui->difpass->setVisible(false);
    ui->regSuccess->setVisible(false);
    ui->regFail->setVisible(false);
    QString namestring = ui->username->text();
    QString passwordstring = ui->password->text();
    QString passwordstring2 = ui->password_2->text();

    QFile file;
    QDataStream stream;
    file.setFileName("persondata.dat");
    if(true == file.exists())
    {
        bool isOpen = file.open(QIODevice::WriteOnly);
        if(isOpen == true)
        {
            stream.setDevice(&file);
            stream << namestring;
            file.close();
        }
        else
        {
            qDebug("文件打开失败");
        }
    }
    QString fileName;
    if(true == file.exists())
    {
        bool isOpen = file.open(QIODevice::ReadOnly);
        if(isOpen == true)
        {
            stream.setDevice(&file);
            stream >> fileName;
            file.close();
        }
        else
        {
            qDebug("文件打开失败");
        }
    }

    SqliteOperator Accountdb;
    Accountdb.openDb();
    int flag = Accountdb.ifquery(namestring);
    if(flag)
    {
        ui->hasuser->setVisible(true);

    }
    else if(passwordstring.compare(passwordstring2))
    {
        ui->difpass->setVisible(true);

    }
    else
    {
        if (ui->types->currentText().compare("商家"))
        {
            Account_user newUser;
            newUser.ID = Accountdb.searchMaxID() ;
            qDebug (" id = %d", newUser.ID);
            newUser.Name = namestring;
            newUser.Password = passwordstring;
            newUser.Purse = 0;
            newUser.Type = 1;
            bool flag;



            //文件输入输出
            flag=Accountdb.userInsertData(newUser);
            qDebug (" id2 = %d", newUser.ID);
            if(flag)
            {
                ui->regFail->setVisible(true);
                ui->regSuccess->setVisible(false);
            }
            else
            {
                ui->regFail->setVisible(false);
                ui->regSuccess->setVisible(true);
            }

        }
        else
        {
            Account_user newUser;
            newUser.ID = Accountdb.searchMaxID();
            qDebug (" id = %d", newUser.ID);
            newUser.Name = namestring;
            newUser.Password = passwordstring;
            newUser.Purse = 0;
            newUser.Type = 2;
            bool flag;

//            ofstream outf("personData.dat",ios_base::out | ios_base::binary);
//            outf << newUser.Name << newUser.Password


            flag=Accountdb.userInsertData(newUser);
            if(flag)
            {
                ui->regFail->setVisible(true);
                ui->regSuccess->setVisible(false);
            }
            else
            {
                ui->regFail->setVisible(false);
                ui->regSuccess->setVisible(true);
            }
        }
    }

}

Register::~Register()
{
    delete ui;
}
