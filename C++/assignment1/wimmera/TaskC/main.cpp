#include "include/controller.h"

#include "include/item.h"
#include "include/book.h"

using namespace std;

int main()
{
    //Let the controller handle main program loop
    Controller controller;
    controller.Start();

    //demonstrate overloaded operators
    //get info
    Book thesaurus;
    cin >>thesaurus;

    //show info
   cout <<thesaurus;

    return 0;
}
