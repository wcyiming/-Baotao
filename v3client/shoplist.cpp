#include "shoplist.h"
#include "ui_shoplist.h"

shopList::shopList(QString userName,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::shopList)
{
    ui->setupUi(this);
    ui->fail_lb->setStyleSheet("QLabel{color:red}");
    ui->fail_lb->setVisible(false);
    ui->money_lb->setStyleSheet("QLabel{color:white}");
    ui->money_tot->setStyleSheet("QLabel{color:white}");
    ui->check->setStyleSheet("QPushButton{color:white ; background-color:rgb(85, 170, 0)}");

    nowName = userName;


    noSearch();

    connect(ui->check, &QPushButton::clicked, this, &shopList::buy_push);

    void (shopList::*slotFun)(QListWidgetItem *) = &shopList::onListItemClicked;
    void (QListWidget:: *signal)(QListWidgetItem *) = &QListWidget::itemClicked;
    connect(ui->buylistWidget , signal , this , slotFun);


}

void shopList::noSearch()  //没有搜索的情况
{
    ui->fail_lb->setVisible(false);
    ui->buylistWidget->clear();
    sqilteOpreatorProjects Projectdb;
    Projectdb.openDb();
    sqliteShop shopCar;
    shopCar.openDb();
    double priceAll = 0.0;
    w_list = shopCar.searchShopName(nowName);
    if (w_list[0] == -1)
    {

        QString Moneystring = QString::number(priceAll, 'f', 2);
        ui->money_tot->setText(Moneystring);
        return;
        qDebug() << "1" ;
    }
    for(int i = 0; i < (int)w_list.size() ; i++)
    {
        QListWidgetItem *tmp = new QListWidgetItem();
        ui->buylistWidget ->addItem(tmp);
        tmp->setSizeHint(QSize(710,140));
        shopListDetail *w = new shopListDetail(nowName,w_list[i],ui->buylistWidget);
        ui->buylistWidget->setItemWidget(tmp,w);


        Projects_books nowProject = Projectdb.searchProjectInfo(w_list[i]);
        int need_number = shopCar.searchProjectNumber(nowName,w_list[i]);
        double Floatdiscount = nowProject.discount*1.0 / 100;
        double newMoney = (nowProject.prise * need_number) * 1.0 * Floatdiscount / 100;
        priceAll += newMoney;
    }

    QString Moneystring = QString::number(priceAll, 'f', 2);
    ui->money_tot->setText(Moneystring);

}

void shopList::buy_push() //按下提交后的槽
{
    ui->fail_lb->setVisible(false);
    sqilteOpreatorProjects Projectdb;
    Projectdb.openDb();
    sqliteShop shopCar;
    shopCar.openDb();

    int flag = 0;

    if(w_list[0] == -1)
    {
        return;
    }
    for(int i = 0; i < (int)w_list.size() ; i++)
    {
        Projects_books nowProject = Projectdb.searchProjectInfo(w_list[i]);
        int need_number = shopCar.searchProjectNumber(nowName,w_list[i]);
        if(need_number > nowProject.number)
        {
            flag =1;
            break;
        }
    }
    if(flag)
    {
        ui->fail_lb->setVisible(true);
        noSearch();
        return;
    }
    for(int i = 0; i < (int)w_list.size() ; i++)
    {
        Projects_books nowProject = Projectdb.searchProjectInfo(w_list[i]);
        int need_number = shopCar.searchProjectNumber(nowName,w_list[i]);
        nowProject.number -= need_number;
        Projectdb.modifyprojectNumber(nowProject.id,nowProject.number);
    }

     emit backSendSignal();
}

void shopList::onListItemClicked(QListWidgetItem *item)  //点击项目
{
    int curItem = 0;
    while(curItem < ui->buylistWidget->count())
    {
        if(ui->buylistWidget->item(curItem) == item)
        {
            break;
        }
        else
        {
            curItem++;
        }
    }

    qDebug("%d",w_list[curItem]);


    shopCarNumber *carChange = new shopCarNumber(nowName,w_list[curItem]);
    carChange->show();
    connect(carChange , &shopCarNumber::backRefreshSignal , this , &shopList::noSearch);
}

shopList::~shopList()
{
    delete ui;
}
