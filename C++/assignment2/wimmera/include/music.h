#ifndef MUSIC_H
#define MUSIC_H

#include "../include/item.h"


class Music : public Item
{
public:
    Music();
    //overloaded constructor to handle initing music item
    Music(string Title,string Artist,bool hasEmusic,int StockQty);
    Music(string Title,string Artist,bool hasEmusic,int StockQty,double pPrice,double ePrice);
    //virtual destructor to prevent slicing
    virtual ~Music();
    string* getArtist();
    void setArtist(string* Artist);
    //overloaded stream operators
    friend istream& operator >>(istream &is,Music &obj);
    friend ostream& operator <<(ostream &os,Music obj);
protected:
    virtual void displayItem(ostream &os);
    virtual void inputItem(istream &is);
private:
    string m_artist;
};

#endif // MUSIC_H
