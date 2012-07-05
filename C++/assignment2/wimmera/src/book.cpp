#include "../include/book.h"
#include <sstream>

using namespace std;

Book::Book()
{
    this->e_cost=10.00;
    this->m_cost=30.00;
    this->m_Qty=0;
    this->m_title="";
    this->m_author="";
}

//overloaded constructor so prices can be set
Book::Book(string Title,string Author,bool hasEbook,int StockQty,double pPrice,double ePrice)
{
    this->m_title=Title;
    this->m_author=Author;
    this->m_hasEversion=hasEbook;
    this->m_Qty=StockQty;
    this->m_cost=pPrice;
    this->e_cost=ePrice;
    this->m_QtySold=0;
    this->e_QtySold=0;
}


//overloaded constructor to init book type. Use default prices
Book::Book(string Title,string Author,bool hasEbook,int StockQty)
{
    Book(Title,Author,hasEbook,StockQty,30.00,10.00);
}

string* Book::getAuthor()
{
    return &this->m_author;
}

void Book::setAuthor(string* Author)
{
    this->m_author=*Author;
}

//will display all info about abook.
void Book::displayItem(ostream &os)
{
    //display the genral information
    Item::displayItem(os);
    //display specific info for a book here (Author)
    os << "Author:"<<m_author<<endl;
}

void Book::inputItem(istream &is)
{
    Item::inputItem(is);
    //input specific info for a book here (Author)
    cout << "Input Author:";
    is >> m_author;
}

//overloaded stream operators
istream& operator >>(istream &is,Book &obj)
{
    obj.inputItem(is);
    return is;
}
ostream& operator <<(ostream &os,Book obj)
{
    obj.displayItem(os);
    return os;
}

Book::~Book()
{
    //dtor
}
