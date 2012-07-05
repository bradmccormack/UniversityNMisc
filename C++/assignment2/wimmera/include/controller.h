#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../include/view.h"
#include "../include/model.h"
#include "../include/utility1.h"

class Controller
{
public:
    Controller();
    virtual ~Controller();
    //function to kick off main program loop
    void Start(string inFile,string outFile);
    //various function to handle program flow
    void actionAddToCart();
    void actionRemoveFromCart();
    void actionViewCart();
    void actionListItems();
    void actionCheckout();
    void actionShowShopItems();
    void actionAddCopiestoItem();
    void actionChangeItemCost();
    void actionAddnewUser();
    void actionShowHistory();
    bool Login();
protected:
private:
    View* view;
    Model* model;
    void LogoutMessage();
    string name;

};

#endif // CONTROLLER_H
