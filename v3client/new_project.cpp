#include "new_project.h"
#include "ui_new_project.h"

new_project::new_project(QString userName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::new_project)
{
    ui->setupUi(this);
    ui->proinfor_lb->setStyleSheet("QLabel{color:white}");
    ui->pronumber_lb->setStyleSheet("QLabel{color:white}");
    ui->proname_lb->setStyleSheet("QLabel{color:white}");
    ui->protype_lb->setStyleSheet("QLabel{color:white}");
    ui->proprice_lb->setStyleSheet("QLabel{color:white}");
    ui->signup->setStyleSheet("QPushButton{color:#A9A9A9}");

    ui->proprice_line->setValidator(new QDoubleValidator(0,99999,2,this));
    ui->pronumber_line->setValidator(new QIntValidator(0,99999,this));

    ui->upFail->setStyleSheet("QLabel{color:red}");
    ui->upFail->setVisible(false);
    ui->upSuccess->setStyleSheet("QLabel{color:green}");
    ui->upSuccess->setVisible(false);
    nowName = userName;

    connect(ui->proname_line, &QLineEdit::textChanged, this , &new_project::enableButton);
    connect(ui->pronumber_line, &QLineEdit::textChanged, this , &new_project::enableButton);
    connect(ui->proprice_line, &QLineEdit::textChanged, this , &new_project::enableButton);

    connect(ui->signup,&QPushButton::clicked, this , &new_project::up_push);
}
void new_project::enableButton()   //提交使能按钮
{
    bool useOK,passOK,passOK2;
    useOK = !ui->proname_line->text().isEmpty();
    passOK = !ui->pronumber_line->text().isEmpty();
    passOK2 = !ui->proprice_line->text().isEmpty();
    ui->signup->setEnabled(useOK && passOK && passOK2);
    if( useOK && passOK && passOK2)
    {
        ui->signup->setCursor(QCursor(Qt::PointingHandCursor));
        ui->signup->setStyleSheet("QPushButton{color:white ; background-color:rgb(85, 170, 0)}");
    }

    else {
        ui->signup->setStyleSheet("QPushButton{color:#A9A9A9; background-color:rgb(40,40,40)}");
        ui->signup->setCursor(QCursor(Qt::ArrowCursor));
    }
}

void new_project::up_push()  //提交
{
    ui->upFail->setVisible(false);
    ui->upSuccess->setVisible(false);
    QString projectName = ui->proname_line->text();
    QString projectInfor = ui->proinfor_text->toPlainText();

    QString priceString = ui->proprice_line->text();
    int projectPrice = priceString.toDouble()*100;

    QString numberString = ui->pronumber_line->text();
    int projectNumber = numberString.toInt();
    int projectType;

    if(!ui->protype_line->currentText().compare("图书"))
    {
        projectType = 1;
    }
    else if(!ui->protype_line->currentText().compare("衣服"))
    {
        projectType = 2;
    }
    else
    {
        projectType = 3;
    }
    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_sailer nowUser;
    nowUser = Accountdb.searchSailerQuery(nowName);

    sqilteOpreatorProjects Projectdb;
    Projectdb.openDb();
    Projects_books nowProject;

    nowProject.id = Projectdb.searchMaxID();
    qDebug("%d" ,nowProject.id);
    nowProject.Name = projectName;
    nowProject.infor = projectInfor;
    nowProject.prise = projectPrice;
    nowProject.number = projectNumber;
    nowProject.type = projectType;
    nowProject.discount = 100;
    nowProject.father = nowUser.ID;
    bool flag;
    flag = Projectdb.projectInsertData(nowProject);
    if(flag)
    {
        ui->upFail->setVisible(true);
        ui->upSuccess->setVisible(false);

    }
    else
    {
        ui->upSuccess->setVisible(true);
        ui->upFail->setVisible(false);
    }




}

new_project::~new_project()
{
    delete ui;
}
