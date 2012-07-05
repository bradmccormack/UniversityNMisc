#include "../include/user.h"

User::User()
{
    m_shoppingcart=new Shoppingcart();
}

void User::setType(ShopperType type)
{
    m_type=type;
    m_shoppingcart->setSpendingLimit(100.0);
}

//Will append a list of items to the users history
void User::addHistory(vector<Item*> Items)
{
    m_history.push_back(Items);
}

Shoppingcart* User::getShoppingCart()
{
    return m_shoppingcart;
}

istream &operator>>(istream &stream, User &ob)
{
    string input;
    do
    {
        cout <<endl<<"Choose a password:";
        stream >>ob.m_password;
        cout <<"Retype password:";
        cin >> input;
        if(input!=ob.m_password)
            cout <<"Incorrect. Start again."<<endl;
    }
    while(input!=ob.m_password);

    cout <<"What is the users name:";
    stream >>ob.m_name;
    cout <<"What is the users email:";
    stream >>ob.m_email;
    bool valid=false;
    while(!valid)
    {
        cout <<"Is the user a shopper(s) or admin(a):";
        cin >>input;
        if(input=="s")
        {
            ob.m_type=SHOPPER;
            valid=true;
        }

        if(input=="a")
        {
            ob.m_type=ADMIN;
            valid=true;
        }

    }
    return stream;
}


User::~User()
{
}
