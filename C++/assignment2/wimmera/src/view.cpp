#include <iostream>
#include <sstream>
#include <string>


#include "../include/view.h"
#include "../include/utility1.h"

using namespace std;


View::View()
{
    //ctor
}
//shows the login menu
int View:: showLoginMenu()
{
    int selection;
    cout <<"Welcome to the Wimmera Store."<<endl;
    cout <<"Please select an option"<<endl;
    cout <<"1. Login"<<endl;
    cout <<"0. Quit"<<endl;
    selection=numberInput("Your selection:",0,1);
    return selection;

}

//shows the main menu for a shopper
int View::showShopperMenu(string shopper)
{
    int selection;
    cout <<endl<<endl<<endl;
    cout <<"Welcome to Wimmera, "+shopper+" . You are logged in as a Shopper."<<endl;
    cout <<"Choose an option:"<<endl;
    cout <<"1. Add an item to shopping cart"<<endl;
    cout <<"2. View shopping cart"<<endl;
    cout <<"3. Remove an item from shopping cart"<<endl;
    cout <<"4. Checkout"<<endl;
    cout <<"5. List all items"<<endl;
    cout <<"6. Print previous purchases"<<endl;
    cout <<"7. Change User"<<endl;
    cout <<"0. Save/Quit"<<endl;
    selection=numberInput("Please make a valid selection from above: ",0,7);
    return selection;
}

//shows the main menu for an admin
int View::showAdminMenu(string Admin)
{
    int selection;
    cout <<endl<<endl<<endl;
    cout <<"Welcome to Wimmera, "+Admin+" . You are logged in as an Admin."<<endl;
    cout <<"Choose an option:"<<endl;
    cout <<"1. List all items"<<endl;
    cout <<"2. Add copies to item"<<endl;
    cout <<"3. Change price of item"<<endl;
    cout <<"4. Add new user"<<endl;
    cout <<"5. Change user"<<endl;
    cout <<"0. Save/Quit"<<endl;

    selection=numberInput("Please make a valid selection from above: ",0,5);
    return selection;
}


Item* View::selectItem(vector<Item*>* itemList)
{
    string prompt="The following titles match";
    listItems(itemList,&prompt);
    cout <<"0. cancel"<<endl;

    //input selection and return the item if they make a valid selection
    int selection=numberInput("What is your selection:",0,itemList->size());
    if(selection!=0)
        return itemList->at(selection-1); //-1 because the display doesnt match the actual index

    return 0;
}

//provides the facility to input the data to search for
string View::getSearchItem()
{
    string input;
    cout << "Enter title to search for:";
    cin >> input;
    return input;
}

//provides the facility to get numeric input between min and max
int View::numberInput(std::string message,int min,int max)
{
    string input;
    int value;
    //loop until they enter a valid number
    while(1)
    {
        cout << message;
        cin >> input;
        stringstream stream(input);
        //they have entered a valid number so exit the loop
        if(stream >> value)
        {
            if(value>=min && value<=max)
                break;
        }
        clearInputBuffer();
        cout <<"Invalid input !"<<endl;

    }
    return value;
}


//This function will iterate through a vector of items and present more detailed information with a prompt
void View::listItems(vector<Item*>* items,string* prompt)
{
    listItems(items,prompt,true,true,false,false,true);
}

void View::listItems(vector<Item*>* items,string* prompt,bool showPrice)
{
    listItems(items,prompt,true,false,false,false,true);
}

//Implementation for other listItem overloads
void View::listItems(vector<Item*>* items,string* prompt,bool showQty,bool showMediumAvail,bool showMedium,bool showSold,bool showPrice)
{
    if(prompt!=NULL)
        cout <<*prompt<<endl;

    for(unsigned int i=0; i<items->size(); i++)
    {
        Item* item=items->at(i);
        cout << i+1 << "."<< *item->getTitle()<<"(";
        //If the item is a book show the author otherwise show the artist
        bool itemisBook=dynamic_cast<Book*>(item)!=0;
        if(itemisBook)
        {
            Book* book=dynamic_cast<Book*>(item);
            cout <<*book->getAuthor();
        }
        else
        {
            Music* music=dynamic_cast<Music*>(item);
            cout <<*music->getArtist();
        }

        cout<<  "), ";
        if(showQty)
            cout << item->getQty()<< " copies , ";

        if(showMediumAvail)
        {
            if(item->getHasEversion())
                cout <<"electronic version available";
            else
                cout <<"no electronic version available";
        }
        if(showMedium)
        {
            if(item->getIsEversion())
                cout <<" (electronic version)";
            else
                cout <<"  (physical version)";
        }
        if(showSold)
        {
            cout <<" ---"<<item->getEQtySold()<<" eversion sold ";
            cout <<" ---"<<item->getQtySold()<<" copy sold";
        }
        if(showPrice)
        {
            string Ecost;
            if(item->getHasEversion())
                Ecost="$"+toStr(item->getECost());
            else
                Ecost="No Eversion";

            cout <<"  $"<<toStr(item->getPCost())<<
                 " / "<<Ecost;

        }
        cout <<endl;
    }
}

//provides the facility to get a string from the view
string View::getInput()
{
    string input="";
    cin >>input;
    return input;
}

//provides the facility to display an arbritrary message to the view
void View::writeMessage(string& message)
{
    cout <<message<<endl;
}

View::~View()
{
    //dtor
}
