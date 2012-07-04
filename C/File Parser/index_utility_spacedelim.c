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
#include <string.h>
#include <stdio.h>
#include <ctype.h>


/*#define CONFUSEDDEBUG*/


/****************************************************************************
* Function readRestOfLine() is used for buffer clearing. Source:
* https://inside.cs.rmit.edu.au/~sdb/teaching/C-Prog/CourseDocuments/
* FrequentlyAskedQuestions/#alternative
****************************************************************************/
void readRestOfLine()
{
  int c;

  /* Read until the end of the line or end-of-file. */
  while ((c = fgetc(stdin)) != '\n' && c != EOF)
    ;

  /* Clear the error and end-of-file flags. */
  clearerr(stdin);
}


/****************************************************************************
* Initialises the index to a safe empty state.
****************************************************************************/
void systemInit(IndexType* index)
{
  memset(index,'\0',sizeof(IndexType));
}

void printList(IndexType* index)
{
  WordTypePtr node;

  printf("\n Current List ..\n");

  node=index->headWord;
  while(node!=NULL)
  {
    printf("Node >%s\n",node->word);
    node=node->nextWord;
  };
}

/*inserts the word in between prevnode and next node*/
WordTypePtr insertBefore(WordTypePtr prevnode,WordTypePtr nextnode,String* word)
{
  WordTypePtr newnode;

  /*create a new node */
  newnode=malloc(sizeof(WordType));

  /*create space for word in the new node*/
  newnode->word=malloc(word->offset+1);
  strcpy( newnode->word,word->contents);
  *(newnode->word+word->offset)='\0';
  newnode->count=1;

  /*link the new head to the existing head*/
  newnode->nextWord=nextnode;

  if(prevnode!=NULL)
    prevnode->nextWord=newnode;

  return newnode;
}

WordTypePtr insertatEnd(WordTypePtr tail,String* word)
{
  WordTypePtr newnode;

  /*create a new node */
  newnode=malloc(sizeof(WordType));
  /*create space for word in the new node*/
  newnode->word=malloc(word->offset+1);
  strcpy( newnode->word,word->contents);
  *(newnode->word+word->offset)='\0';
  newnode->count=1;
  newnode->nextWord=NULL;
  tail->nextWord=newnode;

  return newnode;
}



/*attempts to insert word.. Fails if cannot allocate memory etc */
int insertWord(IndexType* index,String* word)
{
  WordTypePtr node,tempnode=NULL,prevnode=NULL;

  int wordequality;
  static int longestword=0,mostcommoncount=0;

  wordequality=0;

  /*the list is empty insert at the start*/
  if(index->headWord==NULL)
  {
    index->headWord=insertBefore(NULL,index->headWord,word);
    index->uniqueWords++;
    index->totalWords++;
    return SUCCESS;
  }

  node=index->headWord;
  do
  {
    wordequality=strcmp(word->contents,node->word);

    /*check if the word to insert should be at the start of the list*/
    if(wordequality<0)
    {
      tempnode=insertBefore(prevnode,node,word);

      index->uniqueWords++;
      index->totalWords++;
      /*if this word is the longest word then update index longest*/
      if(word->offset>longestword)
      {
        longestword=word->offset;
        index->longestWord=node;
      }
      if(node==index->headWord)
        index->headWord=tempnode;

      return SUCCESS;
    }
    /*duplicate word case*/
    if(wordequality==0)
    {
      node->count++;
      index->totalWords++;

      /*update the most commonword if necessary*/
      if(node->count>mostcommoncount)
        index->mostCommonWord=node;


      return SUCCESS;
    }
    if(node!=NULL)
      prevnode=node;

    node=node->nextWord;
  } while(node!=NULL);

  /*to be inserted at the end of the list*/

  node=insertatEnd(prevnode,word);

  index->uniqueWords++;
  index->totalWords++;
  /*if this word is the longest word then update index longest*/
  if(word->offset>longestword)
  {
    longestword=word->offset;
    index->longestWord=node;
  }
  return SUCCESS;
}

void insertDummy(String* word)
{
  static int i=0;

  printf("inserting word %d) %s\n",i++,stringToCharArray(word));
  /*getchar();*/
}


/****************************************************************************
* Loads all data into the index.
****************************************************************************/
int loadData(IndexType* index, char* trecFile)
{
  char buffer[BUFFSIZE];
  int nextchar;
  char* tagname;
  int inTag;
  int inHdr;
  int pastHdr;
  int inDoc;
  String string;
  String tag;
  FILE *trec_file;

  inTag=FALSE;
  inHdr=FALSE;
  pastHdr=FALSE;
  inDoc=FALSE;

  /*set up a String variable */
  stringInit(&string);
  stringInit(&tag);


  if((trec_file=fopen(trecFile,"rb"))==NULL)
  {
    printf("%s failed to load !\n",trecFile);
    return FAILURE;
  }

  printf("Loading index file %s ..\n",trecFile);
  /*need to allocate memory for dummy head word down here*/
  index->headWord=NULL;
  /*set up full buffering for performance */
  setvbuf(trec_file,buffer,_IOFBF,BUFFSIZE);

  /*keep looping until end of file */
  while((nextchar=fgetc(trec_file))!=EOF)
  {



    /*close the current tag*/
    if(nextchar==CLOSETAG)
    {
      inTag=FALSE;

      /*find out the tag that was just processed*/
      tagname=stringToCharArray(&tag);

      /*if in document tag then flag it*/
      if(strcmp(tagname,(char*)TAGDOC)==0)
        inDoc=TRUE;

      if(strcmp(tagname,(char*)TAGDOCCLOSE)==0)
      {
        inDoc=FALSE;
        inHdr=FALSE;
        pastHdr=FALSE;
      }

      /*if in header then flag it*/
      if(strcmp(tagname,(char*)TAGHDR)==0)
        inHdr=TRUE;

      /*if past th  String string;
          String tag;e header then flag it*/
      if(strcmp(tagname,(char*)TAGHDRCLOSE)==0)
        pastHdr=TRUE;


      stringInit(&tag);
      continue;
    }

     /*if inside a tag then keep building the name of the tag*/
    if(inTag)
    {
      stringAddChar(&tag,nextchar);
      continue;
    }



    /*ignore words outside of doc if outside of a Doc*/
    if(inDoc)
    {
      /*only process as a word if its not a tag*/
      if(!inTag)
      {
        /*ignore words until after the header*/
        if(pastHdr)
        {
          /*its a new word*/
        if(!(nextchar>=a && nextchar<=z) || (nextchar>=A && nextchar<=Z))

          {
            /*perhaps the String is empty because
            this word contained All non alpha chars
            so don't insert it*/
            if(string.offset!=0)
            {
              /*insertWord(index,&string);*/
              insertDummy(&string);
              stringInit(&string);
              continue;
            }
          }
          else
          {
            /*add the char only if its alhpabetic*/

              stringAddChar(&string,tolower(nextchar));
          }
        }
      }
    }

    if(nextchar==OPENTAG)
    {
      inTag=TRUE;
      continue;

    }


  }
  printList(index);
  fclose(trec_file);

  return SUCCESS;
}


/****************************************************************************
* Deallocates memory used in the index.
****************************************************************************/
void systemFree(IndexType* index)
{
}
