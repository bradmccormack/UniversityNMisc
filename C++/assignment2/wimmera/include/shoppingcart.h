#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <vector>
#include "../include/item.h"

using namespace std;

class Shoppingcart
{
public:
    Shoppingcart();

    virtual ~Shoppingcart();
    //returns all items in the shopping cart
    vector<Item*>* getItems();
    //getters and setters
    double getSum();
    double getSpendingLimit();
    void setSum(double sum);
    void setSpendingLimit(double limit);
    double getSumHistory();
    void setSumHistory(double sum);
    void addItem(Item* item);
protected:
private:
    vector<Item*>* m_items;
    double m_spending_limit;
    double m_sum;
    double m_sumhistory; //total over mutliple checkouts

};

#endif // SHOPPINGCART_H
