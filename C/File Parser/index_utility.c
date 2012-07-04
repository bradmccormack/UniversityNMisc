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



/****************************************************************************
* getString(): An interactive string input function.
* Source: http://blackboard.rmit.edu.au/courses/1/COSC2138OUA_1037/content/
  _2307602_1/dir_CLibFunctEx_220.zip/CLibFunctEx_220/
  InputValidation/getString-basic.c
  Modified to add minimum length by me - Shows implementation using fgets as requested
****************************************************************************/
int getString(char* string, unsigned length,unsigned minlength, char* prompt)
{
    int finished = FALSE;
    char tempString[TEMP_STRING_LENGTH + 2];

    /* Continue to interact with the user until the input is valid. */
    do
    {
        /* Provide a custom prompt. */
        printf("%s", prompt);

        /* Accept input. "+2" is for the \n and \0 characters. */
        fgets(tempString, length + 2, stdin);

        /* A string that doesn't have a newline character is too long. */
        if (tempString[strlen(tempString) - 1] != '\n' )
        {
            printf("Input was too long.\n");
            readRestOfLine();
        }
        else if(strlen(tempString)<minlength+1)
        {
            printf("Input was too short.\n");
        }
        else
        {
            finished = TRUE;
        }
    }
    while (finished == FALSE);

    /* Overwrite the \n character with \0. */
    tempString[strlen(tempString) - 1] = '\0';

    /* Make the result string available to calling function. */
    strcpy(string, tempString);

    return SUCCESS;
}


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

/*inserts the docNum in between prevnode and next node*/
DocTypePtr insertDocBefore(DocTypePtr prevnode,DocTypePtr nextnode,char* docNum)
{
    DocTypePtr newnode;
    int doclen;

    newnode=malloc(sizeof(DocType));

    doclen=strlen(docNum);
    /*create space for docname in the new node and copy it across*/
    newnode->name=malloc(doclen+1);
    strcpy(newnode->name,docNum);
    *(newnode->name+doclen+1)='\0';
    newnode->count=1;

    newnode->nextDoc=nextnode;

    if(prevnode!=NULL)
        prevnode->nextDoc=newnode;

    return newnode;

}


/*inserts the word in between prevnode and next node*/
WordTypePtr insertBefore(WordTypePtr prevnode,WordTypePtr nextnode,String* word)
{
    WordTypePtr newnode;

    /*create a new node */
    newnode=malloc(sizeof(WordType));

    /*create space for word in the new node and copy it across*/
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


WordTypePtr deletebetween(WordTypePtr prev,WordTypePtr node)
{
    WordTypePtr temp;

    /*deleting at the head case
    the node and prev is the same*/
    if(prev==node)
    {
        temp=node->nextWord;
        free(node->word);
        free(node);
        return temp;
    }
    /*deleting at the tail case
    the next node is null*/
    if(node->nextWord==NULL)
    {
        prev->nextWord=NULL;
        free(node->word);
        free(node);
        return prev;
    }

    /*deleting in between two nodes*/
    prev->nextWord=node->nextWord;
    free(node->word);
    free(node);
    return prev;
}

DocTypePtr insertDocatEnd(DocTypePtr tail,char* docNum)
{
    DocTypePtr newnode;
    int doclen;
    doclen=strlen(docNum);

    /*create a new node and copy across*/
    newnode=malloc(sizeof(DocType));
    newnode->name=malloc(doclen+1);
    strcpy(newnode->name,docNum);
    *(newnode->name+doclen+1)='\0';

    /*linking of nodes*/
    newnode->count=1;
    newnode->nextDoc=NULL;
    tail->nextDoc=newnode;

    return newnode;
}


WordTypePtr insertatEnd(WordTypePtr tail,String* word)
{
    WordTypePtr newnode;

    /*create a new node */
    newnode=malloc(sizeof(WordType));
    /*create space for word in the new node and copy across*/
    newnode->word=malloc(word->offset+1);
    strcpy( newnode->word,word->contents);
    *(newnode->word+word->offset)='\0';

    /*linking of nodes*/
    newnode->count=1;
    newnode->nextWord=NULL;
    tail->nextWord=newnode;

    return newnode;
}

int insertDoc(WordTypePtr word,char* docNum)
{
    DocTypePtr node,prevnode;
    int docequality;

    /*if there are no documents insert the first one and exit*/
    if(word->nextDoc==NULL)
    {
        word->nextDoc=insertDocBefore(NULL,word->nextDoc,docNum);
        /*printf("Doc inserted at head %s\n",docNum);*/
        return SUCCESS;
    }
    node=word->nextDoc;
    /*loop through and insert Doc at appropriate location*/
    do
    {
        /*printf("docnode name addr=%c\n",node->name[0]);*/
        docequality=strcmp(docNum,node->name);

        /*insert the doc here*/
        if(docequality<0)
            node=insertDocBefore(prevnode,node,docNum);

        /*doc already in existence*/
        if(docequality==0)
        {
            node->count++;
            return SUCCESS;
        }

        if(node!=NULL)
            prevnode=node;

        node=node->nextDoc;
    }
    while(node!=NULL);
    /*to be inserted at the end of the list*/
    node=insertDocatEnd(prevnode,docNum);

    return SUCCESS;
}

/*attempts to insert word.. Fails if cannot allocate memory etc */
int insertWord(IndexType* index,String* word,char* docNum)
{
    WordTypePtr node,tempnode=NULL,prevnode=NULL;

    int wordequality;
    static unsigned int longestword=0,mostcommoncount=0;

    wordequality=0;

    /*the list is empty insert at the start*/
    if(index->headWord==NULL)
    {
        index->headWord=insertBefore(NULL,index->headWord,word);
        index->uniqueWords++;
        index->totalWords++;

        /*also insert the first document*/
        index->headWord->nextDoc=NULL;
        insertDoc(index->headWord,docNum);

        return SUCCESS;
    }

    node=index->headWord;
    do
    {
        wordequality=strcmp(word->contents,node->word);
        /*check if the word to insert should be at the start of the list*/
        if(wordequality<0)
        {
            /*insert the word*/
            tempnode=insertBefore(prevnode,node,word);

            /*insert the doc if necessary*/
            tempnode->nextDoc=NULL;
            insertDoc(tempnode,docNum);

            /* update the index unique words*/
            index->uniqueWords++;
            /*and the index total word count*/
            index->totalWords++;

            /*if this word is the longest word then update index longest*/
            if(word->offset>longestword)
            {
                longestword=word->offset;
                index->longestWord=tempnode;
            }

            if(node==index->headWord)
                index->headWord=tempnode;

            return SUCCESS;
        }
        /*duplicate word case*/
        if(wordequality==0)
        {
            /*update node count*/
            node->count++;

            /*update doc count*/
            insertDoc(node,docNum);
            /*node->nextDoc->count++;*/

            /*update the index total count*/
            index->totalWords++;

            /*update the most commonword if necessary*/
            if(node->count>mostcommoncount)
            {
                index->mostCommonWord=node;
                mostcommoncount=index->mostCommonWord->count;
            }

            return SUCCESS;
        }
        if(node!=NULL)
            prevnode=node;

        node=node->nextWord;
    }
    while(node!=NULL);

    /*to be inserted at the end of the list*/
    node=insertatEnd(prevnode,word);
    /*also insert the first document*/
    node->nextDoc=NULL;
    insertDoc(node,docNum);


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


/****************************************************************************
* Loads all data into the index.
****************************************************************************/
int loadData(IndexType* index, char* trecFile)
{
    char buffer[BUFFSIZE];
    int nextchar;
    char* tagname;
    int inTag,inHdr,pastHdr,inDoc,inDocnum;
    String string,tag,docNum;
    FILE *trec_file;

    inTag=FALSE;
    inHdr=FALSE;
    pastHdr=FALSE;
    inDoc=FALSE;


    /*set up a String variable */
    stringInit(&string);
    stringInit(&tag);
    stringInit(&docNum);

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
            {
                inDoc=TRUE;
            }

            /*if encountered a new document number then allocate new node*/
            if(strcmp(tagname,(char*) TAGDOCNUM)==0)
            {
                /*need to start building the next document name*/
                stringClear(&docNum);
                inDocnum=TRUE;
            }

            /*closing the document */
            if(strcmp(tagname,(char*)TAGDOCCLOSE)==0)
            {
                inDoc=FALSE;
                inHdr=FALSE;
                pastHdr=FALSE;
            }
            /*not in a doc anymore*/
            if(strcmp(tagname,(char*)TAGDOCNUMCLOSE)==0)
                inDocnum=FALSE;

            /*if in header then flag it*/
            if(strcmp(tagname,(char*)TAGHDR)==0)
                inHdr=TRUE;

            /*if past th  String string;
                String tag header then flag it*/
            if(strcmp(tagname,(char*)TAGHDRCLOSE)==0)
                pastHdr=TRUE;

            stringClear(&tag);
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
            /*if in the document number tag then keep building the docnum*/
            if(inDocnum)
                stringAddChar(&docNum,nextchar);

            /*only process as a word if its not a tag*/
            if(!inTag)
            {
                /*ignore words until after the header*/
                if(pastHdr)
                {
                    /*its a new word*/
                    if(nextchar==SPACE || nextchar==FULLSTOP || nextchar==OPENTAG )
                    {
                        /*perhaps the String is empty because
                        this word contained All non alpha chars
                        so don't insert it*/
                        if(string.offset!=0)
                        {
                            /*insert the current word into the index with the current docnum*/
                            insertWord(index,&string,docNum.contents);
                            stringClear(&string);
                        }
                    }
                    else
                    {
                        /*add the char only if its alhpabetic*/
                        if((nextchar>=a && nextchar<=z) || (nextchar>=A && nextchar<=Z))
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
    fclose(trec_file);
    stringFree(&string);
    stringFree(&tag);
    stringFree(&docNum);
    return SUCCESS;
}


/****************************************************************************
* Deallocates memory used in the index.
****************************************************************************/
void systemFree(IndexType* index)
{
    /*loop through every node
     delete the word in it and then delete the structure*/
    WordTypePtr node,temp;
    DocTypePtr docnode,tempdocnode;

    node=index->headWord;
    while(node!=NULL)
    {
        temp=node;
        node=node->nextWord;
        /*free the word in the node*/
        free(temp->word);

        /*free all the doc nodes attached to the word*/
        docnode=temp->nextDoc;

        while(docnode!=NULL)
        {
            tempdocnode=docnode;
            docnode=docnode->nextDoc;

            /*free the document number text*/
            free(tempdocnode->name);
            /*free the document node*/
            free(tempdocnode);


        }
        free(temp);
    }



}
