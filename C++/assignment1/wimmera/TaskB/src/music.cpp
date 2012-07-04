#include "../include/music.h"

//overloaded constructor to handle music type
Music::Music(string Title,string Artist,bool hasEmusic,int StockQty)
{
    this->m_title=Title;
    this->m_artist=Artist;
    this->m_cost=20.00;
    this->e_cost=10.00;
    this->m_hasEversion=hasEmusic;
    this->m_Qty=StockQty;

}
string* Music:: getArtist()
{
    return &m_artist;
}

Music::~Music()
{
    //dtor
}
