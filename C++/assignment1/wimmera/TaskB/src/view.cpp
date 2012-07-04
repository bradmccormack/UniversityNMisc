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

int View::showMenu()
{
    int selection;
    cout <<endl<<endl<<endl;
    cout <<"Welcome to Wimmera"<<endl;
    cout <<"Choose an option:"<<endl;
    cout <<"1. Add an item to shopping cart"<<endl;
    cout <<"2. View shopping cart"<<endl;
    cout <<"3. Remove an item from shopping cart"<<endl;
    cout <<"4. Checkout"<<endl;
    cout <<"5. List all items"<<endl;
    cout <<"0. Quit"<<endl;

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
    listItems(items,prompt,true,true,false);
}

//Implementation for other listItem overloads
void View::listItems(vector<Item*>* items,string* prompt,bool showQty,bool showMediumAvail,bool showMedium)
{
    if(prompt!=NULL)
        cout <<*prompt<<endl;

    for(unsigned int i=0; i<items->size(); i++)
    {
        Item* item=items->at(i);

        cout << i+1 << "."
             << *item->getTitle()<<", ";
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
void View::writeMessage(string* message)
{
    cout <<*message<<endl;
}

View::~View()
{
    //dtor
}
