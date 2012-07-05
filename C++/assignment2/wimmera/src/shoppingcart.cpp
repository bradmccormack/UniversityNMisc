#include "../include/shoppingcart.h"

#include <string>
#include <vector>

#include "../include/item.h"
#include "../include/book.h"
#include "../include/music.h"

//This class represents a consumers shopping cart at any point in time

//overloaded constructor for flexibility
Shoppingcart::Shoppingcart()
{
    m_items=new vector<Item*>();
    m_sum=0;
}

//return all the items in the shopping cart
vector<Item*>* Shoppingcart::getItems()
{
    return m_items;
}

//return the spending limit
double Shoppingcart::getSpendingLimit()
{
    return m_spending_limit;
}

//return the current amount spent
double Shoppingcart::getSum()
{
    return m_sum;
}

void Shoppingcart::setSum(double sum)
{
    m_sum=sum;
}

void Shoppingcart::setSpendingLimit(double limit)
{
    m_spending_limit=limit;
}

double Shoppingcart::getSumHistory()
{
    return m_sumhistory;
}

void Shoppingcart::setSumHistory(double sum)
{
    m_sumhistory=sum;
}

void Shoppingcart::addItem(Item* Item)
{
    m_items->push_back(Item);
}

Shoppingcart::~Shoppingcart()
{
    //dellocate memory for all items in the vector
    for(unsigned int i=0; i<m_items->size(); i++)
        delete m_items->at(i);

}
