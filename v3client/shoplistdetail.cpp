#include "shoplistdetail.h"
#include "ui_shoplistdetail.h"

shopListDetail::shopListDetail(QString nowName,int nowID,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::shopListDetail)
{
    ui->setupUi(this);
    ui->proName_lb->setStyleSheet("QLabel{color:white}");
    ui->Number_lb->setStyleSheet("QLabel{color:white}");
    ui->buytext_lb->setStyleSheet("QLabel{color:white}");
    ui->lastNumber_lb->setStyleSheet("QLabel{color:white}");
    ui->lastText_lb->setStyleSheet("QLabel{color:white}");
    ui->discountPricenew_lb->setStyleSheet("QLabel{color:white}");
    ui->discountPriceold_lb->setStyleSheet("QLabel{color:white;text-decoration:line-through}");
    ui->discoutPrecent_lb->setStyleSheet("QLabel{color:rgb(123,171,42)}");


    ui->discount_fra->setVisible(false);
    ui->discoutPrecent_lb->setVisible(false);
    ui->discountPricenew_lb->setVisible(false);
    ui->discountPriceold_lb->setVisible(false);

    sqilteOpreatorProjects Projectdb;
    Projectdb.openDb();
    Projects_books nowProject;
    nowProject = Projectdb.searchProjectInfo(nowID);
    sqliteShop shopCar;
    shopCar.openDb();

    ui->proName_lb->setText(nowProject.Name);

    if (nowProject.type == 1)
    {
        ui->proIcon->setStyleSheet("QFrame{image: url(:/new/prefix1/static/book.jpg);}");
    }
    else if(nowProject.type == 2)
    {
        ui->proIcon->setStyleSheet("QFrame{image: url(:/new/prefix1/static/clouth.jpg);}");
    }
    else
    {
        ui->proIcon->setStyleSheet("QFrame{image: url(:/new/prefix1/static/food.jpg);}");
    }

    if(nowProject.discount != 100)   //如果打折了，一种界面
    {
        ui->discount_fra->setVisible(true);
        double Floatdiscount = nowProject.discount*1.0 / 100;
        int Gfat = 100 - nowProject.discount;
        double newMoney = nowProject.prise * 1.0 * Floatdiscount / 100;
        QString newMoneystring = "¥ ";
        newMoneystring += QString::number(newMoney, 'f', 2);
        ui->discountPricenew_lb->setText(newMoneystring);

        double oldMoney = nowProject.prise*1.0 /100;
        QString oldMoneystring = "¥ ";
        oldMoneystring += QString::number(oldMoney, 'f', 2);
        ui->discountPriceold_lb->setText(oldMoneystring);

        QString nowDiscount = "-";
        nowDiscount += QString::number(Gfat);
        nowDiscount += "%";
        ui->discoutPrecent_lb->setText(nowDiscount);

        int need_number = shopCar.searchProjectNumber(nowName,nowID);
        QString nowNumberStr = QString::number(need_number);
        ui->Number_lb->setText(nowNumberStr);

        QString lastNumberPtr = QString::number(nowProject.number);
        ui->lastNumber_lb->setText(lastNumberPtr);

        ui->discountPricenew_lb->setVisible(true);
        ui->discountPriceold_lb->setVisible(true);
        ui->discoutPrecent_lb->setVisible(true);

    }
    else  //不打折另一种
    {
        ui->discountPriceold_lb->setStyleSheet("QLabel{color:white}");
        ui->discountPriceold_lb->setVisible(true);
        ui->discount_fra->setVisible(false);
        double nowMoney = nowProject.prise*1.0 /100;
        QString Moneystring = "¥";
        Moneystring += QString::number(nowMoney, 'f', 2);
        ui->discountPriceold_lb->setText(Moneystring);

        int need_number = shopCar.searchProjectNumber(nowName,nowID);
        QString nowNumberStr = QString::number(need_number);
        ui->Number_lb->setText(nowNumberStr);

        QString lastNumberPtr = QString::number(nowProject.number);
        ui->lastNumber_lb->setText(lastNumberPtr);

        ui->discountPricenew_lb->setVisible(false);
        ui->discoutPrecent_lb->setVisible(false);
    }
}

shopListDetail::~shopListDetail()
{
    delete ui;
}
