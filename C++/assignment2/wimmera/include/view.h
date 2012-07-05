#ifndef VIEW_H
#define VIEW_H
#include <vector>
#include "../include/utility1.h"
#include "../include/item.h"
#include "../include/book.h"
#include "../include/music.h"
#include "../include/user.h"


class View
{
public:
    View();
    virtual ~View();

    virtual int showShopperMenu(string shopper); //shows the main menu for a shopper
    virtual int showAdminMenu(string admin); //shows the main menu for an admin
    virtual int showLoginMenu(); //shows the login menu

    string getInput(); //used to retrieve arbritrary text from the user interface
    void writeMessage(string& message); //used to send arbritrary text to the user interface
    Item* selectItem(vector<Item*>* itemList); //get the user to select an item from a list
    string getSearchItem(); //request something to search for from the view
    int numberInput(std::string message,int min,int max); //get a number between min and max
    void listItems(vector<Item*>* items,string* prompt,bool showQty,bool showMediumAvail,bool showMedium,bool showSold,bool showPrice); //full options
    void listItems(vector<Item*>* items,string* prompt);
    void listItems(vector<Item*>* items,string* prompt,bool showPrice);
    void listItems(vector<Item*>* items); //instruct view to show all items minimal detail with sequence number

protected:
private:

};

#endif // VIEW_H
