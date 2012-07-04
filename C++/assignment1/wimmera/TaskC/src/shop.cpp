#include "../include/shop.h"

//This class represents a shop that sells items
shop::shop()
{
    m_items=new vector<Item*>();
}

vector<Item*>* shop::getItems()
{
    return m_items;
}

void shop::addItem(Item* Item)
{
    m_items->push_back(Item);
}

shop::~shop()
{
    //dellocate memory for all items in the vector
    for(unsigned int i=0; i<m_items->size(); i++)
        delete m_items->at(i);

    //dellocate memory for the vector of items
    delete m_items;

}
