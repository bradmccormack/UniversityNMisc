#ifndef BOOK_H
#define BOOK_H

#include "../include/item.h"

using namespace std;

class Book : public Item
{
public:
    Book();
    //overloaded constructor to init the book items
    Book(string Title,string Author,bool hasEbook,int StockQty);
    //virtual destructor to prevent slicing
    virtual ~Book();
    string* getAuthor();

    //overloaded stream operators
    friend istream& operator >>(istream &is,Book &obj);
    friend ostream& operator <<(ostream &os,Book obj);

protected:
    virtual void displayItem(ostream &os);
    virtual void inputItem(istream &is);
private:
    string m_author;
};

#endif // BOOK_H
