#ifndef MODEL_H
#define MODEL_H

#include <map>

#include "../include/book.h"
#include "../include/user.h"
#include "../include/shop.h"
#include "../include/shoppingcart.h"
#include "../include/utility1.h"
#include "../include/customexceptions.h"

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
    void tryUpdateShopItem(Item* item,bool isEversion);
    //will return a user if one matches otherwise null
    User* getUser(string Id);
    //will add a new user
    void addUser(User user);
    //shop
    vector<Item*>* getShopItems(); //gets all shop items
    vector<Item*>* getShopItems(string* containsTitle); //gets all shopitems that match the filter
    double getTotalCost();

    void loadUsers(vector<string>& lines); //will parse the vector and get the users -TODO
    void loadBooks(vector<string>& lines)throw (FileParseException); //will parse the vector and get the books -TODO
    vector<string> saveAll(); //will produce a data file in the same format as input

    User& getLoggedinUser(); //returns the current logged in user
    bool Authenticate(string username,string password); // will return true if there is a user in the system with specced username and pass

protected:
private:
    const char* usersTag;
    const char* booksTag;
    const char* hash;
    const char* delim;
    int userFields;
    //will get the artist or the author for the item
    string getCreator(Item* item);
    //ptrs to shop and shoppingcart objects
    shop* m_shop;
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

    //The model has users and users have shopping carts
    map<string,User> m_users;
    User m_loggedinUser;

};

#endif // MODEL_H
