#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../include/view.h"
#include "../include/model.h"

class Controller
{
public:
    Controller();
    virtual ~Controller();
    //function to kick off main program loop
    void Start();
    //various function to handle program flow
    void actionAddToCart();
    void actionRemoveFromCart();
    void actionViewCart();
    void actionListItems();
    void actionCheckout();
protected:
private:
    View* view;
    Model* model;


};

#endif // CONTROLLER_H
