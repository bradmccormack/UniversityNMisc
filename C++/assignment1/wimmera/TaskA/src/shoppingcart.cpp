#include "../include/shoppingcart.h"

#include <string>
#include <vector>

#include "../include/item.h"
#include "../include/book.h"
#include "../include/music.h"

//This class represents a consumers shopping cart at any point in time

//overloaded constructor for flexibility
shoppingcart::shoppingcart(double spendingLimit)
{
    m_items=new vector<Item*>();
    m_spending_limit=spendingLimit;
}

//return all the items in the shopping cart
vector<Item*>* shoppingcart::getItems()
{
    return m_items;
}

//return the spending limit
double shoppingcart::getSpendingLimit()
{
    return m_spending_limit;
}

//return the current amount spent
double shoppingcart::getSum()
{
    return m_sum;
}

void shoppingcart::setSum(double sum)
{
    m_sum=sum;
}

void shoppingcart::addItem(Item* Item)
{
    m_items->push_back(Item);
}

shoppingcart::~shoppingcart()
{
    //dellocate memory for all items in the vector
    for(unsigned int i=0; i<m_items->size(); i++)
        delete m_items->at(i);

    //deallocate memory for the vector of items
    delete m_items;
}
