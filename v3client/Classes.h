#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <vector>
#include <QWidget>
using namespace std;


class Account{
    public:
    int getID();
    QString getName();
    QString getPassword();
    int getPurse();
    virtual int getUserType()=0;
    int ID; //用户id
    QString Name;//用户名字
    QString Password;//用户密码
    int Purse,Type;//用户钱包 用户类型
};

class Account_user : public Account
{
    public:
    virtual int getUserType()
    {
        return Type;
    }
};

class Account_sailer : public Account
{
    public:
    virtual int getUserType()
    {
        return Type;
    }

};

class Projectsclass{
    public:
    int getId();
    QString getName();
    QString getInfor();
    virtual int getPrise()
    {
        return prise;
    }
    int getType();
    int getNumber();
    double getDiscount();

    int id;   //商品id
    QString Name;//商品名
    QString infor;//详细信息
    int prise,type,number;//商品价格  商品类型 商品数量
    int discount;  //商品折扣
    int father; //商品的创建者
};

class Projects_books : public Projectsclass
{
    public:
    virtual int getPrise()
    {
        return prise;
    }

};

class Projects_clothes : public Projectsclass
{
    public:
    virtual int getPrise()
    {
        return prise;
    }
};

class Projects_foods : public Projectsclass
{
    public:
    virtual int getPrise()
    {
        return prise;
    }
};
#endif // CLASSES_H
