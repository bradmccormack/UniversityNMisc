/****************************************************************************
* COSC2138/CPT220 - Programming Principles 2A
* Study Period 2  2010 Assignment #2 - index program
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Course Code      : EDIT HERE
* Program Code     : EDIT HERE
* Start up code provided by the CTeach Team
****************************************************************************/
#include <string.h>
#ifndef INDEX_OPTIONS_H
#define INDEX_OPTIONS_H

#define MAXLENGTH 100

/* Function prototypes. */
void indexSummary(IndexType* index);
void searchIndex(IndexType* index);
void indexReport(IndexType* index);
void stemmingReport(IndexType* index);
void stoppingReport(IndexType* index);
void deleteStopWords(IndexType* index);

#endif
