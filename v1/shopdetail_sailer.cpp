#include "shopdetail_sailer.h"
#include "ui_shopdetail_sailer.h"

shopdetail_sailer::shopdetail_sailer(int projectID,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::shopdetail_sailer)
{
    ui->setupUi(this);
    ui->projectfather_lb->setStyleSheet("QLabel{color:white}");
    ui->projectname_lb->setStyleSheet("QLabel{color:white}");
    ui->nodiscount_lb->setStyleSheet("QLabel{color:white}");
    ui->discountnew_lb->setStyleSheet("QLabel{color:white}");
    ui->buy_lb->setStyleSheet("QLabel{color:white}");
    ui->projectname_lb2->setStyleSheet("QLabel{color:white}");
    ui->projectnumber_lb->setStyleSheet("QLabel{color:white}");
    ui->special_lb->setStyleSheet("QLabel{color:white}");
    ui->still_lb->setStyleSheet("QLabel{color:white}");
    ui->projectfather_lb_2->setStyleSheet("QLabel{color:white}");

    ui->discountold_lb->setStyleSheet("QLabel{color:white;text-decoration:line-through}");
    ui->discountprecent_lb->setStyleSheet("QLabel{color:rgb(123,171,42)}");
    ui->frame_4->setVisible(false);
    ui->discountprecent_lb->setVisible(false);
    ui->discountnew_lb->setVisible(false);
    ui->discountold_lb->setVisible(false);
    ui->special_lb->setVisible(false);

    sqilteOpreatorProjects Projectdb;
    Projectdb.openDb();
    Projects_books nowProject;
    nowProject = Projectdb.searchProjectInfo(projectID);

    ui->projectname_lb->setText(nowProject.Name);
    ui->projectname_lb2->setText(nowProject.Name);
    ui->projectinfor_text->setText(nowProject.infor);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowFather;
    nowFather = Accountdb.searchUserIDQuery(nowProject.father);
    ui->projectfather_lb->setText(nowFather.Name);

    QString numberstring = QString::number(nowProject.number);
    ui->projectnumber_lb->setText(numberstring);

    if (nowProject.type == 1)
    {
        ui->icon_Fra->setStyleSheet("QFrame{image: url(:/new/prefix1/static/book.jpg);}");
    }
    else if(nowProject.type == 2)
    {
        ui->icon_Fra->setStyleSheet("QFrame{image: url(:/new/prefix1/static/clouth.jpg);}");
    }
    else
    {
        ui->icon_Fra->setStyleSheet("QFrame{image: url(:/new/prefix1/static/food.jpg);}");
    }



    if(nowProject.discount != 100)
    {
        ui->nodiscount_lb->setVisible(false);
        double Floatdiscount = nowProject.discount*1.0 / 100;
        int Gfat = 100 - nowProject.discount;
        double newMoney = nowProject.prise * 1.0 * Floatdiscount / 100;
        QString newMoneystring = "¥ ";
        newMoneystring += QString::number(newMoney, 'f', 2);
        ui->discountnew_lb->setText(newMoneystring);

        double oldMoney = nowProject.prise*1.0 /100;
        QString oldMoneystring = "¥ ";
        oldMoneystring += QString::number(oldMoney, 'f', 2);
        ui->discountold_lb->setText(oldMoneystring);

        QString nowDiscount = "-";
        nowDiscount += QString::number(Gfat);
        nowDiscount += "%";
        ui->discountprecent_lb->setText(nowDiscount);

        ui->discountnew_lb->setVisible(true);
        ui->discountold_lb->setVisible(true);
        ui->discountprecent_lb->setVisible(true);
        ui->frame_4->setVisible(true);
        ui->special_lb->setVisible(true);

    }
    else
    {
        ui->nodiscount_lb->setVisible(true);
        double nowMoney = nowProject.prise*1.0 /100;
        QString Moneystring = "¥";
        Moneystring += QString::number(nowMoney, 'f', 2);
        ui->nodiscount_lb->setText(Moneystring);

        ui->discountnew_lb->setVisible(false);
        ui->discountold_lb->setVisible(false);
        ui->discountprecent_lb->setVisible(false);
        ui->frame_4->setVisible(false);
        ui->special_lb->setVisible(false);
    }
}

void shopdetail_sailer::changeView(int projectID)
{
    sqilteOpreatorProjects Projectdb;
    Projectdb.openDb();
    Projects_books nowProject;
    nowProject = Projectdb.searchProjectInfo(projectID);

    ui->projectname_lb->setText(nowProject.Name);
    ui->projectname_lb2->setText(nowProject.Name);
    ui->projectinfor_text->setText(nowProject.infor);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowFather;
    nowFather = Accountdb.searchUserIDQuery(nowProject.father);
    ui->projectfather_lb->setText(nowFather.Name);

    QString numberstring = QString::number(nowProject.number);
    ui->projectnumber_lb->setText(numberstring);

    if (nowProject.type == 1)
    {
        ui->icon_Fra->setStyleSheet("QFrame{image: url(:/new/prefix1/static/book.jpg);}");
    }
    else if(nowProject.type == 2)
    {
        ui->icon_Fra->setStyleSheet("QFrame{image: url(:/new/prefix1/static/clouth.jpg);}");
    }
    else
    {
        ui->icon_Fra->setStyleSheet("QFrame{image: url(:/new/prefix1/static/food.jpg);}");
    }



    if(nowProject.discount != 100)
    {
        ui->nodiscount_lb->setVisible(false);
        double Floatdiscount = nowProject.discount*1.0 / 100;
        int Gfat = 100 - nowProject.discount;
        double newMoney = nowProject.prise * 1.0 * Floatdiscount / 100;
        QString newMoneystring = "¥ ";
        newMoneystring += QString::number(newMoney, 'f', 2);
        ui->discountnew_lb->setText(newMoneystring);

        double oldMoney = nowProject.prise*1.0 /100;
        QString oldMoneystring = "¥ ";
        oldMoneystring += QString::number(oldMoney, 'f', 2);
        ui->discountold_lb->setText(oldMoneystring);

        QString nowDiscount = "-";
        nowDiscount += QString::number(Gfat);
        nowDiscount += "%";
        ui->discountprecent_lb->setText(nowDiscount);

        ui->discountnew_lb->setVisible(true);
        ui->discountold_lb->setVisible(true);
        ui->discountprecent_lb->setVisible(true);
        ui->frame_4->setVisible(true);
        ui->special_lb->setVisible(true);

    }
    else
    {
        ui->nodiscount_lb->setVisible(true);
        double nowMoney = nowProject.prise*1.0 /100;
        QString Moneystring = "¥";
        Moneystring += QString::number(nowMoney, 'f', 2);
        ui->nodiscount_lb->setText(Moneystring);

        ui->discountnew_lb->setVisible(false);
        ui->discountold_lb->setVisible(false);
        ui->discountprecent_lb->setVisible(false);
        ui->frame_4->setVisible(false);
        ui->special_lb->setVisible(false);
    }
}

shopdetail_sailer::~shopdetail_sailer()
{
    delete ui;
}
