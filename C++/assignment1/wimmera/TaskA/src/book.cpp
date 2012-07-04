#include "../include/book.h"

using namespace std;

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


Book::~Book()
{
    //dtor
}
