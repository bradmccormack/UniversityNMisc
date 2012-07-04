/****************************************************************************
* COSC2138/CPT220 - Programming Principles 2A
* Study Period 2  2010 Assignment #2 - index program
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Course Code      : EDIT HERE
* Program Code     : EDIT HERE
* Start up code provided by the CTeach Team
****************************************************************************/
#ifndef INDEX_H
#define INDEX_H

/* System-wide header files. */
#include <stdio.h>
#include <stdlib.h>

/* System-wide constants. */
#define SUCCESS 1
#define FAILURE 0
#define ONE 49
#define SEVEN 55

/* Structure definitions. */

typedef struct docStruct* DocTypePtr;
typedef struct docStruct
{
    char* name;
    unsigned int count;
    DocTypePtr nextDoc;
}DocType;

typedef struct wordStruct* WordTypePtr;
typedef struct wordStruct
{
    char* word;
    unsigned count;
    WordTypePtr nextWord;
    DocTypePtr nextDoc;
} WordType;

typedef struct indexStruct
{
    WordTypePtr headWord;
    WordTypePtr longestWord;
    WordTypePtr mostCommonWord;
    unsigned totalWords;
    unsigned uniqueWords;
} IndexType;

#endif
