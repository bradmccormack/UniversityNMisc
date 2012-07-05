#ifndef USER_H
#define USER_H

#include <iostream>
#include "../include/shoppingcart.h"

using namespace std;

enum ShopperType
{
    SHOPPER,
    ADMIN
};

class User
{
public:
    User();
    virtual ~User();

    //inline the setters and getters
    void setId(string id)
    {
        m_id=id;
    }
    void setPassword(string password)
    {
        m_password=password;
    }
    void setName(string name)
    {
        m_name=name;
    }
    void setEmail(string email)
    {
        m_email=email;
    }
    void setType(ShopperType type);
    void setMember(bool isMember)
    {
        m_isMember=isMember;
    }
    vector<vector<Item*> > getHistory()
    {
        return m_history;
    }

    string getId()
    {
        return m_id;
    }
    string getPassword()
    {
        return m_password;
    }
    string getName()
    {
        return m_name;
    }
    string getEmail()
    {
        return m_email;
    }
    ShopperType getType()
    {
        return m_type;
    }
    bool getMember()
    {
        return m_isMember;
    }
    Shoppingcart* getShoppingCart();

    void addHistory(vector<Item*> Items); //will add contents of a shopping cart to the history

    friend istream &operator>>(istream &stream, User &ob);
protected:
private:
    string m_id;
    string m_password;
    string m_name;
    string m_email;
    ShopperType m_type;
    bool m_isMember;
    Shoppingcart* m_shoppingcart;
    vector<vector<Item*> > m_history;



};

#endif // USER_H
