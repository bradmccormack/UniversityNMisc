/****************************************************************************
* COSC2138/CPT220 - Programming Principles 2A
* Study Period 2  2010 Assignment #2 - index program
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Course Code      : EDIT HERE
* Program Code     : EDIT HERE
* Start up code provided by the CTeach Team
****************************************************************************/
#ifndef INDEX_UTILITY_H
#define INDEX_UTILITY_H
#include "bstring.h"


/*Tag information*/
#define OPENTAG '<'
#define CLOSETAG '>'
#define TAGDOC "DOC"
#define TAGDOCNUM "DOCNO"
#define TAGHDR "DOCHDR"
#define TAGHDRCLOSE "/DOCHDR"
#define TAGDOCCLOSE "/DOC"
#define TAGDOCNUMCLOSE "/DOCNO"

/*various variables that will be used*/
#define BUFFSIZE 512
#define a 97
#define z 122
#define A 65
#define Z 90
#define TEMP_STRING_LENGTH 80

#define SPACE ' '
#define FULLSTOP '.'

/* Function prototypes. */
void readRestOfLine();
void systemInit(IndexType* index);
int loadData(IndexType* index, char* trecFile);
void systemFree(IndexType* index);
WordTypePtr insertBefore(WordTypePtr nextnode,WordTypePtr prevnode,String* word);
DocTypePtr insertDocBefore(DocTypePtr prevnode,DocTypePtr nextnode,char* docNum);
WordTypePtr insertatEnd(WordTypePtr tail,String* word);
DocTypePtr insertDocatEnd(DocTypePtr tail,char* docNum);
WordTypePtr deletebetween(WordTypePtr prev,WordTypePtr node);
int insertWord(IndexType* index,String* word,char* docNum);
int insertDoc(WordTypePtr word,char* docNum);
void printList(IndexType* index);
int getString(char* string, unsigned length,unsigned minlength, char* prompt);
#endif
