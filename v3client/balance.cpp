#include "balance.h"
#include "ui_balance.h"

balance::balance(QString userName,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::balance)
{
    ui->setupUi(this);
    ui->fail_lb->setStyleSheet("QLabel{color:red}");
    ui->fail_lb->setVisible(false);

    ui->moneyAll_lb->setStyleSheet("QLabel{color:white}");
    ui->moneytext_lb->setStyleSheet("QLabel{color:white}");
    ui->delete_bt->setStyleSheet("QPushButton{color:white ; background-color:rgb(85, 170, 0)}");
    ui->up_bt->setStyleSheet("QPushButton{color:white ; background-color:rgb(85, 170, 0)}");

    nowName = userName;
    noSearch();
    connect(ui->up_bt, &QPushButton::clicked, this, &balance::buy_push);
    connect(ui->delete_bt, &QPushButton::clicked, this, &balance::delete_push);

}

void balance::noSearch()
{
    ui->fail_lb->setVisible(false);
    ui->INIlistWidget->clear();
    sqilteOpreatorProjects Projectdb;
    Projectdb.openDb();
    sqliteShop shopCar;
    shopCar.openDb();
    double priceAll = 0.0;
    w_list = shopCar.searchShopName(nowName);
    if (w_list[0] == -1)
    {
        return;
        qDebug() << "1222" ;
    }
    for(int i = 0; i < (int)w_list.size() ; i++)
    {
        QListWidgetItem *tmp = new QListWidgetItem();
        ui->INIlistWidget ->addItem(tmp);
        tmp->setSizeHint(QSize(710,140));
        shopListDetail *w = new shopListDetail(nowName,w_list[i],ui->INIlistWidget);
        ui->INIlistWidget->setItemWidget(tmp,w);


        Projects_books nowProject = Projectdb.searchProjectInfo(w_list[i]);
        int need_number = shopCar.searchProjectNumber(nowName,w_list[i]);
        double Floatdiscount = nowProject.discount*1.0 / 100;
        double newMoney = (nowProject.prise * need_number) * 1.0 * Floatdiscount / 100;
        priceAll += newMoney;
    }

    QString Moneystring = QString::number(priceAll, 'f', 2);
    ui->moneyAll_lb->setText(Moneystring);

}

void balance::buy_push() //按下提交后的槽
{
    ui->fail_lb->setVisible(false);
    sqilteOpreatorProjects Projectdb;
    Projectdb.openDb();
    sqliteShop shopCar;
    shopCar.openDb();
    w_list = shopCar.searchShopName(nowName);

    double priceAll = 0.0;


    for(int i = 0; i < (int)w_list.size() ; i++)
    {
        Projects_books nowProject = Projectdb.searchProjectInfo(w_list[i]);
        int need_number = shopCar.searchProjectNumber(nowName,w_list[i]);
        double Floatdiscount = nowProject.discount*1.0 / 100;
        double newMoney = (nowProject.prise * need_number) * 1.0 * Floatdiscount / 100;
        priceAll += newMoney;
        qDebug()<<QString("priceAll :%1  newMoney : %2").arg(priceAll).arg(newMoney);
    }
    int checkprice = priceAll * 100;
    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_user nowUser;
    nowUser = Accountdb.searchUserQuery(nowName);
    if(nowUser.Purse < checkprice)
    {
        ui->fail_lb->setVisible(true);
        return;
    }

    nowUser.Purse -= checkprice;
    Accountdb.modifyUserData(nowUser);


    int sailerMoney;

    for(int i = 0; i < (int)w_list.size() ; i++)
    {
        Projects_books nowProject = Projectdb.searchProjectInfo(w_list[i]);
        int need_number = shopCar.searchProjectNumber(nowName,w_list[i]);
        double Floatdiscount = nowProject.discount*1.0 / 100;
        double newMoney = (nowProject.prise * need_number) * 1.0 * Floatdiscount / 100;
        sailerMoney = newMoney * 100;
         qDebug()<<QString("sailerMoney :%1  newMoney : %2").arg(sailerMoney).arg(newMoney);
        Account_user nowFather = Accountdb.searchUserIDQuery(nowProject.father);
        nowFather.Purse += sailerMoney;
        Accountdb.modifyUserData(nowFather);
    }

     shopCar.deleteClient(nowName);
     emit backBuySignal();
}

void balance::delete_push() //按下删除后的槽
{
    ui->fail_lb->setVisible(false);
    sqilteOpreatorProjects Projectdb;
    Projectdb.openDb();
    sqliteShop shopCar;
    shopCar.openDb();
    w_list = shopCar.searchShopName(nowName);

    for(int i = 0; i < (int)w_list.size() ; i++)
    {
        Projects_books nowProject = Projectdb.searchProjectInfo(w_list[i]);
        int need_number = shopCar.searchProjectNumber(nowName,w_list[i]);
        nowProject.number += need_number;
        Projectdb.modifyprojectNumber(nowProject.id,nowProject.number);
    }

     emit backRefreshSignal();
}



balance::~balance()
{
    delete ui;
}
