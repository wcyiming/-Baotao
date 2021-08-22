#include "management.h"
#include "ui_management.h"

management::management(QString userName,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::management)
{
    ui->setupUi(this);
    ui->discount_lb->setStyleSheet("QLabel{color:white}");
    ui->discount_lb2->setStyleSheet("QLabel{color:white}");
    ui->discount_line->setValidator(new QIntValidator(0,100,this));
    ui->discount_bt->setStyleSheet("QPushButton{color:white}");

    ui->upFail_lb->setStyleSheet("QLabel{color:red}");
    ui->upFail_lb->setVisible(false);
    ui->upSuccesslb->setStyleSheet("QLabel{color:green}");
    ui->upSuccesslb->setVisible(false);

    SqliteOperator Accountdb;
    Accountdb.openDb();
    Account_sailer nowSailer;
    nowSailer = Accountdb.searchSailerQuery(userName);
    nowFather = nowSailer.ID;


    noSearch();

    connect(ui->resetbt, &QPushButton::clicked, this, &management::noSearch);

    connect(ui->discount_bt, &QPushButton::clicked, this, &management::discount_push);
    connect(ui->discount_line, &QLineEdit::textChanged, this , &management::enableButton);

    void (management::*slotFun)(QListWidgetItem *) = &management::onListItemClicked;
    void (QListWidget:: *signal)(QListWidgetItem *) = &QListWidget::itemClicked;
    connect(ui->sonListWidget , signal , this , slotFun);
}

void management::noSearch()//无搜索条件或者刷新
{
    ui->sonListWidget->clear();
    sqilteOpreatorProjects Projectdb;
    Projectdb.openDb();
    if (nowFather == 0)
    {
        w_list = Projectdb.searchProjectAll();
        if(w_list[0] == -1)
        {
            return;
        }
        for(int i = 0; i < (int)w_list.size() ; i++)
        {
            QListWidgetItem *tmp = new QListWidgetItem();
            ui->sonListWidget->addItem(tmp);
            tmp->setSizeHint(QSize(650,160));
            projectPreview *w = new projectPreview(w_list[i],ui->sonListWidget);
            ui->sonListWidget->setItemWidget(tmp,w);
        }
    }
    else
    {
    w_list = Projectdb.searchProjectFather(nowFather);
    if(w_list[0] == -1)
    {
        return;
    }
    for(int i = 0; i < (int)w_list.size() ; i++)
    {
        QListWidgetItem *tmp = new QListWidgetItem();
        ui->sonListWidget->addItem(tmp);
        tmp->setSizeHint(QSize(650,160));
        projectPreview *w = new projectPreview(w_list[i],ui->sonListWidget);
        ui->sonListWidget->setItemWidget(tmp,w);
    }
    }
}

void management::discount_push()//打折
{

    sqilteOpreatorProjects Projectdb;
    Projectdb.openDb();

    QString nowDiscountString = ui->discount_line->text();
    int nowDiscount = nowDiscountString.toInt();
    if(nowDiscount > 100)
    {
        ui->upFail_lb->setVisible(true);
        ui->upSuccesslb->setVisible(false);
        return;
    }

    int nowType = 0;
    if(!ui->typeCombo->currentText().compare("图书"))
    {
        nowType = 1;
    }
    else if(!ui->typeCombo->currentText().compare("衣服"))
    {
        nowType = 2;
    }
    else if(!ui->typeCombo->currentText().compare("食品"))
    {
        nowType = 3;
    }
    if (nowFather == 0)
    {
        w_list = Projectdb.searchProjectAll();
        if(w_list[0] == -1)
        {
            return;
        }
        for(int i = 0; i < (int)w_list.size() ; i++)
        {
            Projects_books now = Projectdb.searchProjectInfo(w_list[i]);
            if (now.type == nowType || nowType == 0)
            {
                now.discount = nowDiscount;
                bool flag;
                flag = Projectdb.modifyprojectDiscount(now);
                if(flag)
                {
                    ui->upFail_lb->setVisible(true);
                    ui->upSuccesslb->setVisible(false);
                }
                else
                {
                    ui->upSuccesslb->setVisible(true);
                    ui->upFail_lb->setVisible(false);
                }
            }
        }
        noSearch();
    }
    else
    {
        w_list = Projectdb.searchProjectFather(nowFather);
        if(w_list[0] == -1)
        {
            return;
        }
        for(int i = 0; i < (int)w_list.size() ; i++)
        {
            Projects_books now = Projectdb.searchProjectInfo(w_list[i]);
            if (now.type == nowType || nowType == 0)
            {
                now.discount = nowDiscount;
                bool flag;
                flag = Projectdb.modifyprojectDiscount(now);
                if(flag)
                {
                    ui->upFail_lb->setVisible(true);
                    ui->upSuccesslb->setVisible(false);
                }
                else
                {
                    ui->upSuccesslb->setVisible(true);
                    ui->upFail_lb->setVisible(false);
                }
            }
        }
        noSearch();
    }
}

void management::onListItemClicked(QListWidgetItem *item)  //项目点击
{
    int curItem = 0;
    while(curItem < ui->sonListWidget->count())
    {
        if(ui->sonListWidget->item(curItem) == item)
        {
            break;
        }
        else
        {
            curItem++;
        }
    }
     qDebug() << "has chang123";
    emit backIDsignalManage( w_list [curItem]);
}

void management::enableButton()  //折扣使能按钮
{
    bool OK;
    OK = !ui->discount_line->text().isEmpty();
    ui->discount_bt->setEnabled(OK);
    if(OK)
    {
        ui->discount_bt->setCursor(QCursor(Qt::PointingHandCursor));
        ui->discount_bt->setStyleSheet("QPushButton{color:white ; background-color:rgb(85, 170, 0)}");
    }

    else {
        ui->discount_bt->setStyleSheet("QPushButton{color:#A9A9A9; background-color:rgb(40,40,40)}");
        ui->discount_bt->setCursor(QCursor(Qt::ArrowCursor));
    }
}

management::~management()
{
    delete ui;
}
