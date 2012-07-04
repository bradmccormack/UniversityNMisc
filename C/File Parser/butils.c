#include "butils.h"
#include <stdio.h>

int scoreWord(String* string)
{
    register int i;
    int depth=string->offset; /*length of word*/
    int score;
    char letter;
    int stride; /*the distance between the last and first letter*/

    stride=z-a+1;

    score=0;

    /*score the first letter differently*/
    letter=*(string->contents);
     if(letter>=a && letter<=z)
        score+=depth*stride+((letter-a+1)*depth*stride);

     if(letter>=A && letter<=Z)
           score+=depth*stride+((letter-A+1)*depth*stride);

     /*score the remaining letters*/
    i=1;
    while(*(string->contents+i)!='\0')
    {
        letter=*(string->contents+i);
        /*if lower case */
        if(letter>=a && letter<=z)
            score+=depth*stride+letter-a+1;

        if(letter>=A && letter<=Z)
         score+=depth*stride+letter-A+1;

        /*next letter gets a lower score*/
        depth--;
        i++;
    }
    return score;
}
