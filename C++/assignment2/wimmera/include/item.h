//
// item.h
//
// Parent Item class
//

#ifndef __ITEM_H__
#define __ITEM_H__
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>


using namespace std;


//look into pure virtual or private constructor to prevent instantiation

class Item
{
public:
    //getters
    virtual double getCost()
    {
        if(m_isEversion)
            return e_cost;
        else
            return m_cost;
    }

    virtual double getECost()
    {
        return e_cost;
    }

    virtual double getPCost()
    {
        return m_cost;
    }

    virtual string* getTitle()
    {
        return &m_title;
    };
    virtual int getQty()
    {
        return m_Qty;
    }
    virtual bool getHasEversion()
    {
        return m_hasEversion;
    }
    virtual bool getIsEversion()
    {
        return m_isEversion;
    }

    virtual int getQtySold()
    {
        return m_QtySold;
    }

    virtual int getEQtySold()
    {
        return e_QtySold;
    }

    //setters
    //will explicitly set the physical cost
    virtual void setPhysicalCost(double cost)
    {
        m_cost=cost;
    }

    virtual void setECost(double cost)
    {
        e_cost=cost;
    }

    virtual void setQty(int Qty)
    {
        m_Qty=Qty;
    }
    virtual void setIsEversion(bool isEversion)
    {
        m_isEversion=isEversion;
    }

    virtual void setHasEversion(bool hasEversion)
    {
        m_hasEversion=hasEversion;
    }

    virtual void setTitle(string* Title)
    {
        m_title=*Title;
    }


    virtual void setQtySold(int Qty)
    {
        m_QtySold=Qty;
    }

    virtual void setEQtySold(int Qty)
    {
        e_QtySold=Qty;
    }

    //overloaded stream operators to be defined in book and music
    friend istream& operator >>(istream &is,Item &obj);
    friend ostream& operator <<(ostream &os,Item obj);

protected:
    //The overloaded operators in derrived classes will call the following two functions
    virtual void displayItem(ostream &os);
    virtual void inputItem(istream &is);

    bool m_hasEversion; //indicates whether there is an e version available of this item
    bool m_isEversion; //indicates whether this is an eversion
    double m_cost;
    double e_cost;
    string m_title;
    int m_Qty;
    int m_QtySold;
    int e_QtySold;
    map<string,vector<string> > recommendations;
private:

};

#endif
