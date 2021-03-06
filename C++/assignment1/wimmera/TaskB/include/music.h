#ifndef MUSIC_H
#define MUSIC_H

#include "../include/item.h"


class Music : public Item
{
public:
    //overloaded constructor to handle initing music item
    Music(string Title,string Artist,bool hasEmusic,int StockQty);
    //virtual destructor to prevent slicing
    virtual ~Music();
    string* getArtist();
protected:
private:
    string m_artist;
};

#endif // MUSIC_H
