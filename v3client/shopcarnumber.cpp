#include "shopcarnumber.h"
#include "ui_shopcarnumber.h"

shopCarNumber::shopCarNumber(QString roamName,int roamID,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::shopCarNumber)
{
    ui->setupUi(this);

    ui->failed_lb->setStyleSheet("QLabel{color:red}");
    ui->failed_lb->setVisible(false);
    ui->need_line->setValidator(new QIntValidator(0,99999,this));


    connect(ui->add_bt,&QPushButton::clicked, this , &shopCarNumber::addPush);
    connect(ui->minus_bt,&QPushButton::clicked, this , &shopCarNumber::minusPush);
    connect(ui->delete_bt,&QPushButton::clicked, this , &shopCarNumber::deletePush);
    connect(ui->update_bt,&QPushButton::clicked, this , &shopCarNumber::updatePush);

    nowID = roamID;
    nowName = roamName;


    sqilteOpreatorProjects Projectdb;
    Projectdb.openDb();
    Projects_books nowProject;
    nowProject = Projectdb.searchProjectInfo(nowID);
    sqliteShop shopCar;
    shopCar.openDb();
    int need_number = shopCar.searchProjectNumber(nowName , nowID);
    QString lastNumberStr = QString::number(nowProject.number);
    QString needNumberStr = QString::number(need_number);

    ui->need_line->setText(needNumberStr);
    ui->sailNumber->setText(lastNumberStr);

}

void shopCarNumber::addPush()
{
    ui->failed_lb->setVisible(false);
    sqilteOpreatorProjects Projectdb;
    Projectdb.openDb();
    Projects_books nowProject;
    nowProject = Projectdb.searchProjectInfo(nowID);
    sqliteShop shopCar;
    shopCar.openDb();
    int need_number =  shopCar.searchProjectNumber(nowName , nowID);
    need_number ++;
    if(need_number > nowProject.number)
    {
        need_number = nowProject.number;
    }
    if(need_number <= 0)
    {
        need_number = 1;
    }
    shopCar.modifyprojectData(nowName , nowID , need_number);

    QString lastNumberStr = QString::number(nowProject.number);
    QString needNumberStr = QString::number(need_number);

    ui->need_line->setText(needNumberStr);
    ui->sailNumber->setText(lastNumberStr);

}

void shopCarNumber::minusPush()
{
    ui->failed_lb->setVisible(false);
    sqilteOpreatorProjects Projectdb;
    Projectdb.openDb();
    Projects_books nowProject;
    nowProject = Projectdb.searchProjectInfo(nowID);
    sqliteShop shopCar;
    shopCar.openDb();
    int need_number =  shopCar.searchProjectNumber(nowName , nowID);
    need_number --;
    if(need_number <= 0)
    {
        need_number = 1;
    }
    if(need_number > nowProject.number)
    {
        need_number = nowProject.number;
    }
    shopCar.modifyprojectData(nowName , nowID , need_number);

    QString lastNumberStr = QString::number(nowProject.number);
    QString needNumberStr = QString::number(need_number);

    ui->need_line->setText(needNumberStr);
    ui->sailNumber->setText(lastNumberStr);

}

void shopCarNumber::deletePush()
{
    sqilteOpreatorProjects Projectdb;
    Projectdb.openDb();
    Projects_books nowProject;
    nowProject = Projectdb.searchProjectInfo(nowID);
    sqliteShop shopCar;
    shopCar.openDb();
    bool flag;
    flag = shopCar.deleteData(nowName ,nowID);
    if(flag)
    {
         ui->failed_lb->setVisible(true);
         return;
    }
    else
    {
        emit backRefreshSignal();
        this->close();
    }

}

void shopCarNumber::updatePush()
{
    sqilteOpreatorProjects Projectdb;
    Projectdb.openDb();
    Projects_books nowProject;
    nowProject = Projectdb.searchProjectInfo(nowID);
    sqliteShop shopCar;
    shopCar.openDb();
    QString needNumberStr = ui->need_line->text();
    int needNubmer = needNumberStr.toInt();
    if(needNubmer <= 0 || needNubmer >= 99999)
    {
        ui->failed_lb->setVisible(true);
        return;
    }

    bool flag;
    flag = shopCar.modifyprojectData(nowName ,nowID,needNubmer);
    if(flag)
    {
         ui->failed_lb->setVisible(true);
    }
    else
    {
        emit backRefreshSignal();
        this->close();
    }

}

shopCarNumber::~shopCarNumber()
{
    delete ui;
}
