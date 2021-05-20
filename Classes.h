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
    int ID;
    QString Name;
    QString Password;
    int Purse,Type;
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

    int id;
    QString Name;
    QString infor;
    int prise,type,number;
    int discount;
    int father;
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
