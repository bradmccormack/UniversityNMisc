#ifndef MODEL_H
#define MODEL_H

#include "../include/shop.h"
#include "../include/shoppingcart.h"

//This class represents the interactions that happen with the data
//The model class will co-ordinate data requests to/from the shop and shopping cart
class Model
{
public:
    Model();
    virtual ~Model();

    //shopping Cart
    string addToCart(Item* Item); //will attempt to add to the cart
    void removeFromCart(Item* Item); //will remove item from cart
    vector<Item*>* getShoppingCartItems(); //get all items in the cart
    //will attempt to find matching item in shopitems and update qty to match item arg if it finds it
    void tryUpdateShopItem(Item* item);
    //shop
    vector<Item*>* getShopItems(); //gets all shop items
    vector<Item*>* getShopItems(string* containsTitle); //gets all shopitems that match the filter
    double getTotalCost();
protected:
private:
    //ptrs to shop and shoppingcart objects
    shop* m_shop;
    shoppingcart* m_shoppingcart;
    //will return the complete list
    vector<Item*>* getItems(vector<Item*>* list);
    //overload used for searching list that contains items equivalent to comparisonItem
    vector<Item*>* getItems(vector<Item*>* list,Item* comparisonItem);
    //used for starts with
    vector<Item*>* getItems(vector<Item*>* list,string* startsWith);
    //returns if an item is contained in a list
    bool containsItem(vector<Item*>* list,Item* item);
    //returns an item that has the same properties as comparisonItem
    Item* getItem(vector<Item*>* list,Item* comparisonItem);
};

#endif // MODEL_H
