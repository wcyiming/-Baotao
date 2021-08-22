#include "projectpreview.h"
#include "ui_projectpreview.h"

projectPreview::projectPreview(int projectID,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::projectPreview)
{
    ui->setupUi(this);

    ui->proName_lb->setStyleSheet("QLabel{color:white}");
    ui->noDiscountPrice_lb->setStyleSheet("QLabel{color:white}");
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
    nowProject = Projectdb.searchProjectInfo(projectID);

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
        ui->noDiscountPrice_lb->setVisible(false);
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

        ui->discountPricenew_lb->setVisible(true);
        ui->discountPriceold_lb->setVisible(true);
        ui->discoutPrecent_lb->setVisible(true);

    }
    else  //不打折另一种
    {
        ui->noDiscountPrice_lb->setVisible(true);
        ui->discount_fra->setVisible(false);
        double nowMoney = nowProject.prise*1.0 /100;
        QString Moneystring = "¥";
        Moneystring += QString::number(nowMoney, 'f', 2);
        ui->noDiscountPrice_lb->setText(Moneystring);

        ui->discountPricenew_lb->setVisible(false);
        ui->discountPriceold_lb->setVisible(false);
        ui->discoutPrecent_lb->setVisible(false);
    }


}

projectPreview::~projectPreview()
{
    delete ui;
}
