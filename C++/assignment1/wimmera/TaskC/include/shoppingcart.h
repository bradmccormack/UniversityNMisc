#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <vector>
#include "../include/item.h"

using namespace std;

class shoppingcart
{
public:
    shoppingcart();
    //overloaded constructor to init spendingLimit
    shoppingcart(double spendingLimit);

    virtual ~shoppingcart();
    //returns all items in the shopping cart
    vector<Item*>* getItems();
    //getters and setters
    double getSum();
    double getSpendingLimit();
    void setSum(double sum);
    void addItem(Item* item);
protected:
private:
    vector<Item*>* m_items;
    double m_spending_limit;
    double m_sum;

};

#endif // SHOPPINGCART_H
