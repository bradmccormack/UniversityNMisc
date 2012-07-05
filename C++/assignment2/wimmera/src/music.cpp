#include "../include/music.h"

Music::Music()
{
    this->e_cost=10.00;
    this->m_cost=20.00;
    this->m_Qty=0;
    this->m_title="";
    this->m_artist="";
}

//overloaded constructor so prices can be set
Music::Music(string Title,string Artist,bool hasEmusic,int StockQty,double pPrice,double ePrice)
{
    this->m_title=Title;
    this->m_artist=Artist;
    this->m_hasEversion=hasEmusic;
    this->m_Qty=StockQty;
    this->m_cost=pPrice;
    this->e_cost=ePrice;
    this->m_QtySold=0;
    this->e_QtySold=0;
}


//overloaded constructor to handle music type
Music::Music(string Title,string Artist,bool hasEmusic,int StockQty)
{
    Music(Title,Artist,hasEmusic,StockQty,20.00,10.00);

}
string* Music:: getArtist()
{
    return &m_artist;
}

void Music::setArtist(string* Artist)
{
    this->m_artist=*Artist;
}

//will display all info about abook.
void Music::displayItem(ostream &os)
{
    //display the genral information
    Item::displayItem(os);
    //display specific info for music here (Artist)
    os << "Artist:"<<m_artist<<endl;
}

void Music::inputItem(istream &is)
{
    Item::inputItem(is);
    //input specific info for music here (Artist)
    cout << "Input Artist:";
    is >> m_artist;
}


//overloaded stream operators
istream& operator >>(istream &is,Music &obj)
{
    obj.inputItem(is);
    return is;
}
ostream& operator <<(ostream &os,Music obj)
{
    obj.displayItem(os);
    return os;
}


Music::~Music()
{
    //dtor
}
