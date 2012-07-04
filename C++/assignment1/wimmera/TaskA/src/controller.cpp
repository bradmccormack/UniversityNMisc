#include "../include/controller.h"
#include <sstream>
#include <iostream>
#include <typeinfo>
using namespace std;

//This class represents co-ordination of actions within the application
//It will mediate between the model (data) and view (user interface)
Controller::Controller()
{
    //ctor
    this->model=new Model();
    this->view=new View();
}

//The main application loop.
void Controller::Start()
{
    //keep the programming running until the user has selected quit
    int action;
    do
    {
        action=view->showMenu();
        switch(action)
        {
        case 1:
            actionAddToCart();
            break;
        case 2:
            actionViewCart();
            break;
        case 3:
            actionRemoveFromCart();
            break;
        case 4:
            actionCheckout();
            break;

        case 5:
            actionListItems();
            break;
        }
    }
    while(action!=0);
    string message="Goodbye !";
    view->writeMessage(&message);
}

//handles addtocart action
void Controller::actionAddToCart()
{
    //request from view the searchItem
    string searchTitle=this->view->getSearchItem();
    bool eVersion;

    //request any matching Items
    vector<Item*>* foundItems=model->getShopItems(&searchTitle);

    string message;
    //Nothing was found so inform UI and return
    if(foundItems->size()==0)
    {
        message="There is no title starting with that";
        this->view->writeMessage(&message);
        return;
    }
    //request to add to the shopping cart.
    else
    {
        Item* itemSelected=this->view->selectItem(foundItems);
        if(itemSelected==0) //return if they cancel
            return;

        message="Do you want to buy this in electronic form (yes/no) only:";
        string input="";
        do
        {
            this->view->writeMessage(&message);
            input=this->view->getInput();
        }
        while(input!="yes" && input!="no");

        //if they request to buy in eform
        if(input=="yes")
        {
            //if there is no eform available then inform them and return
            if(!itemSelected->getHasEversion())
            {
                message=*itemSelected->getTitle()+" does not have an electronic version available sorry !";
                this->view->writeMessage(&message);
                return;
            }
            //mark item to add as eversion
            eVersion=true;
        }
        else
        {
            if(itemSelected->getQty()==0)
            {
                message=*itemSelected->getTitle()+" Has no physical copies available sorry !";
                this->view->writeMessage(&message);
                return;
            }
            eVersion=false;
        }

        /*Attempt to add the item to the shopping cart and write out result in view
        We need derrived type information so we can instantiate the correct type
        Then use the overloaded constructor so it will set it's information and price*/
        Item* itemToAdd;

        if(dynamic_cast<Book*>(itemSelected)!=0)
        {
            Book* book=(Book*) itemSelected;
            itemToAdd=new Book(*book->getTitle(),*book->getAuthor(),book->getHasEversion(),1);
        }
        //or music and instantiate new music
        if(dynamic_cast<Music*>(itemSelected)!=0)
        {
            Music* music=(Music*) itemSelected;
            itemToAdd=new Music(*music->getTitle(),*music->getArtist(),music->getHasEversion(),1);
        }

        itemToAdd->setIsEversion(eVersion);
        string result=this->model->addToCart(itemToAdd);
        this->view->writeMessage(&result);
    }
}

//handles ViewCart action
void Controller::actionViewCart()
{
    //get items in shoppingcart and show them. If empty show nothing
    vector<Item*>* Items=this->model->getShoppingCartItems();

    string message;
    if(Items->size()==0)
    {
        message="Your shopping cart is empty";
        this->view->writeMessage(&message);
        return;
    }
    //show all items in the cart in the view
    message="Your shopping cart contains the following:";
    this->view->listItems(Items,&message,true,false,true);
}

//handles Remove from cart action
void Controller::actionRemoveFromCart()
{
    vector<Item*>* items=this->model->getShoppingCartItems();

    //check if Shopping cart is empty and handle
    string message;
    if(items->size()==0)
    {
        message="Your Shopping Cart is empty. Nothing to remove";
        this->view->writeMessage(&message);
        return;
    }
    //Show shopping cart and request input from view
    message="Your Shopping Cart contains the following:";
    this->view->listItems(items,&message,false,false,true); //show medium type to distinguish physical and electroic purchases
    message="0. cancel";
    this->view->writeMessage(&message);

    int choice=this->view->numberInput("Which number item do you wish to remove:",0,items->size());
    if(choice!=0)
    {
        //confirm the selection they have made and delete it if they confirm
        Item* selected=items->at(choice-1);
        message="Selected "+*selected->getTitle();
        this->view->writeMessage(&message);
        message="Do you want to remove it (yes/no):";
        string yn="";
        while(1)
        {
            this->view->writeMessage(&message);
            yn=this->view->getInput();
            if(yn=="yes" || yn=="no")
                break;
        }
        if(yn=="yes")
        {
            model->removeFromCart(selected);
            message="Item removed from Shopping Cart";
            this->view->writeMessage(&message);
        }
    }
}

//handles Checkout action
void Controller::actionCheckout()
{
    //get all shopping cart items
    string message;
    vector<Item*>* items=model->getShoppingCartItems();
    //show message if it's empty and return
    if(items->size()==0)
    {
        message="You have not made any purchases. Your shopping cart is empty";
        view->writeMessage(&message);
        return;
    }
    //show total spent
    stringstream out;
    out << model->getTotalCost();
    message="Thank you for your patronage ! Your total price is $"+out.str();
    view->writeMessage(&message);

    //update shop qtys
    for(unsigned int i=0; i<items->size(); i++)
    {
        Item* curritem=items->at(i);
        /*if the current item is not electronic
        correlate the current item with the shop
        if it's in the shop then adjust the shop stock. Otherwise just continue on*/
        if(!curritem->getIsEversion())
            model->tryUpdateShopItem(curritem);

        model->removeFromCart(curritem);
    }
}

//handles listing items in cart
void Controller::actionListItems()
{
    //go get items from the model
    vector<Item*>* Items=model->getShopItems();
    string message;
    if(Items->size()>0)
    {
        //if some items were found list them
        message="The following titles are available";
        this->view->listItems(Items,&message);
    }
    else
    {
        message="The shop currently has no titles";
        this->view->writeMessage(&message);
    }
    message="Shop item quantities will be adjusted upon checkout!";
    this->view->writeMessage(&message);
    return;

}

Controller::~Controller()
{
    //dtor
    delete this->model;
    delete this->view;
}
