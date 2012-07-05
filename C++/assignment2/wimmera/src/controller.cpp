#include "../include/controller.h"
#include "../include/customexceptions.h"
#include <sstream>
#include <iostream>
#include <typeinfo>
using namespace std;

//This class represents co-ordination of actions within the application
//It will mediate between the model (data) and view (user interface)
Controller::Controller()
{

    this->model=new Model();
    this->view=new View();
}

//The main application loop.
void Controller::Start(string inFile,string outFile)
{
    // Load the text file and get the model to parse the users and books
    try
    {
        vector<string> lines = loadFile(inFile);
        model->loadUsers(lines);
        model->loadBooks(lines);
    }
    catch(FileNotFoundException& f)
    {
        string msg=f.what();
        view->writeMessage(msg);
        return;
    }
    catch(FileParseException& fp)
    {
        string msg=fp.what();
        view->writeMessage(msg);
        msg="Please check the input file for corruption";
        view->writeMessage(msg);
    }


    //atempt to do initial login. Return to main if they decide to quit
    if(!Login())
    {
        LogoutMessage();
        return;
    }
    //keep the programming running until the user has selected quit
    int action;
    do
    {
        //Admin is logged in show admin menu and offer admin functionality
        if(model->getLoggedinUser().getType()==ADMIN)
        {
            action=view->showAdminMenu(name);
            switch(action)
            {
            case 1:
                //List all items with purchase statistics
                actionShowShopItems();
                break;
            case 2:
                //add copies to item
                actionAddCopiestoItem();
                break;
            case 3:
                //change price of item
                actionChangeItemCost();
                break;
            case 4:
                //add new user
                actionAddnewUser();
                break;

            case 5:
                if(!Login())
                    action=0;
            }
        }
        else
        {
            action=view->showShopperMenu(name);
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

            case 6:
                actionShowHistory();
                break;

            case 7:
                if(!Login())
                    action=0;

            }
        }
    }
    while(action!=0);
    //Save changes that the shopper/admin has made
    saveFile(model->saveAll(),outFile);
    LogoutMessage();
}

//Loop through transaction history and show them all
void Controller::actionShowHistory()
{
    string message;
    User* logged=&model->getLoggedinUser();
    vector<vector<Item*> > items=logged->getHistory();
    for(unsigned int i=0; i<items.size(); i++)
    {
        vector<Item*> transaction=items.at(i);
        message="Transaction "+toStr(i+1)+" ,You purchased the following";
        view->listItems(&transaction,&message,true,true,true,true,true);
    }
}

void Controller::actionShowShopItems()
{
    string msg="Results found";
    view->listItems(model->getShopItems(),&msg,true,true,true,true,true);
}

void Controller::actionAddCopiestoItem()
{
    //find items from the shop that contain their query
    string title=view->getSearchItem();
    Item* item=view->selectItem(model->getShopItems(&title));
    if(item!=NULL)
    {
        //I chose an arbritrary maximum qty to add. The assignment doesn't specify
        string msg="How many copies would you like to add (0-99999):";
        int numtoAdd=view->numberInput(msg,0,99999);
        item->setQty(item->getQty()+numtoAdd);
        msg="Total number of copies available for this title is now "+toStr(item->getQty());
        view->writeMessage(msg);
    }
}

void Controller::actionChangeItemCost()
{
    string title=view->getSearchItem();
    Item* item=view->selectItem(model->getShopItems(&title));
    string msg,input;
    if(item!=NULL)
    {
        //I chose an arbritrary maximum qty to add. The assignment doesn't specify
        if(item->getHasEversion())
        {
            msg="Do you want to change the price of eversion (y/n)";
            view->writeMessage(msg);
            input=view->getInput();
            if(input=="y"|| input=="Y")
            {
                msg="What is the new price :";
                view->writeMessage(msg);
                input=view->getInput();
                item->setECost(toDouble(input));
                msg="The price of eversions of this title are now "+input;
                view->writeMessage(msg);
            }
        }
        msg="Do you want to change the price of the physical version (y/n)";
        view->writeMessage(msg);
        input=view->getInput();
        if(input=="y"||input=="Y")
        {
            msg="What is the new price :";
            view->writeMessage(msg);
            input=view->getInput();
            item->setPhysicalCost(toDouble(input));
            msg="The price of physical copies of this title are now "+input;
            view->writeMessage(msg);
        }
    }
}

//add a new user
void Controller::actionAddnewUser()
{
    string message,input;
    while(true)
    {
        message="What is the id of the new user:";
        view->writeMessage(message);
        string id=view->getInput();
        User* user=model->getUser(input);
        if(user!=NULL)
        {
            message="This id is already in use. Do you want to continue (y/n)";
            view->writeMessage(message);
            input=view->getInput();
            if(input=="n" || input=="N")
                return;
        }
        else
        {
            User newuser;
            cin >>newuser;
            newuser.setId(id);
            message=newuser.getName()+" has been added as a user.";
            model->addUser(newuser);
            view->writeMessage(message);
            return;
        }
    }
}

void Controller::LogoutMessage()
{
    string message="Goodbye "+model->getLoggedinUser().getName();
    view->writeMessage(message);
    message="Please come again";
    view->writeMessage(message);
}

bool Controller::Login()
{
    int action=-1;
    string msg,username,password;

    while(true)
    {
        action=view->showLoginMenu();
        //quit app
        if(action==0)
        {
            //user decided to quit
            return false;
        }
        //Confirm login information and attempt to authenticate
        msg="Enter your username below:";
        view->writeMessage(msg);
        username=view->getInput();

        msg="Enter your password below:";
        view->writeMessage(msg);
        password=view->getInput();
        if(!model->Authenticate(username,password))
        {
            msg="Username or password is incorrect!";
            view->writeMessage(msg);
        }
        else
        {
            name=model->getLoggedinUser().getName();
            return true;
        }
    }
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
        this->view->writeMessage(message);
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
            this->view->writeMessage(message);
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
                this->view->writeMessage(message);
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
                this->view->writeMessage(message);
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
            Book* book=dynamic_cast<Book*>(itemSelected);
            //use the book cost in the correct part of the constructor signature depending on eversion or not
            if(eVersion)
            {
                itemToAdd=new Book(*book->getTitle(),*book->getAuthor(),true,1,0.0,book->getECost());
                itemToAdd->setIsEversion(true);
            }
            else
                itemToAdd=new Book(*book->getTitle(),*book->getAuthor(),book->getHasEversion(),1,book->getPCost(),0.0);
        }
        //or music and instantiate new music
        else
        {
            Music* music=dynamic_cast<Music*>(itemSelected);
            if(eVersion)
            {
                itemToAdd=new Music(*music->getTitle(),*music->getArtist(),true,1,0.0,music->getCost());
                itemToAdd->setIsEversion(true);
            }
            else
                itemToAdd=new Music(*music->getTitle(),*music->getArtist(),music->getHasEversion(),1,music->getCost(),0.0);
        }
        string result=this->model->addToCart(itemToAdd);
        this->view->writeMessage(result);
    }
}

//handles ViewCart action
void Controller::actionViewCart()
{
    //get items in Shoppingcart and show them. If empty show nothing
    vector<Item*>* Items=this->model->getShoppingCartItems();

    string message;
    if(Items->size()==0)
    {
        message="Your shopping cart is empty";
        this->view->writeMessage(message);
        return;
    }
    //show all items in the cart in the view
    message="Your shopping cart contains the following:";
    this->view->listItems(Items,&message,true,false,true,false,false);
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
        this->view->writeMessage(message);
        return;
    }
    //Show shopping cart and request input from view
    message="Your Shopping Cart contains the following:";
    this->view->listItems(items,&message,false,false,true,false,true); //show medium type to distinguish physical and electroic purchases
    message="0. cancel";
    this->view->writeMessage(message);

    int choice=this->view->numberInput("Which number item do you wish to remove:",0,items->size());
    if(choice!=0)
    {
        //confirm the selection they have made and delete it if they confirm
        Item* selected=items->at(choice-1);
        message="Selected "+*selected->getTitle();
        this->view->writeMessage(message);
        message="Do you want to remove it (yes/no):";
        string yn="";
        while(1)
        {
            this->view->writeMessage(message);
            yn=this->view->getInput();
            if(yn=="yes" || yn=="no")
                break;
        }
        if(yn=="yes")
        {
            model->removeFromCart(selected);
            message="Item removed from Shopping Cart";
            this->view->writeMessage(message);
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
        view->writeMessage(message);
        return;
    }
    //show total spent
    stringstream out;
    out << model->getTotalCost();
    message="Thank you for your patronage ! Your total price is $"+out.str();
    view->writeMessage(message);

    //If they spend 10% more than their limit make them an offer to become a member
    Shoppingcart* loggedinUserCart=model->getLoggedinUser().getShoppingCart();
    int sumhistory=loggedinUserCart->getSumHistory();

    loggedinUserCart->setSumHistory(sumhistory+model->getTotalCost());
    sumhistory=loggedinUserCart->getSumHistory();

    if(loggedinUserCart->getSumHistory()>=loggedinUserCart->getSpendingLimit()*1.10)
    {
        string message="Your total spending at Wimmer has exceeded "+toStr(loggedinUserCart->getSpendingLimit())+
                       "You qualify to become a member. This will remove your spending limit and increase your discounts!";
        view->writeMessage(message);
        message="Would you like to become a member (y/n) :";
        view->writeMessage(message);
        string input=view->getInput();
        if(input=="y")
        {
            model->getLoggedinUser().setMember(true);
            message="Congratulations "+model->getLoggedinUser().getName()+" you are now a member!";
            view->writeMessage(message);
        }
    }

    //save the contents of the cart to the users history

    model->getLoggedinUser().addHistory(*items);

    //update shop qtys
    for(unsigned int i=0; i<items->size(); i++)
    {
        Item* curritem=items->at(i);
        //if it's in the shop then adjust the shop stock. Otherwise just continue on*/
        model->tryUpdateShopItem(curritem,curritem->getIsEversion());
        model->removeFromCart(curritem);
        //Need to create a new transaction here I believe
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
        this->view->listItems(Items,&message,true);
    }
    else
    {
        message="The shop currently has no titles";
        this->view->writeMessage(message);
    }
    message="Shop item quantities will be adjusted upon checkout!";
    this->view->writeMessage(message);
    return;

}

Controller::~Controller()
{
    //dtor
    delete this->model;
    delete this->view;
}
