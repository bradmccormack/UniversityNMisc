#include "../include/music.h"

Music::Music()
{
   this->e_cost=10.00;
   this->m_cost=20.00;
   this->m_Qty=0;
   this->m_title="";
   this->m_artist="";
}

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
