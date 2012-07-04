#include "../include/utility1.h"

////////////////////////////////////////////
void clearInputBuffer()     // function to clear the input buffer
{
    char symbol;
    do
    {
        cin.get(symbol);
    }
    while(symbol != '\n');
}
