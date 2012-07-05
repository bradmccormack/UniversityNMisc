#include "include/controller.h"
#include "include/item.h"
#include "include/book.h"

using namespace std;

int main(int argc,char *argv[])
{
    if(argc!=3)
    {
       cout <<"Incorrect usage."<<endl;
       cout <<"usage: assign2 inputfile outputfile"<<endl;
       return -1;
    }
    else
    {
       cout <<"Loading "<<argv[1]<<". "<<argv[2]<<" will be used for saving data"<<endl;
    }

    //Let the controller handle main program loop and pass in files that will be used
    Controller controller;
    controller.Start(argv[1],argv[2]);

    return 0;
}
