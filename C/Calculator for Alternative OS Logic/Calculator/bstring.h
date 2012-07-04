/****************************************************************************
* COSC2138/CPT220 - Programming Principles 2A
* Study Period 2  2010 Assignment #2 - index program
* Full Name        : Bradley Jason Mccormack
* Student Number   : s3258798
* Course Code      : COSC2138
* Program Code     : COSC2138
* Start up code provided by the CTeach Team
****************************************************************************/

#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

#define FALSE 0
#define TRUE 1
#define STRINGSIZE 60

typedef struct stringInfo
{
  char* contents;
  /* the depth of the evaulation .. eg 10*2+(3*4)
  ... the second * has depth of 2 */
  unsigned int depth;
  unsigned int offset;
  unsigned int blocks;
} String;

void stringInit(String *string);
char* stringAddChar(String *string,char c);
char* stringAddCharArray(String *string,char *toadd);
char* stringToCharArray(String *string);
void stringSet(String *string,char *stringtoset);
void stringFree(String *string);
void stringClear(String *string);

#endif
