#include "../include/model.h"
#include <stdlib.h>
#include <iostream>
#include <iterator>


/*I believe I am using my Model as a Facade as well.
   It is wrapping two other objects and mediating on their behalf
*/

//constructor
Model::Model()
{
    //allocate memory for the shop and shopping cart
    m_shop=new shop();


    /*I was thinking of filling the shop in its constructor but that is too tightly coupled.
    /If a different Shop was to exist then it might require different products.
    The model can fill the shop.
    */

    m_shop->addItem(new Music("At Folsom Prison","Johnny Cash",true,10,7.56,10.99));
    m_shop->addItem(new Music("The Essential Johnny Cash","Johnny Cash",true,5,12.64,16.99));
    m_shop->addItem(new Music("American Recordings","Johnny Cash",true,0,9.99,9.99));
    m_shop->addItem(new Music("Classic Nursery Rhymes","Hap Palmer",false,0,13.73,0.0));
    m_shop->addItem(new Music("Classic Nursery Rhymes","Susie Tallman",true,1,11.47,8.99));

    //Related to parsing files
    usersTag="#users";
    booksTag="#books";
    hash="#";
    delim="|";
    userFields=5;

}

//will prepare data  with the same format as the input file ready for writing
vector<string> Model::saveAll()
{
    vector<string> data;
    string line;

    //book header
    data.push_back(string("#books"));
    data.push_back(string("#title|author|no. of copies|ebook?(yes,no)|physical-price|ebook-price"));
    //write out all items that are books
    for(unsigned int i=0; i<m_shop->getItems()->size(); i++)
    {
        Item* item=m_shop->getItems()->at(i);
        if(dynamic_cast<Book*>(item)!=0)
        {
            Book* book=dynamic_cast<Book*>(item);
            string haseversion;
            if(book->getHasEversion())
                haseversion="yes";
            else
                haseversion="no";

            line=*book->getTitle()+delim+
                 *book->getAuthor()+delim+
                 toStr(book->getQty())+delim+
                 haseversion+delim+
                 toStr(book->getPCost())+delim+
                 toStr(book->getECost());
            data.push_back(line);
        }
    }
    //users header
    data.push_back(string("#users"));
    data.push_back(string("#id|password|name|email|shopper/admin|member/non-member[|cart-title1|cart-author1|ebook?|price-paid]*   for any items in cart"));
    //write out users
    map<string,User>::iterator iter;
    for(iter=m_users.begin(); iter!=m_users.end(); iter++)
    {
        User user=iter->second;
        string type,member;
        if(user.getType()==ADMIN)
            type="admin";
        else
            type="shopper";

        if(user.getMember()==true)
            member="member";
        else
            member="non-member";

        line=user.getId()+delim+
             user.getPassword()+delim+
             user.getName()+delim+
             user.getEmail()+delim+
             type+delim+
             member;
        //add the items in their cart
        vector<Item*>* items=user.getShoppingCart()->getItems();
        string strdelim=toStr(delim);
        for(unsigned int i=0; i<items->size(); i++)
        {

            Item* item=items->at(i);
            //Don't bother saving music as Forum post says no marking
            if(dynamic_cast<Book*>(item)==0)
                continue;

            Book* book=dynamic_cast<Book*>(item);
            string ebook;
            double price;
            //note if the item is not an eversion then use book as the data
            if(book->getIsEversion())
            {
                ebook="ebook";
                price=book->getECost();
            }

            else
            {
                ebook="book";
                price=book->getPCost();
            }
            //Note the file format does not allow for item qty so hard code as 1
            string cartItemline=strdelim+*book->getTitle()+
                                strdelim+*book->getAuthor()+
                                strdelim+ebook+
                                strdelim+toStr(price);
            line.append(cartItemline);
        }
        data.push_back(line);
    }
    return data;
}

//will update shop item with new information from item arg if it exists in the shop
void Model::tryUpdateShopItem(Item* item,bool isEversion)
{
    //find matching item in shop
    Item* shopItem=getItem(getShopItems(),item);
    int qty=item->getQty();

    //if its found adjust the qty for amount left and the amount sold
    if(shopItem!=NULL)
    {
        if(isEversion)
        {
            int esold=shopItem->getEQtySold();
            shopItem->setEQtySold(esold+1);
        }
        else
        {
            shopItem->setQty(shopItem->getQty()-qty);
            shopItem->setQtySold(shopItem->getQtySold()+qty);
        }
    }
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

            getLoggedinUser().getShoppingCart()->setSum(getLoggedinUser().getShoppingCart()->getSum()-itemcost);
        }
    }
}

//will attempt to purchase the item and return success or failure
string Model::addToCart(Item* ItemToAdd)
{
    string result="";

    //check to see if purchasing tt)?his item would exceed their spending budget if so return with message
    Shoppingcart* cart=getLoggedinUser().getShoppingCart();
    if((cart->getSum()+ItemToAdd->getCost())>cart->getSpendingLimit())
    {
        result="purchasing "+*ItemToAdd->getTitle()+" will exceed your spending limit ($100) sorry !";
        return result;
    }
    Item* itemInCart=getItem(cart->getItems(),ItemToAdd);

    //if the item is already in the cart then increment the count
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
        cart->addItem(ItemToAdd);
    }

    cart->setSum(cart->getSum()+ItemToAdd->getCost());
    result=*ItemToAdd->getTitle()+" has been added to the cart";
    return result;
}

// Will get the artist or author depending on Item type
string Model::getCreator(Item* item)
{
    if(dynamic_cast<Book*>(item)!=0)
    {
        Book* currBook=dynamic_cast<Book*>(item);
        return *currBook->getAuthor();
    }
    else
    {
        Music* currMusic=dynamic_cast<Music*>(item);
        return *currMusic->getArtist();
    }
}

//returns a single item from a list where the title starts with a specific value
Item* Model::getItem(vector<Item*>* list,Item* item)
{
    vector<Item*>* items=getItems(list,item);
    for(unsigned int i=0; i<items->size(); i++)
    {
        string iteminListCreator=getCreator(items->at(i));
        string itemArgCreator=getCreator(item);
        if(iteminListCreator==itemArgCreator)
            return items->at(i);
    }
    return NULL;
}

//overloaded getItems that contains a filter. It will return all items that start with the filter.
//Note assignment 2 I can see the search is case insensitive. I have done that
vector<Item*>* Model::getItems(vector<Item*>* list,string* startsWith)
{
    string& start=*startsWith;
    strUpper(start);

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
        strUpper(currTitle);

        if(currTitle.find(start)==0)
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
        if(find==0)
            foundItems->push_back(curr);
    }
    return foundItems;
}

//will get the total cost for the logged in user
double Model::getTotalCost()
{
    return getLoggedinUser().getShoppingCart()->getSum();
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

//getShoppingCartItems will get all items in logged in users shopping cart
vector<Item*>* Model::getShoppingCartItems()
{
    return getLoggedinUser().getShoppingCart()->getItems();
}

bool Model::Authenticate(string userId,string password)
{
    map<string,User>::iterator it;
    it=m_users.find(userId);
    //If there is no matching user can't authenticae
    if(it==m_users.end())
    {
        return false;
    }
    //compare the password and if ok then assign logged in user (second refers to the value not the key)
    User user=(*it).second;
    if( user.getPassword()==password)
    {
        m_loggedinUser=user;
        return true;
    }
    return false;
}

User& Model::getLoggedinUser()
{
    return m_loggedinUser;
}

//will parse the vector and get the users
void Model::loadUsers(vector<string>& lines)
{
    bool inUserBlock=false;
    bool firstTagIgnored=false;
    for(unsigned int i=0; i<lines.size(); i++)
    {
        string& current=lines.at(i);
        if(!inUserBlock)
        {
            if(current.find(usersTag)==0)
                inUserBlock=true; //start processing users
        }
        else
        {
            // Ignore the id line and potentially any other tags
            if(current.find(hash)==0)
            {
                if(!firstTagIgnored)
                {
                    firstTagIgnored=true;
                    continue;
                }
                else
                {
                    inUserBlock=false;
                    continue;
                }
            }
            // Tokenize the string
            vector<string> tokens;
            unsigned int prev=0;
            size_t pos=current.find(delim);
            while(true)
            {
                tokens.push_back(current.substr(prev,pos-prev));
                prev=pos+1;
                pos=current.find(delim,prev);

                if(pos==string::npos)
                    break;
            }
            // Add the final token
            tokens.push_back(current.substr(prev,current.size()-prev));

            // Fillout details for a new user and add to the User map
            User* newuser=new User();
            newuser->setId(tokens.at(0));
            newuser->setPassword(tokens.at(1));
            newuser->setName(tokens.at(2));
            newuser->setEmail(tokens.at(3));
            if(tokens.at(4)=="shopper")
                newuser->setType(SHOPPER);
            else if(tokens.at(4)=="admin")
                newuser->setType(ADMIN);

            // Find out how many items are in the cart and add them
            int amountofitems=(tokens.size()-6)/4;
            int offset=userFields+1;
            for(int i=0; i<amountofitems; i++)
            {

                //Book::Book(string Title,string Author,bool hasEbook,int StockQty,double pPrice,double ePrice)'
                bool ebook=tokens.at(offset+2)=="ebook";
                double price=toDouble(tokens.at(offset+3));
                double phyprice;
                double eprice;
                if(ebook)
                {
                    phyprice=0;
                    eprice=price;
                }
                else
                {
                    phyprice=price;
                    eprice=0;
                }
                //create the new item - Note the file format does not allow for item qty so hard code as 1
                Item* savedCartItem=
                    new Book(tokens.at(offset),tokens.at(offset+1),ebook,1,phyprice,eprice);
                savedCartItem->setIsEversion(ebook);
                newuser->getShoppingCart()->addItem(savedCartItem);
                offset+=4;
            }
            m_users[newuser->getId()]=*newuser;
            // m_users.insert(pair<string,User>(newuser->getId(),*newuser)); //I think above is appropriate
        }
    }

}
//will parse the vector and get the books
void Model::loadBooks(vector<string>& lines) throw (FileParseException)
{
    bool inBookBlock=false;
    bool firstTagIgnored=false;
    for(unsigned int i=0; i<lines.size(); i++)
    {
        string& current=lines.at(i);
        if(!inBookBlock)
        {
            if(current.find(booksTag)==0)
                inBookBlock=true; //start processing books
        }
        else
        {
            // Ignore the explanation line
            if(current.find(hash)==0)
            {
                if(!firstTagIgnored)
                {
                    firstTagIgnored=true;
                    continue;
                }
                else
                {
                    inBookBlock=false;
                    continue;
                }
            }

            // Tokenize the string
            vector<string> tokens;
            unsigned int prev=0;
            size_t pos=current.find(delim);
            while(true)
            {
                tokens.push_back(current.substr(prev,pos-prev));
                prev=pos+1;
                pos=current.find(delim,prev);

                if(pos==string::npos)
                    break;
            }
            //add the final token
            tokens.push_back(current.substr(prev,current.size()-prev));

            int qty=-1;
            stringstream qtystream(tokens.at(2));
            if(!(qtystream >> qty))
                throw FileParseException(string("Cannot parse file correctly. Failed on reading qty."));

            bool hasEversion;
            if(tokens.at(3)=="yes")
                hasEversion=true;
            else
                hasEversion=false;

            //Parse the cost and assign it to phys cost and ecost
            //
            double phycost;
            stringstream phyconv(tokens.at(4));
            if(!(phyconv>>phycost))
                throw FileParseException(string("Cannot parse file correctly. Failed on reading physical cost."));

            double ecost;
            stringstream econv(tokens.at(5));
            if(!(econv>>ecost))
                throw FileParseException(string("Cannot parse file correctly. Failed on reading e cost."));

            Book* newBook=new Book(tokens.at(0),tokens.at(1),hasEversion,qty,phycost,ecost);
            newBook->setIsEversion(false);
            m_shop->addItem(newBook);

        }
    }
}

//will return a user if one matches otherwise null
User* Model::getUser(string Id)
{
    map<string,User>::iterator it;
    it=m_users.find(Id);
    if(it==m_users.end())
        return NULL;
    return &it->second;

}

//Will add a new user
void Model::addUser(User user)
{
    m_users[user.getId()]=user;
}

//destructor
Model::~Model()
{
    //dealloate memory for the shop and shopping cart
    delete m_shop;


}

