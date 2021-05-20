#include "shopmall.h"
#include "ui_shopmall.h"

Shopmall::Shopmall(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Shopmall)
{
    ui->setupUi(this);
    ui->searchNone->setStyleSheet("QLabel{color:red}");
    ui->searchNone->setVisible(false);


    noSearch();

    connect(ui->searchbt, &QPushButton::clicked, this, &Shopmall::search_push);
    connect(ui->resetbt, &QPushButton::clicked, this, &Shopmall::noSearch);

    void (Shopmall::*slotFun)(QListWidgetItem *) = &Shopmall::onListItemClicked;
    void (QListWidget:: *signal)(QListWidgetItem *) = &QListWidget::itemClicked;
    connect(ui->splistWidget , signal , this , slotFun);
}

void Shopmall::noSearch()
{
    ui->splistWidget->clear();
    sqilteOpreatorProjects Projectdb;
    Projectdb.openDb();
    w_list = Projectdb.searchProjectAll();
    if (w_list[0] == -1)
    {
        return;
        qDebug() << "1" ;
    }
    for(int i = 0; i < (int)w_list.size() ; i++)
    {
        QListWidgetItem *tmp = new QListWidgetItem();
        ui->splistWidget ->addItem(tmp);
        tmp->setSizeHint(QSize(650,160));
        projectPreview *w = new projectPreview(w_list[i],ui->splistWidget);
        ui->splistWidget->setItemWidget(tmp,w);
    }
}

void Shopmall::search_push()
{
    ui->splistWidget->clear();
    sqilteOpreatorProjects Projectdb;
    Projectdb.openDb();

    QString nowSearch = ui->searchedit->text();

    w_list = Projectdb.searchProjectName(nowSearch);

    if(w_list[0] == -1)
    {
        ui->searchNone->setVisible(true);
        return;
    }
    for(int i = 0; i < (int)w_list.size() ; i++)
    {
        QListWidgetItem *tmp = new QListWidgetItem();
        ui->splistWidget ->addItem(tmp);
        tmp->setSizeHint(QSize(650,160));
        projectPreview *w = new projectPreview(w_list[i],ui->splistWidget);
        ui->splistWidget->setItemWidget(tmp,w);
    }
}

void Shopmall::onListItemClicked(QListWidgetItem *item)
{
    int curItem = 0;
    while(curItem < ui->splistWidget->count())
    {
        if(ui->splistWidget->item(curItem) == item)
        {
            break;
        }
        else
        {
            curItem++;
        }
    }

    qDebug("%d",w_list[curItem]);
    emit backIDsignal(w_list[curItem]);
}

Shopmall::~Shopmall()
{
    delete ui;
}
