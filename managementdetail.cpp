#include "managementdetail.h"
#include "ui_managementdetail.h"

managementDetail::managementDetail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::managementDetail)
{
    ui->setupUi(this);
    ui->proinfor_lb->setStyleSheet("QLabel{color:white}");
    ui->pronumber_lb->setStyleSheet("QLabel{color:white}");
    ui->proname_lb->setStyleSheet("QLabel{color:white}");
    ui->proprice_lb->setStyleSheet("QLabel{color:white}");
    ui->prodiscount_lb->setStyleSheet("QLabel{color:white}");
    ui->prodiscount_lb2->setStyleSheet("QLabel{color:white}");
    ui->signup->setStyleSheet("QPushButton{color:#A9A9A9}");

    ui->proprice_line->setValidator(new QDoubleValidator(0,99999,2,this));
    ui->pronumber_line->setValidator(new QIntValidator(0,99999,this));
    ui->prodiscount_line->setValidator(new QIntValidator(0,100,this));

    ui->upFail->setStyleSheet("QLabel{color:red}");
    ui->upFail->setVisible(false);
    ui->upSuccess->setStyleSheet("QLabel{color:green}");
    ui->upSuccess->setVisible(false);

    connect(ui->proname_line, &QLineEdit::textChanged, this , &managementDetail::enableButton);
    connect(ui->pronumber_line, &QLineEdit::textChanged, this , &managementDetail::enableButton);
    connect(ui->proprice_line, &QLineEdit::textChanged, this , &managementDetail::enableButton);

    connect(ui->signup,&QPushButton::clicked, this , &managementDetail::up_push);

    nowID = 1;

    sqilteOpreatorProjects Projectdb;
    Projectdb.openDb();
    Projects_books nowProject;
    nowProject = Projectdb.searchProjectInfo(1);
    ui->proname_line->setText(nowProject.Name);
    ui->proinfor_text->setText(nowProject.infor);

    double nowPrice = nowProject.prise*1.0 /100;
    QString Pricestring = QString::number(nowPrice, 'f', 2);
    ui->proprice_line->setText(Pricestring);

    double nowNumber = nowProject.number*1.0 /100;
    QString numberstring = QString::number(nowNumber, 'f', 2);
    ui->pronumber_line->setText(numberstring);

    int nowDicount = nowProject.discount;
    QString Moneystring = QString::number(nowDicount);
    ui->prodiscount_line->setText(Moneystring);

}
void managementDetail::enableButton()
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

void managementDetail::up_push()
{
    ui->upFail->setVisible(false);
    ui->upSuccess->setVisible(false);
    QString projectName = ui->proname_line->text();
    QString projectInfor = ui->proinfor_text->toPlainText();

    QString priceString = ui->proprice_line->text();
    int projectPrice = priceString.toDouble()*100;

    QString numberString = ui->pronumber_line->text();
    int projectNumber = numberString.toInt();

    QString discountString = ui->prodiscount_line->text();
    int projectDiscount = discountString.toInt();

    if(projectDiscount > 100)
    {
        ui->upFail->setVisible(true);
        ui->upSuccess->setVisible(false);
        return;
    }

    int projectType = 0;

    sqilteOpreatorProjects Projectdb;
    Projectdb.openDb();
    Projects_books nowProject;

    nowProject.id =nowID;
    nowProject.Name = projectName;
    nowProject.infor = projectInfor;
    nowProject.prise = projectPrice;
    nowProject.number = projectNumber;
    nowProject.type = projectType;
    nowProject.discount = projectDiscount;
    nowProject.father = 1;
    bool flag;
    flag = Projectdb.modifyprojectData(nowProject);
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

void managementDetail::list_push(int passID)
{
    nowID = passID;

    sqilteOpreatorProjects Projectdb;
    Projectdb.openDb();
    Projects_books nowProject;
    nowProject = Projectdb.searchProjectInfo(nowID);
    ui->proname_line->setText(nowProject.Name);
    ui->proinfor_text->setText(nowProject.infor);

    double nowPrice = nowProject.prise*1.0 /100;
    QString Pricestring = QString::number(nowPrice, 'f', 2);
    ui->proprice_line->setText(Pricestring);

    int nowNumber = nowProject.number;
    QString numberstring = QString::number(nowNumber);
    ui->pronumber_line->setText(numberstring);

    int nowDicount = nowProject.discount;
    QString Moneystring = QString::number(nowDicount);
    ui->prodiscount_line->setText(Moneystring);

}

managementDetail::~managementDetail()
{
    delete ui;
}
