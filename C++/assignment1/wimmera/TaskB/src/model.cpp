#include "../include/model.h"
#include <stdlib.h>
#include <iostream>

/*I believe I am using my Model as a Facade as well.
   It is wrapping two other objects and mediating on their behalf
*/

//constructor
Model::Model()
{
    //allocate memory for the shop and shopping cart
    m_shop=new shop();
    m_shoppingcart=new shoppingcart(100.0);

    /*I was thinking of filling the shop in its constructor but that is too tightly coupled.
    /If a different Shop was to exist then it might require different products.
    The model can fill the shop.
    */
    this->m_shop->addItem(new Book("Absolute C++","Savitch",true,5));
    this->m_shop->addItem(new Book("C++: How to Program","Deitel and Deitel",true,0));
    this->m_shop->addItem(new Music("In the Ghetto","Elvis Presley",true,4));
    this->m_shop->addItem(new Book("Computing Concepts with C++","Stroustrup",false,5));
    this->m_shop->addItem(new Music("How Many Roads Must a Man Walk Down?","Bob Dylan?",false,0));
    this->m_shop->addItem(new Book("C++ Software Solutions","Lafore and Sutter",false,5));
    this->m_shop->addItem(new Book("Hard Days Night","The Beatles",true,3));
    this->m_shop->addItem(new Book("C++ Program Design","Stroustrup",true,1));
    this->m_shop->addItem(new Music("Maggie May","Rod Stewart",true,5));
    this->m_shop->addItem(new Book("Test book","Test Author",true,2));
}


//will update shop item with new information from item arg if it exists in the shop
void Model::tryUpdateShopItem(Item* item)
{
    //find matching item in shop
    Item* shopItem=getItem(getShopItems(),item);
    //if its found adjust the qty
    if(shopItem!=NULL)
        shopItem->setQty(item->getQty());
}

void Model::removeFromCart(Item* item)
{
    //remove from vector and update sum in the shopping cart.
    vector<Item*>* items=getShoppingCartItems();

    vector<Item*>::iterator iter=items->begin(); //practice using an iterator instead of index
    //loop through all items in the shop and see if anything starts with the value specified by containsTitle
    while(iter!=items->end())
    {

        Item* curritem=*iter;
        string* curTitle=curritem->getTitle();
        //have to do title comparison to handle physical and eversions
        if(curTitle->find(item->getTitle()==0))
        {
            //update shopping cart cost
            double itemcost=curritem->getQty()*curritem->getCost();
            //delete and update the iterator at the same time
            iter=items->erase(iter++);
            m_shoppingcart->setSum(m_shoppingcart->getSum()-itemcost);
        }
    }

}

//will attempt to purchase the item and return success or failure
string Model::addToCart(Item* ItemToAdd)
{
    //dont forget to set the qty to NULL when adding an item for the first time Brad!
    string result="";

    //check to see if purchasing this item would exceed their spending budget if so return with message
    if((this->m_shoppingcart->getSum()+ItemToAdd->getCost())>m_shoppingcart->getSpendingLimit())
    {
        result="purchasing "+*ItemToAdd->getTitle()+" will exceed your spending limit ($100) sorry !";
        return result;
    }
    Item* itemInCart=getItem(m_shoppingcart->getItems(),ItemToAdd);

    if(itemInCart!=NULL)
    {
        if(ItemToAdd->getIsEversion())
        {
            result="You already have an electronic version of "+*ItemToAdd->getTitle()+" In your cart";
            return result;
        }
        //check to see if purchasing this item would exceed the availability amount in the shop
        //note this only applies for physical items
        else
        {
            //find the matching shop item
            Item* itemInShop=getItem(m_shop->getItems(),ItemToAdd);
            if(itemInShop==NULL)
                return NULL;
            //make sure the qty in the shopping card doesn't exceed the shop availability
            if(itemInCart->getQty()==itemInShop->getQty())
            {
                result="There are no physical copies left of "+*ItemToAdd->getTitle();
                return result;
            }
            itemInCart->setQty(itemInCart->getQty()+1);
        }
    }
    else
    {
        //add it to the cart now
        ItemToAdd->setQty(1);
        m_shoppingcart->addItem(ItemToAdd);
    }

    m_shoppingcart->setSum(m_shoppingcart->getSum()+ItemToAdd->getCost());
    result=*ItemToAdd->getTitle()+" has been added to the cart";
    return result;
}

//returns a single item from a list where the title starts with a specific value
Item* Model::getItem(vector<Item*>* list,Item* item)
{
    vector<Item*>* items=getItems(list,item);
    if(items->size()>0)
        return items->at(0);
    else
        return NULL;
}

//overloaded getItems that contains a filter. It will return all items that start with the filter.
vector<Item*>* Model::getItems(vector<Item*>* list,string* startsWith)
{
    vector<Item*>* foundItems=new vector<Item*>();
    vector<Item*>::const_iterator iter; //practice using an iterator instead of index
    //loop through all items in the shop and see if anything starts with the value specified by containsTitle
    for(iter=list->begin();
            iter!=list->end();
            iter++)
    {
        Item* curr=*iter;
        //if it finds a match add it to the return vector
        string currTitle=*curr->getTitle();
        if(currTitle.find(*startsWith)==0)
            foundItems->push_back(*iter);
    }
    return foundItems;
}

vector<Item*>* Model::getItems(vector<Item*>* list,Item* item)
{

    vector<Item*>* foundItems=new vector<Item*>();
    for(unsigned int i=0; i<list->size(); i++)
    {
        Item* curr=list->at(i);
        string* currTitle=curr->getTitle();
        string* itemTitle=item->getTitle();
        int find=itemTitle->find(*currTitle);

        if(find==0 &&curr->getIsEversion()==item->getIsEversion())
            foundItems->push_back(curr);
    }
    return foundItems;
}

double Model::getTotalCost()
{
    return m_shoppingcart->getSum();
}


vector<Item*>* Model::getShopItems(string* containsTitle)
{
    vector<Item*>* shopItems=getItems(m_shop->getItems(),containsTitle);
    return shopItems;
}
//getItems with no params. Will get all Items from the Shop
vector<Item*>* Model::getShopItems()
{
    return m_shop->getItems();
}

//getShoppingCartItems will get all items in the shopping cart
vector<Item*>* Model::getShoppingCartItems()
{
    return m_shoppingcart->getItems();
}

//destructor
Model::~Model()
{
    //dealloate memory for the shop and shopping cart
    free (m_shop);
    free (m_shoppingcart);
}
