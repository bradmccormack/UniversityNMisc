/****************************************************************************
* COSC2138/CPT220 - Programming Principles 2A
* Study Period 2  2010 Assignment #2 - index program
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Course Code      : EDIT HERE
* Program Code     : EDIT HERE
* Start up code provided by the CTeach Team
****************************************************************************/
#include "index.h"
#include "index_options.h"
#include "index_utility.h"
#include "bstring.h"
#include "butils.h"
#include <ctype.h>



int main(int argc, char* argv[])
{
  int result,quit;
  char choice[2];
  IndexType index;


  if(argc<2 || argc>2)
  {
    printf("Incorrect arguments.\n");
    printf("\nUsage: index <datafile>\n");
    return EXIT_SUCCESS;
  }

  /*initialization of main variables*/
  quit=FALSE;

  /*make system in a safe state*/
  systemInit(&index);
  /*load in the data into the index*/
  result= loadData(&index, argv[1]);
  if(result==FAILURE)
  {
    printf("\nError encountered. exiting..\n");
    return EXIT_FAILURE;
  }

  /*keep looping until they have selected quit*/
  while(!quit)
  {
    printf("\n\nMain Menu:\n");
    printf("[1] Index Summary\n");
    printf("[2] Search Index\n");
    printf("[3] Index Report\n");
    printf("[4] Stemming Report\n");
    printf("[5] Stopping Report\n");
    printf("[6] Delete Stop Words\n");
    printf("[7] Exit\n");

    /*keep looping until they enter valid choice*/
    do
    {
      getString(choice,2,0,"Enter a choice :");
    } while(choice[0]<ONE && choice[0]>SEVEN);

    switch(choice[0]-48)
    {
      case 1:
        indexSummary(&index);
        break;
      case 2:
        searchIndex(&index);
        break;
      case 3:
        indexReport(&index);
        break;
      case 4:
        stemmingReport(&index);
        break;
      case 5:
        stoppingReport(&index);
        break;
      case 6:
        deleteStopWords(&index);
        break;
      case 7:
        systemFree(&index);
        quit=TRUE;
        break;
    }

  }

  return EXIT_SUCCESS;
}
