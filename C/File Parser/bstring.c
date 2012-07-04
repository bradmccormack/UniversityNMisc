#include "bstring.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*brads string "class" */

void stringClear(String *string)
{
    string->blocks=1;
    string->offset=0;
}

void stringInit(String *string)
{
   string->contents=malloc(STRINGSIZE*sizeof(char));
   stringClear(string);
}

void stringFree(String *string)
{
     if(string->contents!=NULL)
        free(string->contents);
}


char* stringAddChar(String *string,char c)
{
    /*time to grow the internal string*/
    if(string->offset==(STRINGSIZE*string->blocks)-1)
    {
        string->blocks++;
        string->contents=realloc(string->contents,STRINGSIZE*string->blocks*sizeof(char));
    }

    *(string->contents+string->offset)=c;
    *(string->contents+string->offset+1)='\0';
    string->offset++;
    return string->contents;
}

char* stringAddCharArray(String *string,char * toadd)
{
    /*time to grow the internal string*/
    while(*(toadd)!='\0')
    {
        stringAddChar(string,(char)*(toadd++));
    }
    return string->contents;

}

char* stringToCharArray(String *string)
{
    return string->contents;
}


void stringSet(String *string,char *stringtoset)
{
    stringInit(string);
    stringAddCharArray(string,stringtoset);
}



