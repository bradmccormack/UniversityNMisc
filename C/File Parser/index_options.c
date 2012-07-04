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

/****************************************************************************
* Menu option #1: Index Summary
* Displays a high level summary of index contents.
****************************************************************************/
void indexSummary(IndexType* index)
{
  printf("\nIndex Summary\n");
  printf("-------------\n\n");
  printf("Unique Words: %d\n",index->uniqueWords);
  printf("Total Words: %d\n",index->totalWords);
  printf("Longest Word: %s\n",index->longestWord->word);
  printf("Most Common Word: %s\n\n",index->mostCommonWord->word);
}


/****************************************************************************
* Menu option #2: Search Index
* Allows the user to make a new report file for a chosen category.
****************************************************************************/
void searchIndex(IndexType* index)
{
  char word[MAXLENGTH];
  int result;
  WordTypePtr node;
  DocTypePtr docnode;

  printf("\nIndex Search\n");
  printf("-------------\n\n");

  result=getString(word,MAXLENGTH,0,"Enter a word :");
  while(result==FAILURE)
    result=getString(word,MAXLENGTH,0,"Enter a word :");

  /*return to main menu if they enter a space*/
  if(strlen(word)==0)
  {
    printf("\nSearch cancelled. Returning to main menu \n");
    return;
  }
  printf("\nResults:\n\n");
  node=index->headWord;
  while(node!=NULL)
  {
    if(strstr(node->word,word)!=NULL)
    {
        /*display the result*/
         printf("%s (%d)\n",node->word,node->count);
         /*and linked documents*/
         docnode=node->nextDoc;
         do
         {
            printf("-> %s (%d)\n",docnode->name,docnode->count);
            docnode=docnode->nextDoc;
         }  while(docnode!=NULL);
    }
    node=node->nextWord;
  }
}


/****************************************************************************
* Menu option #3: Index Report
* Creates an external file with statistics of all words in the index.
****************************************************************************/
void indexReport(IndexType* index)
{
  FILE *fp;
  WordTypePtr node;
  int longestword;

  printf("\nIndex Report\n");
  printf("------------\n");

  if((fp=fopen("report.txt","w"))==NULL)
  {
      printf("Failed to open report.txt for writing!\n");
      return;
  }

  longestword=strlen(index->longestWord->word);

  /*align the headings .. Word should be left aligned */
  fprintf(fp,"%-*s%4s\n",longestword,"Word","Count");
  fprintf(fp,"%-*s%4s\n",longestword,"----","-----");

  node=index->headWord;
  while(node!=NULL)
  {
    /*write out each node where word is left aligned and count is right*/
    fprintf(fp,"%-*s %4d\n",longestword,node->word,node->count);
    node=node->nextWord;
  }
  fclose(fp);

  printf("\nThe file report.txt has been created\n");


}


/****************************************************************************
* Menu option #4: Stemming Report
* Creates an external file with statistics of all words in the index that
* have common suffixes.
****************************************************************************/
void stemmingReport(IndexType* index)
{
  FILE *fp;
  WordTypePtr node;
  char filename[FILENAME_MAX];
  String stem;
  char c;
  char buffer[BUFFSIZE];
  char* longestword;

  unsigned int nodelength;



  printf("\nStemming Report\n");
  printf("---------------\n");


  getString(filename,FILENAME_MAX,0,"Enter name of a suffixes file:");
  /*if they enter no file name cancel to the main menu*/
  if(strlen(filename)==0)
  {
    printf("\nStemm report cancelled. Returning to main menu.\n");
    return;
  }

  /*open the file*/
  fp=fopen(filename,"r");
  if(fp==NULL)
  {
    printf("\n Failed to read %s file!\n",filename);
    return;
  }

   stringInit(&stem);

  /*reserve space for longest word*/
  longestword=malloc(strlen(index->longestWord->word)*sizeof(char));


  /*speed up*/
  setvbuf(fp,buffer,_IOFBF,BUFFSIZE);

  printf("\nResults:\n\n");

  /*loop through all nodes*/
  node=index->headWord;
  while(node!=NULL)
  {
    /*printf("node is %s\n",node->word);*/
    nodelength=strlen(node->word);

    /*loop through all stem words*/
    fseek(fp,0,0);
    while((c=fgetc(fp))!=EOF)
    {
      /*next stem words is ready*/
      if(c=='\n')
      {
        /*if the stem word is larger than the node word skip the node*/
        if(stem.offset>nodelength)
        {
          stringClear(&stem);
          continue;
        }
        /*check if the node word containts the stem word*/
        if(strcmp(stem.contents,node->word+nodelength-stem.offset)==0)
        {
          /*get the base word and null terminate*/
          strncpy(longestword,node->word,nodelength-stem.offset);
          *(longestword+nodelength-stem.offset)='\0';
          /*display the node and the stem prefix*/
          printf("%s %s\n",node->word,longestword);
        }
        stringClear(&stem);
      }
      /*keep building the stem word*/
      else
        stringAddChar(&stem,c);
    }
    node=node->nextWord;
  }
  fclose(fp);
  free(longestword);
  stringFree(&stem);
}

/****************************************************************************
* Menu option #5: Stopping Report
* Creates an external file with statistics of some common words in the index.
****************************************************************************/
void stoppingReport(IndexType* index)
{
  FILE *fp;
  unsigned int stopwords,i,reported;
  char word[MAXLENGTH];
  char buffer[BUFFSIZE];
  WordTypePtr indexnode;

  /*this contains the words and their frequency*/
  unsigned int* stoplist;


  printf("\nStopping Report\n");
  printf  ("---------------\n");


  do
  {
    getString(word,MAXLENGTH,0,"How many words do you want to report (1-999)?");

    if(strlen(word)==0)
    {
      printf("Stopping Report cancelled. Returning to main menu.\n");
      return;
    }
    stopwords=atoi(word);
    /*keep looping until valid number*/
  } while(stopwords<1 || stopwords>999);



  /*open the file*/
  fp=fopen("stopping-report.txt","w");
  if(fp==NULL)
  {
    printf("\n Failed to open stopping-report.txt file!\n");
    return;
  }
  /*speed up*/
  setvbuf(fp,buffer,_IOFBF,BUFFSIZE);

    if(stopwords==1)
  {
    /*do to file*/
    fprintf(fp,"%s %d",index->mostCommonWord->word,index->mostCommonWord->count);
    printf("The most common word has been reported to file stopping-report.txt");
    fclose(fp);
    return;
  }

  /*allocate space for stoplist*/
  stoplist=calloc(stopwords,sizeof(unsigned int));
  if(stoplist==NULL)
  {
    printf("Failed to allocate memory for stop list\n");
    return;
  }


  /*set the last entry to the highest value*/
  stoplist[stopwords-1]=index->mostCommonWord->count;

  indexnode=index->headWord;
  while(indexnode!=NULL)
  {
    /*is the current node count greater than at least one existing most common*/
    for(i=0; i<stopwords; i++)
    {
      /*its less than the current word so exit as we know where to insert*/
      if(indexnode->count<stoplist[i])
        break;
    }
    /*the node count is less than any existing common word*/
    if(i!=0)
    {
      /*we have an insert postion so shift all memory before that down 1*/
      memmove(stoplist,stoplist,i-1);
      /*insert it*/
      stoplist[i-1]=indexnode->count;
    }
    indexnode=indexnode->nextWord;
  }

  /*correlate the mostcommon counts with actual words*/
  reported=0;
  indexnode=index->headWord;
  while(indexnode!=NULL)
  {
    for(i=0; i<stopwords; i++)
    {
      if(indexnode->count==stoplist[i])
      {
        fprintf(fp,"%s %d\n",indexnode->word,indexnode->count);
        reported++;
        /*all words saved so exit*/
        if(reported==stopwords)
        {
          fclose(fp);
          printf("%d most common words reported to file stopping-report.txt"
                 ,stopwords);
          free(stoplist);
          return;
        }
      }
    }
    indexnode=indexnode->nextWord;
  }
  fclose(fp);
}



/****************************************************************************
* Menu option #6: Delete Stop Words
* Removes common words from the index supplied from an external file.
****************************************************************************/
void deleteStopWords(IndexType* index)
{
  FILE *fp;
  unsigned int injunk,in,notin;
  char word[MAXLENGTH],c;
  char buffer[BUFFSIZE];
  WordTypePtr node,prev,temp;
  String line;

  printf("\nDelete Stop Words\n");
  printf("-----------------\n");


  getString(word,MAXLENGTH,0,"Enter name of stop word file:");

  if(strlen(word)==0)
  {
    printf("Delete Stop Words cancelled. Returning to main menu.\n");
    return;
  }

  if((fp=fopen(word,"rb"))==NULL)
  {
    printf("Failed to read %s !\n",word);
    return;
  }

  setvbuf(fp,buffer,_IOFBF,BUFFSIZE);

  stringInit(&line);
  injunk=FALSE;
  in=FALSE;
  notin=FALSE;

  while((c=fgetc(fp))!=EOF)
  {
    if((c>=a && c<=z) || (c>=A && c<=Z))
    {
      injunk=FALSE;
      stringAddChar(&line,c);
    }
    if(!injunk)
    {
      if(c==SPACE || c=='\n')
      {
        /*found the word so search index and remove the node if its found*/
        node=index->headWord;
        prev=node;
        while(node!=NULL)
        {
          /*found the word to delete so delete it*/
          if(strcmp(node->word,line.contents)==0)
          {
            temp=deletebetween(prev,node);

            /*temp=node;*/


            if(node==index->headWord)
                index->headWord=temp;
            else
                node=temp;


            stringClear(&line);
            injunk=TRUE;
            in++;
            break;
          }
          prev=node;
          node=node->nextWord;

        }
        /*the word wasnt found in the list*/
        if(node==NULL)
            notin++;

      }
    }
  }
  printf("\n\n%d words removed from the index. %d words not found."
         ,in,notin);

  stringFree(&line);
  fclose(fp);


}
