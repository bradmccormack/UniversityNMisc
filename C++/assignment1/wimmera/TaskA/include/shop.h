#ifndef SHOP_H
#define SHOP_H

#include <vector>

#include "../include/item.h"
#include "../include/book.h"
#include "../include/music.h"

using namespace std;

//This class represents the shop.
class shop
{
public:
    shop();
    virtual ~shop();
    //gets all items in the shop
    vector<Item*>* getItems();
    //adds item to the shop
    void addItem(Item* item);
protected:
private:
    vector<Item*>* m_items;


};

#endif // SHOP_H
