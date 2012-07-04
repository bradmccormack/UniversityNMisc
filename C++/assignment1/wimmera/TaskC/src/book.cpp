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

//overloaded constructor to init book type
Book::Book(string Title,string Author,bool hasEbook,int StockQty)
{
    this->m_title=Title;
    this->m_author=Author;
    this->m_hasEversion=hasEbook;
    this->m_Qty=StockQty;
    this->m_cost=30.00;
    this->e_cost=10.00;
}

string* Book::getAuthor()
{
    return &this->m_author;
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
