#ifndef BOOK_H
#define BOOK_H

#include "../include/item.h"

using namespace std;

class Book : public Item
{
public:
    //overloaded constructor to init the book items
    Book(string Title,string Author,bool hasEbook,int StockQty);
    //virtual destructor to prevent slicing
    virtual ~Book();
    string* getAuthor();
protected:
private:
    string m_author;
};

#endif // BOOK_H
