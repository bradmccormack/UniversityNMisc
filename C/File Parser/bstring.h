#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

#define FALSE 0
#define TRUE 1
#define STRINGSIZE 60

typedef struct stringInfo
{
    char* contents;
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
