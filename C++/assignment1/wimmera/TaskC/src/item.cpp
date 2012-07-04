#include "../include/item.h"
#include "../include/utility1.h"
#include <iostream>


using namespace std;

void Item::displayItem(ostream &os)
{
    os << "Title :"+m_title<<endl;
    string version=m_hasEversion==true?"true":"false";
    os << "Has Eversion:"+version<<endl;
    version=m_isEversion==true?"true":"false";
    os << "Is Eversion:"+version<<endl;

    stringstream s;
    s<<m_cost;
    os << "Cost for Physical version:"+s.str()<<endl;
    s.str(std::string()); //clear stringstream
    s<<e_cost;
    os << "Cost for Electronic version:"+s.str()<<endl;

    s.str(std::string());
    s<<m_Qty;

    os << "Qty available:"+s.str()<<endl;
}

void Item::inputItem(istream &is)
{
    cout <<"Input title:";
    is>>m_title;
    string choice;
    do
    {
        cout <<"Does Item have eversion: (yes/no)";
        is >> choice;
        clearInputBuffer();
    }
    while(choice!="yes" && choice!="no");
    choice=="yes"?m_hasEversion=true:m_hasEversion=false;
    choice="";
    do
    {
        cout <<"Is the Item an eversion: (yes/no)";
        is >> choice;
        clearInputBuffer();
    }
    while(choice!="yes" && choice!="no");
    choice=="yes"?m_isEversion=true:m_isEversion=false;
    cout <<"Input Qty:";
    is>>m_Qty;
}




