/****************************************************************************
* COSC2138/CPT220 - Programming Principles 2A
* Study Period 2  2010 Assignment #2 - index program
* Full Name        : Bradley Jason Mccormack
* Student Number   : s3258798
* Course Code      : COSC2138
* Program Code     : COSC2138
* Start up code provided by the CTeach Team
****************************************************************************/

#include "bstring.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/****************************************************************************
*brads string "class"
*****************************************************************************/

/****************************************************************************
clears a string
*****************************************************************************/
void stringClear(String *string)
{
  string->depth=0;
  string->blocks=1;
  string->offset=0;
}
/****************************************************************************
*initializes a string ready to use
*****************************************************************************/
void stringInit(String *string)
{
  /*allocate memory for the string and initialize it*/
  string->contents=malloc(STRINGSIZE*sizeof(char));
  stringClear(string);
}
/****************************************************************************
*frees the memory used by the string
*****************************************************************************/
void stringFree(String *string)
{
    /*if the string has something in it then clear it*/
  if(string->contents!=NULL)
    free(string->contents);
}

/****************************************************************************
*adds a char to the string
*****************************************************************************/
char* stringAddChar(String *string,char c)
{
  /*if the place to place the char is at the end
  of the mem block then grow it*/
  if(string->offset==(STRINGSIZE*string->blocks)-1)
  {
    string->blocks++;
    string->contents=
      realloc(string->contents,STRINGSIZE*string->blocks*sizeof(char));
  }
  /*place the char i the string and move ptr along and null terminate*/
  *(string->contents+string->offset)=c;
  *(string->contents+string->offset+1)='\0';
  string->offset++;
  return string->contents;
}
/****************************************************************************
*add a whole char array to the string
*****************************************************************************/
char* stringAddCharArray(String *string,char * toadd)
{
  /*add all chars the the internal char array and return the contents*/
  while(*(toadd)!='\0')
  {
    stringAddChar(string,(char)*(toadd++));
  }
  return string->contents;

}
/****************************************************************************
*return the underlying char array
*****************************************************************************/
char* stringToCharArray(String *string)
{
  return string->contents;
}

/****************************************************************************
*specificially set the contents of the string
*****************************************************************************/
void stringSet(String *string,char *stringtoset)
{
  stringInit(string);
  stringAddCharArray(string,stringtoset);
}



